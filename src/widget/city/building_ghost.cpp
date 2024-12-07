#include "building_ghost.h"

#include "grid/routing/routing.h"
#include "building/construction/build_planner.h"
#include "building/building_booth.h"
#include "building/building_bandstand.h"
#include "building/building_pavilion.h"
#include "building/building_farm.h"
#include "building/building_fishing_wharf.h"
#include "building/building_festival_square.h"
#include "building/building_storage_yard.h"
#include "building/building_road.h"
#include "building/building_well.h"
#include "building/industry.h"
#include "building/monument_mastaba.h"
#include "building/rotation.h"
#include "building/building_fort.h"
#include "building/building.h"
#include "building/count.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "grid/bridge.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/image_context.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/road_canal.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "config/config.h"
#include "ornaments.h"
#include "game/game.h"
#include "widget/city/bridges.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"

#include <cmath>

#define MAX_TILES 25

const vec2i VIEW_OFFSETS[]          = {          {0, 0},
                                       {-30,15}, {30, 15}, {0,30},
                             {-60,30}, {60, 30}, {-30,45}, {30, 45}, {0,  60},
                  {-90, 45}, {90, 45}, {-60,60}, {60, 60}, {-30,75}, {30, 75},  {0, 90},
       {-120,60}, {120, 60}, {-90,75}, {90, 75}, {-60,90}, {60, 90}, {-30,105}, {30,105}, {0,120}};

// #define OFFSET(x,y) (x + GRID_SIZE_PH * y)

static const int TILE_GRID_OFFSETS_PH[4][MAX_TILES] = {
  {GRID_OFFSET(0, 0), GRID_OFFSET(0, 1), GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(0, 2),
   GRID_OFFSET(2, 0), GRID_OFFSET(1, 2), GRID_OFFSET(2, 1), GRID_OFFSET(2, 2), GRID_OFFSET(0, 3),
   GRID_OFFSET(3, 0), GRID_OFFSET(1, 3), GRID_OFFSET(3, 1), GRID_OFFSET(2, 3), GRID_OFFSET(3, 2),
   GRID_OFFSET(3, 3), GRID_OFFSET(0, 4), GRID_OFFSET(4, 0), GRID_OFFSET(1, 4), GRID_OFFSET(4, 1),
   GRID_OFFSET(2, 4), GRID_OFFSET(4, 2), GRID_OFFSET(3, 4), GRID_OFFSET(4, 3), GRID_OFFSET(4, 4)},
  {GRID_OFFSET(0, 0),  GRID_OFFSET(-1, 0), GRID_OFFSET(0, 1),  GRID_OFFSET(-1, 1), GRID_OFFSET(-2, 0),
   GRID_OFFSET(0, 2),  GRID_OFFSET(-2, 1), GRID_OFFSET(-1, 2), GRID_OFFSET(-2, 2), GRID_OFFSET(-3, 0),
   GRID_OFFSET(0, 3),  GRID_OFFSET(-3, 1), GRID_OFFSET(-1, 3), GRID_OFFSET(-3, 2), GRID_OFFSET(-2, 3),
   GRID_OFFSET(-3, 3), GRID_OFFSET(-4, 0), GRID_OFFSET(0, 4),  GRID_OFFSET(-4, 1), GRID_OFFSET(-1, 4),
   GRID_OFFSET(-4, 2), GRID_OFFSET(-2, 4), GRID_OFFSET(-4, 3), GRID_OFFSET(-3, 4), GRID_OFFSET(-4, 4)},
  {GRID_OFFSET(0, 0),   GRID_OFFSET(0, -1),  GRID_OFFSET(-1, 0),  GRID_OFFSET(-1, -1), GRID_OFFSET(0, -2),
   GRID_OFFSET(-2, 0),  GRID_OFFSET(-1, -2), GRID_OFFSET(-2, -1), GRID_OFFSET(-2, -2), GRID_OFFSET(0, -3),
   GRID_OFFSET(-3, 0),  GRID_OFFSET(-1, -3), GRID_OFFSET(-3, -1), GRID_OFFSET(-2, -3), GRID_OFFSET(-3, -2),
   GRID_OFFSET(-3, -3), GRID_OFFSET(0, -4),  GRID_OFFSET(-4, 0),  GRID_OFFSET(-1, -4), GRID_OFFSET(-4, -1),
   GRID_OFFSET(-2, -4), GRID_OFFSET(-4, -2), GRID_OFFSET(-3, -4), GRID_OFFSET(-4, -3), GRID_OFFSET(-4, -4)},
  {GRID_OFFSET(0, 0),  GRID_OFFSET(1, 0),  GRID_OFFSET(0, -1), GRID_OFFSET(1, -1), GRID_OFFSET(2, 0),
   GRID_OFFSET(0, -2), GRID_OFFSET(2, -1), GRID_OFFSET(1, -2), GRID_OFFSET(2, -2), GRID_OFFSET(3, 0),
   GRID_OFFSET(0, -3), GRID_OFFSET(3, -1), GRID_OFFSET(1, -3), GRID_OFFSET(3, -2), GRID_OFFSET(2, -3),
   GRID_OFFSET(3, -3), GRID_OFFSET(4, 0),  GRID_OFFSET(0, -4), GRID_OFFSET(4, -1), GRID_OFFSET(1, -4),
   GRID_OFFSET(4, -2), GRID_OFFSET(2, -4), GRID_OFFSET(4, -3), GRID_OFFSET(3, -4), GRID_OFFSET(4, -4)},
};

