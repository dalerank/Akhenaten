#include "building_ghost.h"

#include "grid/routing/routing.h"
#include "building/construction/build_planner.h"
#include "building/industry.h"
#include "building/properties.h"
#include "building/rotation.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "grid/bridge.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "grid/image_context.h"
#include "grid/orientation.h"
#include "grid/property.h"
#include "grid/road_aqueduct.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "config/config.h"
#include "ornaments.h"
#include "widget/city/bridges.h"

#include <cmath>

#define MAX_TILES 25

const vec2i VIEW_OFFSETS[MAX_TILES] = {          {0, 0},
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

static const int FORT_GROUND_GRID_OFFSETS_PH[4][4] = {
     {GRID_OFFSET(3, -1), GRID_OFFSET(4, -1), GRID_OFFSET(4, 0), GRID_OFFSET(3, 0)},
     {GRID_OFFSET(-1, -4), GRID_OFFSET(0, -4), GRID_OFFSET(0, -3), GRID_OFFSET(-1, -3)},
     {GRID_OFFSET(-4, 0), GRID_OFFSET(-3, 0), GRID_OFFSET(-3, 1), GRID_OFFSET(-4, 1)},
     {GRID_OFFSET(0, 3), GRID_OFFSET(1, 3), GRID_OFFSET(1, 4), GRID_OFFSET(0, 4)}
};
static const int FORT_GROUND_X_VIEW_OFFSETS[4] = {120, 90, -120, -90};
static const int FORT_GROUND_Y_VIEW_OFFSETS[4] = {30, -75, -60, 45};

static const int RESERVOIR_GRID_OFFSETS_PH[4]
  = {GRID_OFFSET(-1, -1), GRID_OFFSET(1, -1), GRID_OFFSET(1, 1), GRID_OFFSET(-1, 1)};

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

static int get_building_image_id(int map_x, int map_y, int type, const building_properties* props) {
    int image_id = props->img_id();
    if (type == BUILDING_GATEHOUSE) {
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
    } else if (type == BUILDING_TRIUMPHAL_ARCH) {
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

static int is_blocked_for_building(int grid_offset, int num_tiles, int* blocked_tiles) {
    int orientation_index = city_view_orientation() / 2;
    int blocked = 0;
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset; // + TILE_GRID_OFFSETS[orientation_index][i];
        switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH:
            tile_offset += TILE_GRID_OFFSETS_PH[orientation_index][i];
            break;
        }
        bool tile_blocked = false;
        if (map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR))
            tile_blocked = true;
        if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) > 0
            || map_terrain_count_diagonally_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) > 0)
            tile_blocked = true;

        if (map_has_figure_at(tile_offset))
            tile_blocked = true;

        blocked_tiles[i] = tile_blocked;
        blocked += (tile_blocked ? 1 : 0);
    }
    return blocked;
}

static void draw_flat_tile(view_context &ctx, int x, int y, color color_mask) {
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), x, y, color_mask);
}

static void draw_partially_blocked(view_context &ctx, vec2i tile, int fully_blocked, int num_tiles, int* blocked_tiles) {
    for (int i = 0; i < num_tiles; i++) {
        vec2i offset = tile + VIEW_OFFSETS[i];
        if (fully_blocked || blocked_tiles[i])
            draw_flat_tile(ctx, offset.x, offset.y, COLOR_MASK_RED);
        else
            draw_flat_tile(ctx, offset.x, offset.y, COLOR_MASK_GREEN);
    }
}

void draw_building(view_context &ctx, int image_id, vec2i tile, color color_mask) {
    ImageDraw::isometric(ctx, image_id, tile, color_mask);
}

static void draw_fountain_range(vec2i pixel, map_point point, view_context &ctx) {
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pixel.x, pixel.y, COLOR_MASK_BLUE, zoom_get_scale());
}

