#include "ornaments.h"

#include "building/animation.h"
#include "building/building.h"
#include "building/dock.h"
#include "city/buildings.h"
#include "city/floods.h"
#include "city/labor.h"
#include "city/ratings.h"
#include "core/direction.h"
#include "game/time.h"
#include "graphics/boilerplate.h"
#include "graphics/image.h"
#include "grid/floodplain.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include <cmath>

static bool drawing_building_as_deleted(building* b) {
    b = b->main();
    if (b->id && (b->is_deleted || map_property_is_deleted(b->tile.grid_offset())))
        return true;

    return false;
}

/////// ANIMATIONS

static void draw_normal_anim(int x,
                             int y,
                             building* b,
                             int grid_offset,
                             int sprite_id,
                             int color_mask,
                             int base_id = 0,
                             int max_frames = 0) {
    if (!base_id)
        base_id = map_image_at(grid_offset);
    int animation_offset = building_animation_offset(b, base_id, grid_offset, max_frames);
    if (animation_offset == 0)
        return;

    if (base_id == sprite_id)
        ImageDraw::img_ornament(sprite_id + animation_offset, base_id, x, y, color_mask);
    else
        ImageDraw::img_sprite(sprite_id + animation_offset, x, y, color_mask);
}
static void draw_water_lift_anim(building* b, int x, int y, color color_mask) {
    int orientation_rel = city_view_relative_orientation(b->data.industry.orientation);
    int anim_offset = 13 * orientation_rel;
    x += 53;
    y += 15;

    switch (orientation_rel) {
    case 1:
        y -= 2;
        break;
    case 2:
        x += 10;
        y += 0;
        break;
    case 3:
        x += 14;
        y += 6;
        break;
    }

    draw_normal_anim(x, y, b, b->tile.grid_offset(), image_id_from_group(GROUP_WATER_LIFT_ANIM) - 1 + anim_offset, color_mask);
}
static void draw_fort_anim(int x, int y, building* b) {
    if (map_property_is_draw_tile(b->tile.grid_offset())) {
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
            ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_FORT) + offset, x + 81, y + 5, drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0);
    }
}

static void draw_gatehouse_anim(int x, int y, building* b) {
    int xy = map_property_multi_tile_xy(b->tile.grid_offset());
    int orientation = city_view_orientation();
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) || (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1)
        || (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0)
        || (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
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

static void draw_entertainment_shows_c3(building* b, int x, int y, color color_mask) {
    //    if (b->type == BUILDING_AMPHITHEATER && b->num_workers > 0)
    //        ImageDraw::img_generic(image_id_from_group(GROUP_DANCERS_SHOW), x + 36, y - 47, color_mask);
    //
    //    if (b->type == BUILDING_THEATER && b->num_workers > 0)
    //        ImageDraw::img_generic(image_id_from_group(GROUP_JUGGLERS_SHOW), x + 34, y - 22, color_mask);
    //
    //    if (b->type == BUILDING_COLOSSEUM && b->num_workers > 0)
    //        ImageDraw::img_generic(image_id_from_group(GROUP_MUSICIANS_SHOW), x + 70, y - 90, color_mask);
    //
    //    if (b->type == BUILDING_HIPPODROME && b->main()->num_workers > 0 &&
    //        city_entertainment_hippodrome_has_race())
    //        draw_hippodrome_spectators(b, x, y, color_mask);
}

static void draw_entertainment_show_jugglers(building* b, int x, int y, color color_mask) {
    building* main = b->main();
    if (main->data.entertainment.days1) {
        draw_normal_anim(x + 30, y + 15, b, b->tile.grid_offset(), image_id_from_group(GROUP_JUGGLERS_SHOW_ALONE) - 1, color_mask, image_id_from_group(GROUP_BUILDING_BOOTH));
    }
}

static void draw_entertainment_shows_musicians(building* b, int x, int y, int direction, color color_mask) {
    building* main = b->main();
    if (main->data.entertainment.days2) {
        building* next_tile = b->next();
        switch (direction) {
        case 0:
            draw_normal_anim(x + 20, y + 12, b, b->tile.grid_offset(), image_id_from_group(GROUP_MUSICIANS_SHOW1) - 1, color_mask, image_id_from_group(GROUP_BUILDING_BANDSTAND), 12);
            break;
        case 1:
            draw_normal_anim(x + 48, y + 12, b, b->tile.grid_offset(), image_id_from_group(GROUP_MUSICIANS_SHOW2) - 1 + 12, color_mask, image_id_from_group(GROUP_BUILDING_BANDSTAND), 12);
            break;
        }
    }
}

static void draw_entertainment_shows_dancers(building* b, int x, int y, color color_mask) {
    building* main = b->main();
    if (main->data.entertainment.days3_or_play) {
        draw_normal_anim(x + 64, y, b, b->tile.grid_offset(), image_id_from_group(GROUP_DANCERS_SHOW) - 1, color_mask, image_id_from_group(GROUP_BUILDING_PAVILLION));
    }
}

static const vec2i FARM_TILE_OFFSETS_FLOODPLAIN[9] = {{60, 0}, {90, 15}, {120, 30}, {30, 15}, {60, 30}, {90, 45}, {0, 30}, {30, 45}, {60, 60}};
static const int FARM_TILE_OFFSETS_MEADOW[5][2] = {{0, 30}, {30, 45}, {60, 60}, {90, 45}, {120, 30}};

static vec2i farm_tile_coords(vec2i pos, int tile_x, int tile_y) {
    int tile_id = 3 * abs(tile_y) + abs(tile_x);
    return pos + FARM_TILE_OFFSETS_FLOODPLAIN[tile_id];
}

int get_farm_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        int base = image_id_from_group(GROUP_BUILDING_FARMLAND);
        int fert_average = map_get_fertility_for_farm(grid_offset);
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
    } else {
        return image_id_from_group(GROUP_BUILDING_FARM_HOUSE);
    }
}

