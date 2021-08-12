#include "ornaments.h"

#include <map/image.h>
#include <map/building.h>
#include <graphics/image.h>
#include <map/property.h>
#include <building/animation.h>
#include <city/entertainment.h>
#include <building/dock.h>
#include <city/population.h>
#include <building/rotation.h>
#include <map/water_supply.h>
#include <map/grid.h>
#include <game/resource.h>
#include <cmath>
#include <city/buildings.h>
#include <city/ratings.h>
#include <city/labor.h>
#include <building/industry.h>
#include <map/terrain.h>
#include <game/time.h>
#include "building/building.h"

static bool drawing_building_as_deleted(building *b) {
    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->grid_offset)))
        return true;
    return false;
}

/////// ANIMATIONS

static void draw_dock_workers(const building *b, int x, int y, color_t color_mask) {
    int num_dockers = building_dock_count_idle_dockers(b);
    if (num_dockers > 0) {
        int image_dock = map_image_at(b->grid_offset);
        int image_dockers = image_id_from_group(GROUP_BUILDING_DOCK_DOCKERS);
        if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_1))
            image_dockers += 0;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_2))
            image_dockers += 3;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK_3))
            image_dockers += 6;
        else {
            image_dockers += 9;
        }
        if (num_dockers == 2)
            image_dockers += 1;
        else if (num_dockers == 3)
            image_dockers += 2;

        const image *img = image_get(image_dockers);
        ImageDraw::img_generic(image_dockers, x + img->sprite_offset_x, y + img->sprite_offset_y, color_mask);
    }
}
static void draw_hippodrome_spectators(const building *b, int x, int y, color_t color_mask) {
    // get which part of the hippodrome is getting checked
    int building_part;
    if (b->prev_part_building_id == 0) {
        building_part = 0; // part 1, no previous building
    } else if (b->next_part_building_id == 0) {
        building_part = 2; // part 3, no next building
    } else {
        building_part = 1; // part 2
    }
    int orientation = building_rotation_get_building_orientation(b->subtype.orientation);
    int population = city_population();
    if ((building_part == 0) && population > 2000) {
        // first building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 6, x + 147, y - 72,
                                       color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 8, x + 58, y - 79, color_mask);
                break;
            case DIR_4_BOTTOM_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 8, x + 119, y - 80,
                                       color_mask);
                break;
            case DIR_6_TOP_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 6, x, y - 72, color_mask);
        }
    } else if ((building_part == 1) && population > 100) {
        // middle building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
            case DIR_4_BOTTOM_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 7, x + 122, y - 79,
                                       color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
            case DIR_6_TOP_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 7, x, y - 80, color_mask);
        }
    } else if ((building_part == 2) && population > 1000) {
        // last building part
        switch (orientation) {
            case DIR_0_TOP_RIGHT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 8, x + 119, y - 80,
                                       color_mask);
                break;
            case DIR_2_BOTTOM_RIGHT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 6, x, y - 72, color_mask);
                break;
            case DIR_4_BOTTOM_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_2) + 6, x + 147, y - 72,
                                       color_mask);
                break;
            case DIR_6_TOP_LEFT:
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_HIPPODROME_1) + 8, x + 58, y - 79, color_mask);
                break;
        }
    }
}