static void draw_storage_yard(vec2i tile, view_context &ctx) {
    int global_rotation = building_rotation_global_rotation();
    int index_rotation = building_rotation_get_storage_fort_orientation(global_rotation);
    int corner = building_rotation_get_corner(index_rotation);
    vec2i corner_offset{-5, -45};
    vec2i place_offset{0, -15};

    int image_id_hut = image_id_from_group(GROUP_BUILDING_STORAGE_YARD);
    int image_id_space = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY);
    for (int i = 0; i < 9; i++) {
        if (i == corner) {
            draw_building(ctx, image_id_hut, tile + VIEW_OFFSETS[i]);
            ImageDraw::img_generic(ctx, image_id_hut + 17, tile.x + VIEW_OFFSETS[i].x + corner_offset.x, tile.y + VIEW_OFFSETS[i].y + corner_offset.y, COLOR_MASK_GREEN);
        } else {
            draw_building(ctx, image_id_space, tile + VIEW_OFFSETS[i] + place_offset);
        }
    }
}

static void draw_farm(view_context &ctx, e_building_type type, vec2i tile, int grid_offset) {
    int image_id = get_farm_image(grid_offset);
    draw_building(ctx, image_id, tile + vec2i{-60, 0});
    
    // fields
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    for (int i = 4; i < 9; i++)
    //        ImageDraw::isometric(image_id + 1, x + X_VIEW_OFFSETS[i], y + Y_VIEW_OFFSETS[i], COLOR_MASK_GREEN);
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH)
    draw_farm_crops(ctx, type, 0, grid_offset, tile + vec2i{-60, 30}, COLOR_MASK_GREEN);
}

static void draw_fort(map_point* tile, vec2i pos, view_context &ctx) {
    bool fully_blocked = false;
    bool blocked = false;
    if (formation_get_num_forts_cached() >= formation_get_max_forts() || city_finance_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    int num_tiles_fort = building_properties_for_type(BUILDING_MENU_FORTS)->size;
    num_tiles_fort *= num_tiles_fort;
    int num_tiles_ground = building_properties_for_type(BUILDING_FORT_GROUND)->size;
    num_tiles_ground *= num_tiles_ground;

    //    int grid_offset_fort = tile->grid_offset;
    int global_rotation = building_rotation_global_rotation();
    int grid_offset_ground = tile->grid_offset() + FORT_GROUND_GRID_OFFSETS_PH[global_rotation][city_view_orientation() / 2];

    int blocked_tiles_fort[MAX_TILES];
    int blocked_tiles_ground[MAX_TILES];

    blocked += is_blocked_for_building(tile->grid_offset(), num_tiles_fort, blocked_tiles_fort);
    blocked += is_blocked_for_building(grid_offset_ground, num_tiles_ground, blocked_tiles_ground);

    int orientation_index = building_rotation_get_storage_fort_orientation(global_rotation) / 2;
    vec2i ground = pos + vec2i(FORT_GROUND_X_VIEW_OFFSETS[orientation_index], FORT_GROUND_Y_VIEW_OFFSETS[orientation_index]);

    if (blocked) {
        draw_partially_blocked(ctx, pos, fully_blocked, num_tiles_fort, blocked_tiles_fort);
        draw_partially_blocked(ctx, ground, fully_blocked, num_tiles_ground, blocked_tiles_ground);
    } else {
        int image_id = image_id_from_group(GROUP_BUILDING_FORT);
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            draw_building(ctx, image_id, pos);
            draw_building(ctx, image_id + 1, ground);
        } else {
            // draw ground first, then fort
            draw_building(ctx, image_id + 1, ground);
            draw_building(ctx, image_id, pos);
        }
    }
}