int get_crops_image(e_building_type type, int growth) {
    int base = 0;
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    base = image_id_from_group(GROUP_BUILDING_FARMLAND);
    //    return (type - BUILDING_BARLEY_FARM) * 5 + growth;
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
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
    
    return image_id_from_group(GROUP_BUILDING_FARM_CROPS_PH) + (type - BUILDING_BARLEY_FARM) * 6; // temp
}

void draw_farm_crops(e_building_type type, int progress, int grid_offset, vec2i tile, color color_mask) {
    int image_crops = get_crops_image(type, 0);
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) { // on floodplains - all
        for (int i = 0; i < 9; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 200) / 100));
            ImageDraw::img_from_below(image_crops + growth_offset, tile.x + FARM_TILE_OFFSETS_FLOODPLAIN[i].x, tile.y + FARM_TILE_OFFSETS_FLOODPLAIN[i].y, color_mask);
        }
    } else { // on dry meadows
        for (int i = 0; i < 5; i++) {
            int growth_offset = fmin(5, fmax(0, (progress - i * 400) / 100));

            ImageDraw::img_from_below(image_crops + growth_offset, tile.x + FARM_TILE_OFFSETS_MEADOW[i][0], tile.y + FARM_TILE_OFFSETS_MEADOW[i][1], color_mask);
        }
    }
}

enum e_farm_worker_state {
    FARM_WORKER_TILING,
    FARM_WORKER_SEEDING,
    FARM_WORKER_HARVESTING
};

static void draw_farm_worker(int direction,
                           int action,
                           int frame_offset,
                           vec2i coords,
                           color color_mask = COLOR_MASK_NONE) {
    int action_offset = 0;
    switch (action) {
    case FARM_WORKER_TILING: // tiling
        action_offset = 104;
        break;
    case FARM_WORKER_SEEDING: // seeding
        action_offset = 208;
        break;
    case FARM_WORKER_HARVESTING: // harvesting
        coords.y += 10;
        action_offset = 312;
        break;
    }
    int final_offset = action_offset + direction + 8 * (frame_offset - 1);
    ImageDraw::img_sprite(image_id_from_group(GROUP_FIGURE_WORKER_PH) + final_offset, coords.x, coords.y, color_mask);
}