static void draw_normal_anim(int x, int y, building *b, int grid_offset, int sprite_id, int color_mask, int base_id = 0, int max_frames = 0) {
    if (!base_id)
        base_id = map_image_at(grid_offset);
    int animation_offset = building_animation_offset(b, base_id, grid_offset, max_frames);
    if (animation_offset == 0)
        return;
    int ydiff = 15 * (map_property_multi_tile_size(grid_offset) + 1);
    const image *base = image_get(base_id);
    if (base_id != sprite_id)
        ImageDraw::img_sprite(sprite_id + animation_offset, x, y, color_mask);
    else
        ImageDraw::img_generic(sprite_id + animation_offset, x + base->sprite_offset_x,
                               y + base->sprite_offset_y - base->height + ydiff, color_mask);
}
static void draw_fort_anim(int x, int y, building *b) {
    if (map_property_is_draw_tile(b->grid_offset)) {
        int offset = 0;
        switch (b->subtype.fort_figure_type) {
            case FIGURE_FORT_LEGIONARY:
                offset = 4;
                break;
            case FIGURE_FORT_MOUNTED:
                offset = 3;
                break;
            case FIGURE_FORT_JAVELIN:
                offset = 2;
                break;
        }
        if (offset)
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_FORT) + offset, x + 81, y + 5,
                                   drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0);
    }
}
static void draw_gatehouse_anim(int x, int y, building *b) {
    int xy = map_property_multi_tile_xy(b->grid_offset);
    int orientation = city_view_orientation();
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) ||
        (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1) ||
        (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0) ||
        (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = image_id_from_group(GROUP_BULIDING_GATEHOUSE);
        int color_mask = drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0;
        if (b->subtype.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(image_id, x - 22, y - 80, color_mask);
            else
                ImageDraw::img_generic(image_id + 1, x - 18, y - 81, color_mask);
        } else if (b->subtype.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(image_id + 1, x - 18, y - 81, color_mask);
            else
                ImageDraw::img_generic(image_id, x - 22, y - 80, color_mask);
        }
    }
}
static void draw_entertainment_shows_c3(building *b, int x, int y, color_t color_mask) {
    if (b->type == BUILDING_AMPHITHEATER && b->num_workers > 0)
        ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW), x + 36, y - 47, color_mask);

    if (b->type == BUILDING_THEATER && b->num_workers > 0)
        ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_THEATER_SHOW), x + 34, y - 22, color_mask);

    if (b->type == BUILDING_COLOSSEUM && b->num_workers > 0)
        ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW), x + 70, y - 90, color_mask);

    if (b->type == BUILDING_HIPPODROME && b->main()->num_workers > 0 &&
        city_entertainment_hippodrome_has_race())
        draw_hippodrome_spectators(b, x, y, color_mask);
}

static void draw_entertainment_show_jugglers(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();
    if (main->data.entertainment.days1) {
        draw_normal_anim(x + 30, y + 15, b, b->grid_offset, image_id_from_group(GROUP_BUILDING_THEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_THEATER));
    }
}
static void draw_entertainment_shows_musicians(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();
    if (main->data.entertainment.days2) {
        building *next_tile = b->next();
        if (next_tile->type == BUILDING_BANDSTAND && next_tile->grid_offset == (b->grid_offset + 1))
            draw_normal_anim(x + 48, y + 12, b, b->grid_offset, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1 + 12,
                             color_mask, image_id_from_group(GROUP_BUILDING_COLOSSEUM), 12);
        else
            draw_normal_anim(x + 20, y + 12, b, b->grid_offset, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1,
                             color_mask, image_id_from_group(GROUP_BUILDING_COLOSSEUM), 12);
    }
}
static void draw_entertainment_shows_dancers(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();
    if (main->data.entertainment.days3_or_play) {
        draw_normal_anim(x + 64, y, b, b->grid_offset, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_LION_HOUSE));
    }
}

static const int X_VIEW_OFFSETS[9] = {
        0, 30, 60,
        -30, 0, 30,
        -60, -30, 0
};

static const int Y_VIEW_OFFSETS[9] = {
        30, 45, 60,
        45, 60, 75,
        60, 75, 90
};
int get_farm_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        int base = image_id_from_group(GROUP_BUILDING_FARMLAND);
        int fert_average = map_get_fertility_average(grid_offset);
        int fertility_index = 0;
        if (fert_average < 13)
            fertility_index = 0;
        else if (fert_average < 25)
            fertility_index = 1;
        else if (fert_average < 38)
            fertility_index = 2;
        else if (fert_average < 50)
            fertility_index = 3;
        else if (fert_average < 63)
            fertility_index = 4;
        else if (fert_average < 75)
            fertility_index = 5;
        else if (fert_average < 87)
            fertility_index = 6;
        else
            fertility_index = 7;
        return base + fertility_index;
    } else
        return image_id_from_group(GROUP_BUILDING_FARM_HOUSE);
}
int get_crops_image(int type, int growth) {
    int base = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        base = image_id_from_group(GROUP_BUILDING_FARMLAND);
        return (type - BUILDING_BARLEY_FARM) * 5 + growth;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        base = image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH);
        switch (type) {
            case BUILDING_BARLEY_FARM:
                return base + 6 * 0 + growth;
            case BUILDING_FLAX_FARM:
                return base + 6 * 6 + growth;
            case BUILDING_GRAIN_FARM:
                return base + 6 * 2 + growth;
            case BUILDING_LETTUCE_FARM:
                return base + 6 * 3 + growth;
            case BUILDING_POMEGRANATES_FARM:
                return base + 6 * 4 + growth;
            case BUILDING_CHICKPEAS_FARM:
                return base + 6 * 5 + growth;
            case BUILDING_FIGS_FARM:
                return base + 6 * 1 + growth;
//            case BUILDING_HENNA_FARM:
//                return base + 6 * 0 + growth;
        }
    }
    return image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH) + (type - BUILDING_BARLEY_FARM) * 6; // temp
}
void draw_ph_crops(int type, int progress, int grid_offset, int x, int y, color_t color_mask) {
    int image_crops = get_crops_image(type, 0);
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        for (int i = 0; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i*200)/100));
            ImageDraw::img_from_below(image_crops + growth_offset, x + X_VIEW_OFFSETS[i] + 60,
                                      y + Y_VIEW_OFFSETS[i] - 30, color_mask);
        }
    } else {
        for (int i = 4; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i*200)/100));
            ImageDraw::img_from_below(image_crops + growth_offset, x + X_VIEW_OFFSETS[i] + 60,
                                      y + Y_VIEW_OFFSETS[i] - 30, color_mask);
        }
    }

}