static void draw_aqueduct(map_point tile, int x, int y, view_context &ctx) {
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
            blocked = !map_is_straight_road_for_aqueduct(grid_offset); // can't start over a road curve!
            if (map_property_is_plaza_or_earthquake(grid_offset))      // todo: plaza not allowing aqueducts? maybe?
                blocked = true;
        } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)
                   && !map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) // terrain is not clear!
            blocked = true;
    }
    if (city_finance_out_of_money()) { // check sufficient funds to continue
        blocked = true;
    }

    if (blocked) { // cannot draw!
        draw_flat_tile(ctx, x, y, COLOR_MASK_RED);
    } else {
        const terrain_image* img = map_image_context_get_aqueduct(grid_offset); // get starting tile
        draw_building(ctx, get_aqueduct_image(grid_offset, map_terrain_is(grid_offset, TERRAIN_ROAD), 0, img), {x, y});
    }
}
static void draw_road(tile2i tile, int x, int y, view_context &ctx) {
    int grid_offset = tile.grid_offset();
    bool blocked = false;
    int image_id = 0;
    if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
        image_id = image_id_from_group(GROUP_BUILDING_AQUEDUCT);
        if (map_can_place_road_under_aqueduct(grid_offset)) {
            image_id += map_get_aqueduct_with_road_image(grid_offset);
        } else {
            blocked = true;
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR - TERRAIN_FLOODPLAIN)) {
        blocked = true;
    } else {
        image_id = image_id_from_group(GROUP_TERRAIN_DIRT_ROAD);
        if (!map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD) && map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD)) {
            image_id++;
        }

        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) // inundated floodplains
                blocked = true;
        } else if (map_terrain_has_adjecent_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN) != 1)
                blocked = true;
            else {
                if (map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_FLOODPLAIN)) {
                    if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_ROAD))
                        blocked = true;
                    else
                        image_id++;
                }
                if (map_terrain_has_adjacent_y_with_type(grid_offset, TERRAIN_FLOODPLAIN)
                    && map_terrain_has_adjacent_x_with_type(grid_offset, TERRAIN_ROAD))
                    blocked = true;
            }
        }
    }

    if (city_finance_out_of_money()) {
        blocked = true;
    }

    if (blocked) {
        draw_flat_tile(ctx, x, y, COLOR_MASK_RED);
    } else {
        draw_building(ctx, image_id, {x, y});
    }
}

static void draw_bridge(map_point tile, int x, int y, int type, view_context &ctx) {
    int length, direction;
    int end_grid_offset = map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction);

    int dir = direction - city_view_orientation();
    if (dir < 0)
        dir += 8;

    bool blocked = false;
    if (type == BUILDING_SHIP_BRIDGE && length < 5)
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
        draw_flat_tile(ctx, x, y, length > 0 ? COLOR_MASK_GREEN : COLOR_MASK_RED);
        if (length > 1)
            draw_flat_tile(ctx, x + x_delta * (length - 1), y + y_delta * (length - 1), COLOR_MASK_RED);

    } else {
        if (dir == DIR_0_TOP_RIGHT || dir == DIR_6_TOP_LEFT) {
            for (int i = length - 1; i >= 0; i--) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_SHIP_BRIDGE);
                city_draw_bridge_tile(ctx, x + x_delta * i, y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        } else {
            for (int i = 0; i < length; i++) {
                int sprite_id = map_bridge_get_sprite_id(i, length, dir, type == BUILDING_SHIP_BRIDGE);
                city_draw_bridge_tile(ctx, x + x_delta * i, y + y_delta * i, sprite_id, COLOR_MASK_GREEN);
            }
        }
    }
}