static const int RESERVOIR_GRID_OFFSETS_PH[4] = {GRID_OFFSET(-1, -1), GRID_OFFSET(1, -1), GRID_OFFSET(1, 1), GRID_OFFSET(-1, 1)};

static const int HIPPODROME_X_VIEW_OFFSETS[4] = {150, 150, -150, -150};
static const int HIPPODROME_Y_VIEW_OFFSETS[4] = {75, -75, -75, 75};

#define RESERVOIR_RANGE_MAX_TILES 520

struct reservoir_range_data_t {
    int total;
    int save_offsets;
    int offsets[RESERVOIR_RANGE_MAX_TILES];
    int last_grid_offset;
};

reservoir_range_data_t reservoir_range_data;

static int get_building_image_id(int map_x, int map_y, int type) {
    const auto &props = building_impl::params((e_building_type)type);
    int image_id = props.anim["base"].first_img();
    if (type == BUILDING_MUD_GATEHOUSE) {
        int orientation = map_orientation_for_gatehouse(map_x, map_y);
        int image_offset;
        if (orientation == 2)
            image_offset = 1;
        else if (orientation == 1)
            image_offset = 0;
        else {
            image_offset = building_rotation_get_road_orientation() == 2 ? 1 : 0;
        }
        int map_orientation = city_view_orientation();
        if (map_orientation == DIR_6_TOP_LEFT || map_orientation == DIR_2_BOTTOM_RIGHT)
            image_offset = 1 - image_offset;

        image_id += image_offset;
    } else if (type == BUILDING_RESERVED_TRIUMPHAL_ARCH_56) {
        int orientation = map_orientation_for_triumphal_arch(map_x, map_y);
        int image_offset;
        if (orientation == 2)
            image_offset = 2;
        else if (orientation == 1)
            image_offset = 0;
        else {
            image_offset = building_rotation_get_road_orientation() == 2 ? 2 : 0;
        }
        int map_orientation = city_view_orientation();
        if (map_orientation == DIR_6_TOP_LEFT || map_orientation == DIR_2_BOTTOM_RIGHT)
            image_offset = 2 - image_offset;

        image_id += image_offset;
    }
    return image_id;
}

static void get_building_base_xy(int map_x, int map_y, int building_size, int* x, int* y) {
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        *x = map_x;
        *y = map_y;
        break;
    case DIR_2_BOTTOM_RIGHT:
        *x = map_x - building_size + 1;
        *y = map_y;
        break;
    case DIR_4_BOTTOM_LEFT:
        *x = map_x - building_size + 1;
        *y = map_y - building_size + 1;
        break;
    case DIR_6_TOP_LEFT:
        *x = map_x;
        *y = map_y - building_size + 1;
        break;
    default:
        *x = *y = 0;
    }
}