static void draw_ph_worker(int direction, int action, int frame_offset, int x, int y) {
    int action_offset = 0;
    switch (action) {
        case 0: // tiling
            action_offset = 104; break;
        case 1: // seeding
            action_offset = 208; break;
        case 2: // harvesting
            action_offset = 312; break;
    }
    int final_offset = action_offset + direction + 8 * (frame_offset - 1);
    ImageDraw::img_sprite(image_id_from_group(GROUP_FIGURE_WORKER_PH) + final_offset, x, y + 15, 0);
}
static void draw_farm_crops(building *b, int x, int y) {
    draw_ph_crops(b->type, b->data.industry.progress, b->grid_offset, x, y, 0);
}
static void draw_farm_workers(building *b, int grid_offset, int x, int y) {
    if (!building_is_floodplain_farm(b))
        return;
    int animation_offset = generic_sprite_offset(grid_offset, 13, 1);

    x += 60;
    y -= 30;
    if (b->num_workers > 0) {
        if (b->data.industry.progress < 400)
            draw_ph_worker(game_time_absolute_tick() % 128 / 16, 1, animation_offset, x + 30, y + 30);
        else if (b->data.industry.progress < 450)
            draw_ph_worker(1, 0, animation_offset, x + 60, y + 15);
        else if (b->data.industry.progress < 650)
            draw_ph_worker(2, 0, animation_offset, x + 90, y + 30);
        else if (b->data.industry.progress < 900)
            draw_ph_worker(3, 0, animation_offset, x + 0, y + 15);
        else if (b->data.industry.progress < 1100)
            draw_ph_worker(4, 0, animation_offset, x + 30, y + 30);
        else if (b->data.industry.progress < 1350)
            draw_ph_worker(5, 0, animation_offset, x + 60, y + 45);
        else if (b->data.industry.progress < 1550)
            draw_ph_worker(6, 0, animation_offset, x + -30, y + 30);
        else if (b->data.industry.progress < 1800)
            draw_ph_worker(0, 0, animation_offset, x + 0, y + 45);
        else if (b->data.industry.progress < 2000)
            draw_ph_worker(1, 0, animation_offset, x + 30, y + 60);
    }
}

/////// ORNAMENTS

static const int granary_offsets_ph[][2] = {
        {0, 0},
        {16, 9},
        {35, 18},
        {51, 26},
        {-16, 7},
        {1, 16},
        {20, 26},
        {37, 35},
};