static void draw_entertainment_venue(map_point tile, int x, int y, int type, view_context &ctx) {
    int can_build = 0;
    //    const building_properties *props = building_properties_for_type(type);
    int size = 0;
    int orientation = 0;
    //    map_tile northern_corner = *tile;
    switch (type) {
    case BUILDING_BOOTH: size = 2; break;
    case BUILDING_BANDSTAND: size = 3; break;
    case BUILDING_PAVILLION: size = 4; break;
    case BUILDING_FESTIVAL_SQUARE: size = 5; break;
    }
    //    int map_orientation = city_view_orientation();
    //    switch (map_orientation) {
    //        case 2: // east
    //            northern_corner.x -= (size - 1);
    //            break;
    //        case 4: // south
    //            northern_corner.x -= (size - 1);
    //            northern_corner.y -= (size - 1);
    //            break;
    //        case 6: // west
    //            northern_corner.y -= (size - 1);
    //            break;
    //    }
    switch (type) {
    case BUILDING_BOOTH:
        can_build = map_orientation_for_venue_with_map_orientation(tile.x(), tile.y(), 0, &orientation);
        break;
    case BUILDING_BANDSTAND:
        can_build = map_orientation_for_venue_with_map_orientation(tile.x(), tile.y(), 1, &orientation);
        break;
    case BUILDING_PAVILLION:
        can_build = map_orientation_for_venue_with_map_orientation(tile.x(), tile.y(), 2, &orientation);
        break;
    case BUILDING_FESTIVAL_SQUARE:
        can_build = map_orientation_for_venue_with_map_orientation(tile.x(), tile.y(), 3, &orientation);
        break;
    }
    // TODO: proper correct for map orientation (for now, just use a different orientation)
    orientation = abs(orientation + (8 - city_view_orientation())) % 8;

    if (can_build != 1) { // no can place
        for (int i = 0; i < size * size; i++) {
            draw_flat_tile(ctx, x + VIEW_OFFSETS[i].x, y + VIEW_OFFSETS[i].y, COLOR_MASK_RED);
        }
    } else { // can place (theoretically)
        if (type == BUILDING_FESTIVAL_SQUARE && city_building_has_festival_square()) {
            for (int i = 0; i < size * size; i++)
                ImageDraw::isometric(ctx, image_id_from_group(GROUP_FESTIVAL_SQUARE) + i, x + ((i % size) - (i / size)) * 30, y + ((i % size) + (i / size)) * 15, COLOR_MASK_RED);
            return;
        }

        switch (type) {
        case BUILDING_BOOTH:
            for (int i = 0; i < size * size; i++) {
                ImageDraw::isometric(ctx, image_id_from_group(GROUP_BOOTH_SQUARE) + i, x + ((i % size) - (i / size)) * 30, y + ((i % size) + (i / size)) * 15, COLOR_MASK_GREEN);
            }
            switch (orientation / 2) {
            case 0:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y}, COLOR_MASK_GREEN);
                break;
            case 1:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x + 30, y + 15}, COLOR_MASK_GREEN);
                break;
            case 2:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y + 30}, COLOR_MASK_GREEN);
                break;
            case 3:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 30, y + 15}, COLOR_MASK_GREEN);
                break;
            }
            break;

        case BUILDING_BANDSTAND:
            for (int i = 0; i < size * size; i++) {
                ImageDraw::isometric(ctx, image_id_from_group(GROUP_BANDSTAND_SQUARE) + i, x + ((i % size) - (i / size)) * 30, y + ((i % size) + (i / size)) * 15, COLOR_MASK_GREEN);
            }

            switch (orientation / 2) {
            case 0:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x, y}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x - 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x + 60, y + 30}, COLOR_MASK_GREEN);
                break;
            case 1:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 2, {x + 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 3, {x + 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y + 60}, COLOR_MASK_GREEN);
                break;
            case 2:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x - 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x - 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y + 60}, COLOR_MASK_GREEN);
                break;
            case 3:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 2, {x, y}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 3, {x + 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 60, y + 30}, COLOR_MASK_GREEN);
                break;
            }
            break;

        case BUILDING_PAVILLION:
            for (int i = 0; i < size * size; i++) {
                ImageDraw::isometric(ctx, image_id_from_group(GROUP_PAVILLION_SQUARE) + i, x + ((i % size) - (i / size)) * 30, y + ((i % size) + (i / size)) * 15, COLOR_MASK_GREEN);
            }
            switch (orientation) {
            case 0:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x, y}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x + 90, y + 45}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x + 60, y + 60}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 60, y + 30}, COLOR_MASK_GREEN);
                break;
            case 1:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x + 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x, y}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x - 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 60, y + 30}, COLOR_MASK_GREEN);
                break;
            case 2:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x + 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x + 90, y + 45}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x + 60, y + 60}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y + 90}, COLOR_MASK_GREEN);
                break;
            case 3:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x - 30, y + 45}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x + 30, y + 75}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x, y + 90}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x + 90, y + 45}, COLOR_MASK_GREEN);
                break;
            case 4:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x + 30, y + 45}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x - 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x - 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 90, y + 45}, COLOR_MASK_GREEN);
                break;
            case 5:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x - 30, y + 15}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x + 60, y + 60}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x + 30, y + 75}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 90, y + 45}, COLOR_MASK_GREEN);
                break;
            case 6:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x - 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x, y + 60}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x - 30, y + 75}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x, y}, COLOR_MASK_GREEN);
                break;
            case 7:
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_PAVILLION), {x, y}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND) + 1, {x + 60, y + 30}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BANDSTAND), {x + 30, y + 45}, COLOR_MASK_GREEN);
                draw_building(ctx, image_id_from_group(GROUP_BUILDING_BOOTH), {x - 90, y + 45}, COLOR_MASK_GREEN);
                break;
            }
            break;

        case BUILDING_FESTIVAL_SQUARE:
            for (int i = 0; i < size * size; i++) {
                ImageDraw::isometric(ctx, image_id_from_group(GROUP_FESTIVAL_SQUARE) + i, x + ((i % size) - (i / size)) * 30, y + ((i % size) + (i / size)) * 15, COLOR_MASK_GREEN);
            }
            break;
        }
    }
}
static void draw_monument_blueprint(map_point tile, int x, int y, int type) {
    // TODO: implement monuments
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

void BuildPlanner::draw_flat_tile(vec2i pos, color color_mask, view_context &ctx) {
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED), pos.x, pos.y, color_mask);
}