int is_blocked_for_farm(tile2i tile, int size, blocked_tile_vec &blocked_tiles) {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    int num_tiles = (size * size);
    for (int i = 0; i < num_tiles; i++) {
        const int offset = TILE_GRID_OFFSETS_PH[orientation_index][i];
        tile2i check_tile = tile.shifted(offset);
        bool tile_blocked = !map_terrain_is(check_tile, TERRAIN_FLOODPLAIN)
                            || (map_building_at(check_tile) != 0)
                            || map_has_figure_at(check_tile);

        blocked_tiles.push_back({ check_tile, tile_blocked });
        blocked += (tile_blocked ? 1 : 0);
    }
    return blocked;
}

int is_blocked_for_building(tile2i tile, int size, blocked_tile_vec &blocked_tiles) {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    int num_tiles = (size * size);
    for (int i = 0; i < num_tiles; i++) {
        int offset = TILE_GRID_OFFSETS_PH[orientation_index][i];
        tile2i check_tile = tile.shifted(offset);
        bool tile_blocked = map_terrain_is(check_tile, TERRAIN_NOT_CLEAR)
                            || (map_terrain_count_directly_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
                            || (map_terrain_count_diagonally_adjacent_with_type(check_tile, TERRAIN_FLOODPLAIN) > 0)
                            || map_has_figure_at(check_tile);

        blocked_tiles.push_back({check_tile, tile_blocked});
        blocked += (tile_blocked ? 1 : 0);
    }
    return blocked;
}

void draw_partially_blocked(painter &ctx, int fully_blocked, const blocked_tile_vec &blocked_tiles) {
    for (auto &tile : blocked_tiles) {
        vec2i pixel = tile_to_pixel(tile.tile);
        draw_flat_tile(ctx, pixel, (fully_blocked || tile.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30);
    }
}

void draw_flat_tile(painter &ctx, vec2i pixel, color color_mask) {
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel.x, pixel.y, color_mask);
}

void draw_building_ghost(painter &ctx, e_image_id image_id, vec2i tile, color color_mask) {
    int img = image_group(image_id);
    ImageDraw::isometric(ctx, img, tile, color_mask);
}

void draw_building_ghost(painter &ctx, int image_id, vec2i pixel, color color_mask) {
    ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, color_mask);
    ImageDraw::isometric_from_drawtile_top(ctx, image_id, pixel, color_mask, 1.f);
}

static void draw_canal(map_point tile, vec2i pixel, painter &ctx) {
    int grid_offset = tile.grid_offset();
    bool blocked = false;
    if (!map_can_place_initial_road_or_aqueduct(grid_offset, true)) {
        blocked = true;
    }
    if (Planner.in_progress) {   // already dragging aqueduct
        if (!Planner.total_cost) // ???
            blocked = true;
    } else {
        if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {               // starting new aqueduct line
            blocked = !map_is_straight_road_for_canal(grid_offset); // can't start over a road curve!
            if (map_property_is_plaza_or_earthquake(grid_offset))      // todo: plaza not allowing aqueducts? maybe?
                blocked = true;
        } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
                   && !map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {// terrain is not clear!
            blocked = true;
        }
    }
    if (city_finance_out_of_money()) { // check sufficient funds to continue
        blocked = true;
    }

    if (blocked) { // cannot draw!
        draw_flat_tile(ctx, pixel, COLOR_MASK_RED);
    } else {
        const terrain_image* img = map_image_context_get_canal(grid_offset); // get starting tile
        draw_building_ghost(ctx, get_canal_image(grid_offset, map_terrain_is(grid_offset, TERRAIN_ROAD), 0, img), pixel);
    }
}