static void draw_workshop_raw_material_storage(const building *b, int x, int y, color_t color_mask) {
    int image_base = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        image_base = image_id_from_group(GROUP_BUILDING_WORKSHOP_RAW_MATERIAL);
        switch (b->type) {
            case BUILDING_WINE_WORKSHOP:
                if (b->stored_full_amount >= 200 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base, x + 45, y + 23, color_mask);
                break;
            case BUILDING_OIL_WORKSHOP:
                if (b->stored_full_amount >= 200 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 1, x + 35, y + 15, color_mask);
                break;
            case BUILDING_WEAPONS_WORKSHOP:
                if (b->stored_full_amount >= 200 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 3, x + 46, y + 24, color_mask);
                break;
            case BUILDING_FURNITURE_WORKSHOP:
                if (b->stored_full_amount >= 200 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 2, x + 48, y + 19, color_mask);
                break;
            case BUILDING_POTTERY_WORKSHOP:
                if (b->stored_full_amount >= 200 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 4, x + 47, y + 24, color_mask);
                break;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        image_base = image_id_from_group(GROUP_EMPIRE_RESOURCES);
        switch (b->type) {
            case BUILDING_HUNTING_LODGE:
                if (b->stored_full_amount > 0)
                    ImageDraw::img_generic(image_base + ceil((float)b->stored_full_amount / 100.0) - 1, x + 61, y + 14, color_mask);
                break;
        }
    }
}
static void draw_granary_stores(const building *b, int x, int y, color_t color_mask) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 1, x, y + 60, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 2400)
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 2, x + 33, y - 60, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 1800)
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 3, x + 56, y - 50, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 1200)
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 4, x + 91, y - 50, color_mask);
        if (b->data.granary.resource_stored[RESOURCE_NONE] < 600)
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 5, x + 117, y - 62, color_mask);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int last_spot_filled = 0;
        int spot_x = 0;
        int spot_y = 0;
        for (int r = 1; r < 9; r++) {
            if (b->data.granary.resource_stored[r] > 0) {
                int spots_filled = ceil((float)(b->data.granary.resource_stored[r] - 199) / (float)400); // number of "spots" occupied by food
                if (spots_filled == 0 && b->data.granary.resource_stored[r] > 0)
                    spots_filled = 1;
                for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
                    // draw sprite on each granary "spot"
                    spot_x = granary_offsets_ph[spot][0];
                    spot_y = granary_offsets_ph[spot][1];
                    ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 2 + r, x + 110 + spot_x,
                                           y - 74 + spot_y,
                                           color_mask);
                }
                last_spot_filled += spots_filled;
            }
        }
    }
}
static void draw_warehouse_ornaments(const building *b, int x, int y, color_t color_mask) {
    ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_WAREHOUSE) + 17, x - 4, y - 42, color_mask);
    if (b->id == city_buildings_get_trade_center() && GAME_ENV == ENGINE_ENV_C3)
        ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_TRADE_CENTER_FLAG), x + 19, y - 56, color_mask);
}
static void draw_hippodrome_ornaments(int x, int y, int grid_offset) {
    int image_id = map_image_at(grid_offset);
    const image *img = image_get(image_id);
    building *b = building_at(grid_offset);
    if (img->num_animation_sprites
        && map_property_is_draw_tile(grid_offset)
        && b->type == BUILDING_HIPPODROME) {
        ImageDraw::img_generic(image_id + 1,
                               x + img->sprite_offset_x, y + img->sprite_offset_y - img->height + 90,
                               drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0
        );
    }
}
static void draw_senate_rating_flags(const building *b, int x, int y, color_t color_mask) {
    if (b->type == BUILDING_SENATE_UPGRADED) {
        // rating flags
        int image_id = image_id_from_group(GROUP_BUILDING_SENATE);
        ImageDraw::img_generic(image_id + 1, x + 138, y + 44 - city_rating_culture() / 2, color_mask);
        ImageDraw::img_generic(image_id + 2, x + 168, y + 36 - city_rating_prosperity() / 2, color_mask);
        ImageDraw::img_generic(image_id + 3, x + 198, y + 27 - city_rating_peace() / 2, color_mask);
        ImageDraw::img_generic(image_id + 4, x + 228, y + 19 - city_rating_favor() / 2, color_mask);
        // unemployed
        image_id = image_id_from_group(GROUP_FIGURE_HOMELESS);
        int unemployment_pct = city_labor_unemployment_percentage_for_senate();
        if (unemployment_pct > 0)
            ImageDraw::img_generic(image_id + 108, x + 80, y, color_mask);

        if (unemployment_pct > 5)
            ImageDraw::img_generic(image_id + 104, x + 230, y - 30, color_mask);

        if (unemployment_pct > 10)
            ImageDraw::img_generic(image_id + 107, x + 100, y + 20, color_mask);

        if (unemployment_pct > 15)
            ImageDraw::img_generic(image_id + 106, x + 235, y - 10, color_mask);

        if (unemployment_pct > 20)
            ImageDraw::img_generic(image_id + 106, x + 66, y + 20, color_mask);

    }
}