void BuildPlanner::draw_blueprints(view_context &ctx, bool fully_blocked) {
    for (int row = 0; row < size.y; row++) {
        for (int column = 0; column < size.x; column++) {
            vec2i current_coord = pixel_coords_cache[row][column];
            color color_mask = (tile_blocked_array[row][column] || fully_blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
            draw_flat_tile(current_coord, color_mask, ctx);
        }
    }
}

void BuildPlanner::draw_graphics(view_context &ctx) {
    // TODO: bring these all over the unified system
    // special graphics buildings
    vec2i pixel = pixel_coords_cache[0][0];
    switch (build_type) {
    case BUILDING_ROAD:
        return draw_road(end, pixel.x, pixel.y, ctx);
        break;

    case BUILDING_IRRIGATION_DITCH:
        return draw_aqueduct(end, pixel.x, pixel.y, ctx);
        break;
        //        case BUILDING_WALL_PH:
        //            return draw_walls((const map_tile*)&end, end_coord.x, end_coord.y);
        //            break;
    case BUILDING_STORAGE_YARD:
        return draw_storage_yard(pixel, ctx);
        break;

    case BUILDING_BOOTH:
    case BUILDING_BANDSTAND:
    case BUILDING_PAVILLION:
    case BUILDING_FESTIVAL_SQUARE:
        draw_entertainment_venue(end, pixel.x, pixel.y, build_type, ctx);
        break;

    case BUILDING_BARLEY_FARM:
    case BUILDING_FLAX_FARM:
    case BUILDING_GRAIN_FARM:
    case BUILDING_LETTUCE_FARM:
    case BUILDING_POMEGRANATES_FARM:
    case BUILDING_CHICKPEAS_FARM:
    case BUILDING_FIGS_FARM:
    case BUILDING_HENNA_FARM:
        draw_farm(ctx, build_type, pixel, end.grid_offset());
        break;

    case BUILDING_WELL:
        if (config_get(CONFIG_UI_SHOW_WATER_STRUCTURE_RANGE)) {
            view_context ctx = view_context_main();
            city_view_foreach_tile_in_range(ctx, end.grid_offset(), 1, 2, draw_fountain_range);
        }
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
                ImageDraw::isometric_from_drawtile(ctx, image_id, current_coord.x, current_coord.y, COLOR_MASK_GREEN);
                //                ImageDraw::isometric_top_from_drawtile(image_id, current_coord.x, current_coord.y,
                //                COLOR_MASK_GREEN, city_view_get_scale_float());
            }
        }
    }
}

void BuildPlanner::draw(view_context &ctx) {
    // empty building
    if (size.x < 1 || size.y < 1)
        return;

    if (can_place == CAN_NOT_PLACE)
        // draw fully red (placement not allowed)
        draw_blueprints(ctx, true);
    else if (tiles_blocked_total > 0)
        // draw green blueprint with red (blocked) tiles
        draw_blueprints(ctx, false);
    else if (!draw_as_constructing)
        // draw normal building ghost (green)
        draw_graphics(ctx);
}