static void draw_farm_workers(building* b, int grid_offset, vec2i pos) {
    if (b->num_workers == 0) {
        return;
    }

    pos += {30, -15};
    int animation_offset = 0;
    int random_seed = 1234.567f * (1 + game_time_day()) * map_random_get(b->tile.grid_offset());
    int d = random_seed % 8;
    if (building_is_floodplain_farm(b)) {
        if (floodplains_is(FLOOD_STATE_IMMINENT)) {
            //int random_x = random_seed % 3;
            //int random_y = int(1234.567f * random_seed) % 3;
            //auto coords = farm_tile_coords(x, y, random_x, random_y);
            //draw_ph_worker(d, 2, animation_offset, coords);
        } else {
            animation_offset = generic_sprite_offset(grid_offset, 13, 1);
            if (b->data.industry.progress < 400)
                draw_farm_worker(game_time_absolute_tick() % 128 / 16, 1, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 500)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 1, 0));
            else if (b->data.industry.progress < 600)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 0));
            else if (b->data.industry.progress < 700)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 0, 1));
            else if (b->data.industry.progress < 800)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 900)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 1));
            else if (b->data.industry.progress < 1000)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 0, 2));
            else if (b->data.industry.progress < 1100)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 1, 2));
            else if (b->data.industry.progress < 1200)
                draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 2));
            else if (b->data.industry.progress < 1300)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 1, 0));
            else if (b->data.industry.progress < 1400)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 2, 0));
            else if (b->data.industry.progress < 1500)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 0, 1));
            else if (b->data.industry.progress < 1600)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 1, 1));
            else if (b->data.industry.progress < 1700)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 2, 1));
            else if (b->data.industry.progress < 1800)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 0, 2));
            else if (b->data.industry.progress < 1900)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 1, 2));
            else if (b->data.industry.progress < 2000)
                draw_farm_worker(d, 2, animation_offset, farm_tile_coords(pos, 2, 2));
        }
    } else {
        animation_offset = generic_sprite_offset(grid_offset, 13, 1);
        if (b->data.industry.progress < 100)
            draw_farm_worker(game_time_absolute_tick() % 128 / 16, 1, animation_offset, farm_tile_coords(pos, 1, 1));
        else if (b->data.industry.progress < 400)
            draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 0, 2));
        else if (b->data.industry.progress < 800)
            draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 1, 2));
        else if (b->data.industry.progress < 1200)
            draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 2));
        else if (b->data.industry.progress < 1600)
            draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 1));
        else if (b->data.industry.progress < 2000)
            draw_farm_worker(d, 0, animation_offset, farm_tile_coords(pos, 2, 0));
    }
}

static void draw_dock_workers(building* b, int x, int y, color color_mask) {
    int num_dockers = building_dock_count_idle_dockers(b);
    if (num_dockers > 0) {
        int image_dock = map_image_at(b->tile.grid_offset());
        int image_dockers = image_id_from_group(GROUP_BUILDING_DOCK_DOCKERS);
        if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK))
            image_dockers += 0;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK) + 1)
            image_dockers += 3;
        else if (image_dock == image_id_from_group(GROUP_BUILDING_DOCK) + 2)
            image_dockers += 6;
        else
            image_dockers += 9;

        if (num_dockers == 2)
            image_dockers += 1;
        else if (num_dockers == 3)
            image_dockers += 2;

        const image_t* img = image_get(image_dockers);
        ImageDraw::img_generic(image_dockers, x + img->animation.sprite_x_offset, y + img->animation.sprite_y_offset, color_mask);
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