void draw_ornaments_and_animations(int x, int y, int grid_offset) {
    // tile must contain image draw data
    if (!map_property_is_draw_tile(grid_offset))
        return;

    int image_id = map_image_at(grid_offset);
    building *b = building_at(grid_offset);
    if (b->type == BUILDING_WAREHOUSE && b->state == BUILDING_STATE_CREATED)
        ImageDraw::img_generic(image_id + 17, x - 5, y - 42);
    if (b->type == 0 || b->state != BUILDING_STATE_VALID)
        return;
    // draw in red if necessary
    int color_mask = 0;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset))
        color_mask = COLOR_MASK_RED;

    switch (b->type) {
        case BUILDING_BURNING_RUIN:
            draw_normal_anim(x, y, b, grid_offset, image_id, color_mask);
            break;
        case BUILDING_GRANARY:
            draw_granary_stores(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, grid_offset, image_id + 5, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                draw_normal_anim(x + 114, y + 2, b, grid_offset, image_id_from_group(GROUP_GRANARY_ANIM_PH) - 1, color_mask);
            break;
        case BUILDING_WAREHOUSE:
            draw_warehouse_ornaments(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, grid_offset, image_id, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                draw_normal_anim(x + 21, y + 24, b, grid_offset, image_id_from_group(GROUP_WAREHOUSE_ANIM_PH) - 1, color_mask);
                ImageDraw::img_generic(image_id + 17, x - 5, y - 42, color_mask);
            }
            break;
        case BUILDING_DOCK:
            draw_dock_workers(b, x, y, color_mask);
            break;
        case BUILDING_GRAIN_FARM:
        case BUILDING_LETTUCE_FARM:
        case BUILDING_CHICKPEAS_FARM:
        case BUILDING_POMEGRANATES_FARM:
        case BUILDING_FIGS_FARM:
        case BUILDING_BARLEY_FARM:
        case BUILDING_FLAX_FARM:
        case BUILDING_HENNA_FARM:
            if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                draw_farm_crops(b, x, y);
                draw_farm_workers(b, grid_offset,x, y);
            }
            break;
        case BUILDING_WATER_LIFT:
            break; // todo
        case BUILDING_GOLD_MINE:
        case BUILDING_COPPER_MINE:
        case BUILDING_GEMSTONE_MINE:
            draw_normal_anim(x + 54, y + 15, b, grid_offset, image_id_from_group(GROUP_MINES) - 1, color_mask);
            break;
        case BUILDING_STONE_QUARRY:
        case BUILDING_LIMESTONE_QUARRY:
        case BUILDING_GRANITE_QUARRY:
        case BUILDING_SANDSTONE_QUARRY:
            break; // todo
        case BUILDING_MENU_FORTS:
            draw_fort_anim(x, y, b);
            break;
        case BUILDING_GATEHOUSE:
            draw_gatehouse_anim(x, y, b);
            break;
        case BUILDING_WELL:
            if (map_water_supply_is_well_unnecessary(b->id, 3) == WELL_NECESSARY) {
                const image *img = image_get(image_id_from_group(GROUP_BUILDING_WELL));
                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_WELL) + 1, x + img->sprite_offset_x,
                                       y + img->sprite_offset_y - 20, color_mask);
            }
            break;
        case BUILDING_BOOTH:
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_entertainment_shows_c3(b, x, y, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                if (grid_offset == b->grid_offset)
                    draw_entertainment_show_jugglers(b, x, y, color_mask);
            }
            break;
        case BUILDING_BANDSTAND:
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_entertainment_shows_c3(b, x, y, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                if (grid_offset == b->grid_offset && building_get(b->prev_part_building_id)->type != b->type)
                    draw_entertainment_shows_musicians(b, x, y, color_mask);
            }
            break;
        case BUILDING_PAVILLION:
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_entertainment_shows_c3(b, x, y, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                if (grid_offset == b->grid_offset + map_grid_delta(0, 1))
                    draw_entertainment_shows_dancers(b, x, y, color_mask);
            }
            break;
        case BUILDING_CONSERVATORY:
            draw_normal_anim(x + 82, y + 14, b, grid_offset, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1 + 12, color_mask);
            break;
        case BUILDING_DANCE_SCHOOL:
            draw_normal_anim(x + 104, y, b, grid_offset, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1, color_mask);
            break;
        default:
            draw_normal_anim(x, y, b, grid_offset, image_id, color_mask);
            if (b->ruin_has_plague)
                ImageDraw::img_generic(image_id_from_group(GROUP_PLAGUE_SKULL), x + 18, y - 32, color_mask);
            break;
    }

    // specific buildings
    draw_senate_rating_flags(b, x, y, color_mask);
    draw_workshop_raw_material_storage(b, x, y, color_mask);
//    draw_hippodrome_ornaments(x, y, grid_offset);
}