static void draw_bridge(map_point tile, vec2i pixel, int type, painter &ctx) {
    int length, direction;
    int end_grid_offset = map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction);

    int dir = direction - city_view_orientation();
    if (dir < 0)
        dir += 8;

    bool blocked = false;
    if (type == BUILDING_UNUSED_SHIP_BRIDGE_83 && length < 5)
        blocked = true;
    else if (!end_grid_offset)
        blocked = true;

    if (city_finance_out_of_money())
        blocked = true;

    int x_delta, y_delta;
    switch (dir) {
    case DIR_0_TOP_RIGHT:
        x_delta = 29;
        y_delta = -15;
        break;
    case DIR_2_BOTTOM_RIGHT:
        x_delta = 29;
        y_delta = 15;
        break;
    case DIR_4_BOTTOM_LEFT:
        x_delta = -29;
        y_delta = 15;
        break;
    case DIR_6_TOP_LEFT:
        x_delta = -29;
        y_delta = -15;
        break;
    default:
        return;
    }
    if (blocked) {
        draw_flat_tile(ctx, pixel, length > 0 ? COLOR_MASK_GREEN : COLOR_MASK_RED);
        if (length > 1)
            draw_flat_tile(ctx, pixel + vec2i(x_delta * (length - 1), y_delta * (length - 1)), COLOR_MASK_RED);

    } else {
        if (dir == DIR_0_TOP_RIGHT || dir == DIR_6_TOP_LEFT) {
            for (int i = length - 1; i >= 0; i--) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        } else {
            for (int i = 0; i < length; i++) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_UNUSED_SHIP_BRIDGE_83);
                city_draw_bridge_tile(ctx, pixel.x + x_delta * i, pixel.y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        }
    }
}

static void draw_entertainment_venue(tile2i tile, vec2i pixel, e_building_type type, painter &ctx) {
    int can_build = 0;

    int size = building_impl::params(type).building_size;
    int orientation = 0;

    switch (type) {
    case BUILDING_BOOTH:
        can_build = map_orientation_for_venue_with_map_orientation(tile, e_venue_mode_booth, &orientation);
        break;
    case BUILDING_BANDSTAND:
        can_build = map_orientation_for_venue_with_map_orientation(tile, e_venue_mode_bandstand, &orientation);
        break;
    case BUILDING_PAVILLION:
        can_build = map_orientation_for_venue_with_map_orientation(tile, e_venue_mode_pavilion, &orientation);
        break;
    case BUILDING_FESTIVAL_SQUARE:
        can_build = map_orientation_for_venue_with_map_orientation(tile, e_venue_mode_festival_square, &orientation);
        break;
    }
    // TODO: proper correct for map orientation (for now, just use a different orientation)
    orientation = abs(orientation + (8 - city_view_orientation())) % 8;

    if (can_build != 1) { // no can place
        for (int i = 0; i < size * size; i++) {
            draw_flat_tile(ctx, pixel + VIEW_OFFSETS[i], COLOR_MASK_RED);
        }
    } else { // can place (theoretically)
        switch (type) {
        case BUILDING_BOOTH:
            building_booth::ghost_preview(ctx, tile, pixel, orientation);
            break;

        case BUILDING_BANDSTAND:
            building_bandstand::ghost_preview(ctx, tile, pixel, orientation);
            break;

        case BUILDING_PAVILLION:
            building_pavilion::ghost_preview(ctx, tile, pixel, orientation);
            break;

        case BUILDING_FESTIVAL_SQUARE:
            building_festival_square::ghost_preview(ctx, tile, pixel, orientation);            
            break;
        }
    }
}

bool city_building_ghost_mark_deleting(tile2i tile) {
    if (!config_get(CONFIG_UI_VISUAL_FEEDBACK_ON_DELETE)) {
        return false;
    }

    int construction_type = Planner.build_type;
    if (!tile.grid_offset() || Planner.draw_as_constructing || construction_type != BUILDING_CLEAR_LAND) {
        return (construction_type == BUILDING_CLEAR_LAND);
    }

    if (!Planner.in_progress) {
        map_property_clear_constructing_and_deleted();
    }

    map_building_tiles_mark_deleting(tile.grid_offset());
    return true;
}

