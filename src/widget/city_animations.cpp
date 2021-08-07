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
#include "city_animations.h"
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

static void draw_normal_anim(int x, int y, building *b, int sprite_id, int color_mask, int base_id = 0, int max_frames = 0) {
    if (!base_id)
        base_id = map_image_at(b->grid_offset);
    int animation_offset = building_animation_offset(b, base_id, b->grid_offset, max_frames);
    if (animation_offset == 0)
        return;
    int ydiff = 0;
    switch (map_property_multi_tile_size(b->grid_offset)) {
        case 1:
            ydiff = 30;
            break;
        case 2:
            ydiff = 45;
            break;
        case 3:
            ydiff = 60;
            break;
        case 4:
            ydiff = 75;
            break;
        case 5:
            ydiff = 90;
            break;
    }
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
        draw_normal_anim(x + 30, y + 15, b, image_id_from_group(GROUP_BUILDING_THEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_THEATER));
    }
}
static void draw_entertainment_shows_musicians(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();
    if (main->data.entertainment.days2) {
        building *next_tile = b->next();
        if (next_tile->type == BUILDING_BANDSTAND && next_tile->grid_offset == (b->grid_offset + 1))
            draw_normal_anim(x + 48, y + 12, b, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1 + 12,
                             color_mask, image_id_from_group(GROUP_BUILDING_COLOSSEUM), 12);
        else
            draw_normal_anim(x + 20, y + 12, b, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1,
                             color_mask, image_id_from_group(GROUP_BUILDING_COLOSSEUM), 12);
    }
}
static void draw_entertainment_shows_dancers(building *b, int x, int y, color_t color_mask) {
    building *main = b->main();
    if (main->data.entertainment.days3_or_play) {
        draw_normal_anim(x + 64, y, b, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1,
                         color_mask, image_id_from_group(GROUP_BUILDING_LION_HOUSE));
    }
}

/////// ORNAMENTS

static int granary_offsets_ph[][2] = {
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
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base, x + 45, y + 23, color_mask);
                break;
            case BUILDING_OIL_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 1, x + 35, y + 15, color_mask);
                break;
            case BUILDING_WEAPONS_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 3, x + 46, y + 24, color_mask);
                break;
            case BUILDING_FURNITURE_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 2, x + 48, y + 19, color_mask);
                break;
            case BUILDING_POTTERY_WORKSHOP:
                if (b->loads_stored >= 2 || b->data.industry.has_raw_materials)
                    ImageDraw::img_generic(image_base + 4, x + 47, y + 24, color_mask);
                break;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        image_base = image_id_from_group(GROUP_EMPIRE_RESOURCES);
        switch (b->type) {
            case BUILDING_HUNTING_LODGE:
                if (b->loads_stored > 0)
                    ImageDraw::img_generic(image_base + b->loads_stored - 1, x + 61, y + 14, color_mask);
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
    building *b = building_get(map_building_at(grid_offset));
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

void draw_animation(int x, int y, int grid_offset) {
    int image_id = map_image_at(grid_offset);
    building *b = building_get(map_building_at(grid_offset));
    if (b->type == BUILDING_WAREHOUSE && b->state == BUILDING_STATE_CREATED)
        ImageDraw::img_generic(image_id + 17, x - 5, y - 42);
    if (b->type == 0 || b->state != BUILDING_STATE_VALID)
        return;
    // draw in red if necessary
    int color_mask = 0;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset))
        color_mask = COLOR_MASK_RED;


    // TODO: bridges
    if (!map_property_is_draw_tile(grid_offset)) {
//    if (map_sprite_bridge_at(grid_offset))
//        city_draw_bridge(x, y, grid_offset);
        return;
    }


    switch (b->type) {
        case BUILDING_BURNING_RUIN:
            draw_normal_anim(x, y, b, image_id, color_mask);
            break;
        case BUILDING_GRANARY:
            draw_granary_stores(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, image_id + 5, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                draw_normal_anim(x + 114, y + 2, b, image_id_from_group(GROUP_GRANARY_ANIM_PH) - 1, color_mask);
            break;
        case BUILDING_WAREHOUSE:
            draw_warehouse_ornaments(b, x, y, color_mask);
            if (GAME_ENV == ENGINE_ENV_C3)
                draw_normal_anim(x + 77, y - 109, b, image_id, color_mask);
            else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                draw_normal_anim(x + 21, y + 24, b, image_id_from_group(GROUP_WAREHOUSE_ANIM_PH) - 1, color_mask);
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
//            draw_farm_crops(b, x, y);
            break;
        case BUILDING_WATER_LIFT:
            break; // todo
        case BUILDING_GOLD_MINE:
        case BUILDING_COPPER_MINE:
        case BUILDING_GEMSTONE_MINE:
            draw_normal_anim(x + 54, y + 15, b, image_id_from_group(GROUP_MINES) - 1, color_mask);
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
            draw_normal_anim(x + 82, y + 14, b, image_id_from_group(GROUP_BUILDING_COLOSSEUM_SHOW) - 1 + 12, color_mask);
            break;
        case BUILDING_DANCE_SCHOOL:
            draw_normal_anim(x + 104, y, b, image_id_from_group(GROUP_BUILDING_AMPHITHEATER_SHOW) - 1, color_mask);
            break;
        default:
            draw_normal_anim(x, y, b, image_id, color_mask);
            if (b->ruin_has_plague)
                ImageDraw::img_generic(image_id_from_group(GROUP_PLAGUE_SKULL), x + 18, y - 32, color_mask);
            break;
    }

    // specific buildings
    draw_senate_rating_flags(b, x, y, color_mask);
    draw_workshop_raw_material_storage(b, x, y, color_mask);
}