static void draw_workshop_raw_material_storage(const building* b, int x, int y, color color_mask) {
    if (b->stored_full_amount <= 0)
        return;
    int amount = ceil((float)b->stored_full_amount / 100.0) - 1;
    switch (b->type) {
    case BUILDING_HUNTING_LODGE:
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_GAMEMEAT_5) + amount,
                               x + 61,
                               y + 14,
                               color_mask);
        break;
    case BUILDING_POTTERY_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_CLAY_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_BEER_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_BARLEY_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_PAPYRUS_WORKSHOP:
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_REEDS_5) + amount, x + 35, y + 4, color_mask);
        break;
    case BUILDING_WOOD_CUTTERS:
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3, color_mask);
        break;
    case BUILDING_LINEN_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_FLAX_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_JEWELS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_GEMS_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_SHIPYARD:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_WEAPONS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_COPPER_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_CHARIOTS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;
    case BUILDING_CHARIOT_MAKER:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_CHARIOTS_2) + amount, x + 65, y +
        //            3, color_mask);
        break;
    }
}
static void draw_granary_stores(const building* b, int x, int y, color color_mask) {
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
                int spots_filled = ceil((float)(b->data.granary.resource_stored[r] - 199)
                                        / (float)400); // number of "spots" occupied by food
                if (spots_filled == 0 && b->data.granary.resource_stored[r] > 0)
                    spots_filled = 1;
                for (int spot = last_spot_filled; spot < last_spot_filled + spots_filled; spot++) {
                    // draw sprite on each granary "spot"
                    spot_x = granary_offsets_ph[spot][0];
                    spot_y = granary_offsets_ph[spot][1];
                    ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_GRANARY) + 2 + r, x + 110 + spot_x, y - 74 + spot_y, color_mask);
                }
                last_spot_filled += spots_filled;
            }
        }
    }
}
static void draw_storageyard_ornaments(const building* b, int x, int y, color color_mask) {
    ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_STORAGE_YARD) + 17, x - 5, y - 42, color_mask);
    //if (b->id == city_buildings_get_trade_center() && GAME_ENV == ENGINE_ENV_C3)
    //    ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_TRADE_CENTER_FLAG), x + 19, y - 56, color_mask);
}
static void draw_hippodrome_ornaments(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int image_id = map_image_at(grid_offset);
    const image_t* img = image_get(image_id);
    building* b = building_at(grid_offset);
    if (img->animation.num_sprites && map_property_is_draw_tile(grid_offset) && b->type == BUILDING_SENET_HOUSE) {
        ImageDraw::img_generic(image_id + 1, x + img->animation.sprite_x_offset, y + img->animation.sprite_y_offset - img->height + 90, drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0);
    }
}