void BuildPlanner::draw_flat_tile(vec2i pos, color color_mask, painter &ctx) {
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pos.x, pos.y, color_mask);
}

void BuildPlanner::draw_blueprints(painter &ctx, bool fully_blocked) {
    vec2i pixel = pixel_coords_cache[0][0];
    switch (build_type) {
    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        building_fort::ghost_preview(ctx, end, pixel, 0);
        return;

    default:
        for (int row = 0; row < size.y; row++) {
            for (int column = 0; column < size.x; column++) {
                vec2i current_coord = pixel_coords_cache[row][column];
                color color_mask = (tile_blocked_array[row][column] || fully_blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
                draw_flat_tile(current_coord, color_mask, ctx);
            }
        }
        break;
    }
}

void BuildPlanner::draw_graphics(painter &ctx) {
    // TODO: bring these all over the unified system
    // special graphics buildings
    vec2i pixel = pixel_coords_cache[0][0];
    switch (build_type) {
    case BUILDING_ROAD:
        building_road::ghost_preview(end, pixel, ctx);
        return;

    case BUILDING_IRRIGATION_DITCH:
        draw_canal(end, pixel, ctx);
        return;
        //        case BUILDING_WALL_PH:
        //            return draw_walls((const map_tile*)&end, end_coord.x, end_coord.y);
        //            break;
    case BUILDING_STORAGE_YARD:
        building_storage_yard::ghost_preview(pixel, ctx);
        return;

    case BUILDING_BOOTH:
    case BUILDING_BANDSTAND:
    case BUILDING_PAVILLION:
    case BUILDING_FESTIVAL_SQUARE:
        draw_entertainment_venue(end, pixel, build_type, ctx);
        return;

    case BUILDING_SMALL_MASTABA:
        building_small_mastaba::ghost_preview(ctx, build_type, pixel, start, end);
        return;

    case BUILDING_BARLEY_FARM:
    case BUILDING_FLAX_FARM:
    case BUILDING_GRAIN_FARM:
    case BUILDING_LETTUCE_FARM:
    case BUILDING_POMEGRANATES_FARM:
    case BUILDING_CHICKPEAS_FARM:
    case BUILDING_FIGS_FARM:
    case BUILDING_HENNA_FARM:
        building_farm::ghost_preview(ctx, build_type, pixel, end);
        return;

    case BUILDING_FORT_ARCHERS:
    case BUILDING_FORT_CHARIOTEERS:
    case BUILDING_FORT_INFANTRY:
        building_fort::ghost_preview(ctx, end, pixel, 0);
        return;

    case BUILDING_WELL:
        building_well::ghost_preview(ctx, end, pixel, 0);        
        break;
    }

    // go through the tiles DIAGONALLY to render footprint and top correctly
    for (int dg_y = 0; dg_y < size.y + size.x - 1; dg_y++) {
        for (int dg_x = fmax(0, dg_y - size.y + 1); dg_x < size.x && dg_x < dg_y + 1; dg_x++) {
            // extract proper row and column index from the mess above
            int row = dg_y - dg_x;
            int column = dg_x;

            int image_id = tile_graphics_array[row][column];
            if (image_id > 0) {
                vec2i current_coord = pixel_coords_cache[row][column];
                ImageDraw::isometric_from_drawtile(ctx, image_id, current_coord, COLOR_MASK_GREEN);
                ImageDraw::isometric_from_drawtile_top(ctx, image_id, current_coord, COLOR_MASK_GREEN);
            }
        }
    }
}

void BuildPlanner::draw(painter &ctx) {
    // empty building
    if (size.x < 1 || size.y < 1)
        return;

    if (can_place == CAN_NOT_PLACE) {
        // draw fully red (placement not allowed)
        draw_blueprints(ctx, true);
    } else if (tiles_blocked_total > 0) {
        // draw green blueprint with red (blocked) tiles
        draw_blueprints(ctx, false);
    } else if (!draw_as_constructing) {
        // draw normal building ghost (green)
        draw_graphics(ctx);
    }
}