static void draw_palace_rating_flags(const building* b, int x, int y, color color_mask) {
    if (b->type == BUILDING_GREATE_PALACE || b->type == BUILDING_GREATE_PALACE_UPGRADED) {
        // rating flags
        int image_id = image_id_from_group(GROUP_BUILDING_PALACE);
        ImageDraw::img_generic(image_id + 1, x + 138, y + 44 - city_rating_culture() / 2, color_mask);
        ImageDraw::img_generic(image_id + 2, x + 168, y + 36 - city_rating_prosperity() / 2, color_mask);
        ImageDraw::img_generic(image_id + 3, x + 198, y + 27 - city_rating_monument() / 2, color_mask);
        ImageDraw::img_generic(image_id + 4, x + 228, y + 19 - city_rating_kingdom() / 2, color_mask);
        // unemployed
        image_id = image_id_from_group(GROUP_FIGURE_VAGRANT);
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

void draw_ornaments_and_animations(vec2i tile, map_point point) {
    int grid_offset = point.grid_offset();
    int x = tile.x;
    int y = tile.y;
    // tile must contain image draw data
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    int image_id = map_image_at(grid_offset);
    building* b = building_at(grid_offset);
    if (b->type == BUILDING_STORAGE_YARD && b->state == BUILDING_STATE_CREATED) {
        ImageDraw::img_generic(image_id + 17, x - 5, y - 42);
    }

    if (b->type == 0 || b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    // draw in red if necessary
    int color_mask = 0;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset)) {
        color_mask = COLOR_MASK_RED;
    }

    switch (b->type) {
    case BUILDING_BURNING_RUIN:
        draw_normal_anim(x, y, b, grid_offset, image_id, color_mask);
        break;

    case BUILDING_GRANARY:
        draw_granary_stores(b, x, y, color_mask);
        draw_normal_anim(x + 114, y + 2, b, grid_offset, image_id_from_group(GROUP_GRANARY_ANIM_PH) - 1, color_mask);
        break;

    case BUILDING_STORAGE_YARD:
        draw_storageyard_ornaments(b, x, y, color_mask);
        draw_normal_anim(x + 21, y + 24, b, grid_offset, image_id_from_group(GROUP_WAREHOUSE_ANIM_PH) - 1, color_mask);
        ImageDraw::img_generic(image_id + 17, x - 5, y - 42, color_mask);
        break;

    case BUILDING_DOCK:
        draw_dock_workers(b, x, y, color_mask);
        break;

    case BUILDING_GRAIN_FARM:
    case BUILDING_LETTUCE_FARM:
    case BUILDING_CHICKPEAS_FARM:
    case BUILDING_POMEGRANATES_FARM:
    case BUILDING_BARLEY_FARM:
    case BUILDING_FLAX_FARM:
    case BUILDING_HENNA_FARM:
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            draw_farm_crops(b->type, b->data.industry.progress, b->tile.grid_offset(), tile, color_mask);
            draw_farm_workers(b, grid_offset, tile);
        }
        break;

    case BUILDING_FIGS_FARM:
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            draw_farm_crops(b->type, b->data.industry.progress, b->tile.grid_offset(), tile, color_mask);
            draw_farm_workers(b, grid_offset, tile);
        }
        break;

    case BUILDING_WATER_LIFT:
        draw_water_lift_anim(b, x, y, color_mask);
        break;

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
        //        case BUILDING_WELL:
        //            if (map_water_supply_is_well_unnecessary(b->id, 3) == WELL_NECESSARY) {
        //                draw_normal_anim(x, y + 20, b, grid_offset, image_id_from_group(GROUP_BUILDING_WELL) + 1,
        //                color_mask);
        ////                const image *img = image_get(image_id_from_group(GROUP_BUILDING_WELL));
        ////                ImageDraw::img_generic(image_id_from_group(GROUP_BUILDING_WELL) + 1, x +
        /// img->animation.sprite_x_offset, /                                       y + img->animation.sprite_y_offset -
        /// 20, color_mask); /                ImageDraw::img_ornament(image_id_from_group(GROUP_BUILDING_WELL) + 1, x, /
        /// y - 20, color_mask);
        //            }
        //            break;
    case BUILDING_BOOTH:
        if (map_image_at(grid_offset) == image_id_from_group(GROUP_BUILDING_BOOTH)) {
            draw_entertainment_show_jugglers(b, x, y, color_mask);
        }
        break;

    case BUILDING_BANDSTAND:
        if (map_image_at(grid_offset) == image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1) {
            draw_entertainment_shows_musicians(b, x, y, 0, color_mask);
        } else if (map_image_at(grid_offset) == image_id_from_group(GROUP_BUILDING_BANDSTAND) + 2) {
            draw_entertainment_shows_musicians(b, x, y, 1, color_mask);
        }
        break;

    case BUILDING_PAVILLION:
        if (map_image_at(grid_offset) == image_id_from_group(GROUP_BUILDING_PAVILLION)) {
            draw_entertainment_shows_dancers(b, x, y, color_mask);
        }
        break;

    case BUILDING_CONSERVATORY:
        draw_normal_anim(x + 82, y + 14, b, grid_offset, image_id_from_group(GROUP_MUSICIANS_SHOW1) - 1, color_mask);
        break;

    case BUILDING_DANCE_SCHOOL:
        draw_normal_anim(x + 104, y, b, grid_offset, image_id_from_group(GROUP_DANCERS_SHOW) - 1, color_mask);
        break;

    default:
        draw_normal_anim(x, y, b, grid_offset, image_id, color_mask);
        if (b->ruin_has_plague) {
            ImageDraw::img_generic(image_id_from_group(GROUP_PLAGUE_SKULL), x + 18, y - 32, color_mask);
        }
        break;
    }

    // specific buildings
    draw_palace_rating_flags(b, x, y, color_mask);
    draw_workshop_raw_material_storage(b, x, y, color_mask);
    //    draw_hippodrome_ornaments(pixel, point);
}