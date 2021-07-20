#include "terrain.h"

#include "map/grid.h"
#include "map/ring.h"
#include "map/routing.h"
#include "core/game_environment.h"
#include "city/floods.h"

static grid_xx terrain_grid = {0, {FS_UINT16, FS_UINT32}};
static grid_xx terrain_grid_backup = {0, {FS_UINT16, FS_UINT32}};
static grid_xx terrain_moisture = {0, {FS_UINT8, FS_UINT8}};

int all_river_tiles[GRID_SIZE_PH * GRID_SIZE_PH];
int all_river_tiles_x[GRID_SIZE_PH * GRID_SIZE_PH];
int all_river_tiles_y[GRID_SIZE_PH * GRID_SIZE_PH];
int all_floodplain_tiles[GRID_SIZE_PH * GRID_SIZE_PH];
int river_total_tiles = 0;
int floodplain_total_tiles = 0;

static grid_xx terrain_floodplain_shoreorder = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_growth = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_fertility = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_soil_depletion = {0, {FS_INT8, FS_INT8}};

// unknown data grids
static grid_xx GRID01_8BIT = {0, {FS_INT8, FS_INT8}}; // all 00
static grid_xx GRID02_8BIT = {0, {FS_INT8, FS_INT8}}; // all FF
static grid_xx GRID03_32BIT = {0, {FS_INT8, FS_INT32}}; // ?? routing

bool map_terrain_is(int grid_offset, int terrain) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(&terrain_grid, grid_offset) & terrain;
}
int map_terrain_get(int grid_offset) {
    return map_grid_get(&terrain_grid, grid_offset);
}
void map_terrain_set(int grid_offset, int terrain) {
    map_grid_set(&terrain_grid, grid_offset, terrain);
}
void map_terrain_add(int grid_offset, int terrain) {
    map_grid_or(&terrain_grid, grid_offset, terrain);
}
void map_terrain_remove(int grid_offset, int terrain) {
    map_grid_and(&terrain_grid, grid_offset, ~terrain);
}
void map_terrain_add_with_radius(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            map_terrain_add(map_grid_offset(xx, yy), terrain);
        }
    }
}
void map_terrain_remove_with_radius(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            map_terrain_remove(map_grid_offset(xx, yy), terrain);
        }
    }
}
void map_terrain_remove_all(int terrain) {
    map_grid_and_all(&terrain_grid, ~terrain);
}

int map_terrain_count_directly_adjacent_with_type(int grid_offset, int terrain) {
    int count = 0;
    if (map_terrain_is(grid_offset + map_grid_delta(0, -1), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(1, 0), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(0, 1), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(-1, 0), terrain))
        count++;

    return count;
}
int map_terrain_count_diagonally_adjacent_with_type(int grid_offset, int terrain) {
    int count = 0;
    if (map_terrain_is(grid_offset + map_grid_delta(1, -1), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(1, 1), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(-1, 1), terrain))
        count++;

    if (map_terrain_is(grid_offset + map_grid_delta(-1, -1), terrain))
        count++;

    return count;
}

bool map_terrain_has_adjecent_with_type(int grid_offset, int terrain) {
    if (map_terrain_is(grid_offset + map_grid_delta(-1, -1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(0, -1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(1, -1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(1, 0), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(1, 1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(0, 1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(-1, 1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(-1, 0), terrain)) {
        return true;
    }
    return false;
}
bool map_terrain_has_adjacent_x_with_type(int grid_offset, int terrain) {
    if (map_terrain_is(grid_offset + map_grid_delta(-1, 0), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(1, 0), terrain)) {
        return true;
    }
    return false;
}
bool map_terrain_has_adjacent_y_with_type(int grid_offset, int terrain) {
    if (map_terrain_is(grid_offset + map_grid_delta(0, -1), terrain) ||
        map_terrain_is(grid_offset + map_grid_delta(0, 1), terrain)) {
        return true;
    }
    return false;
}
bool map_terrain_exists_tile_in_area_with_type(int x, int y, int size, int terrain) {
    for (int yy = y; yy < y + size; yy++) {
        for (int xx = x; xx < x + size; xx++) {
            if (map_grid_is_inside(xx, yy, 1) && map_grid_get(&terrain_grid, map_grid_offset(xx, yy)) & terrain)
                return true;
        }
    }
    return false;
}
bool map_terrain_exists_tile_in_radius_with_type(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            if (map_terrain_is(map_grid_offset(xx, yy), terrain))
                return true;
        }
    }
    return false;
}
bool map_terrain_exists_tile_in_radius_with_exact(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            if (map_terrain_get(map_grid_offset(xx, yy)) == terrain)
                return true;
        }
    }
    return false;
}
bool map_terrain_exists_clear_tile_in_radius(int x, int y, int size, int radius, int except_grid_offset, int *x_tile, int *y_tile) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            int grid_offset = map_grid_offset(xx, yy);
            if (grid_offset != except_grid_offset && !map_grid_get(&terrain_grid, grid_offset)) {
                *x_tile = xx;
                *y_tile = yy;
                return true;
            }
        }
    }
    *x_tile = x_max;
    *y_tile = y_max;
    return false;
}

bool map_terrain_all_tiles_in_area_are(int x, int y, int size, int terrain) {
    if (!map_grid_is_inside(x, y, size))
        return false;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
//            if ((map_terrain_get(grid_offset) & TERRAIN_NOT_CLEAR) != terrain)
            if (!map_terrain_is(grid_offset, terrain))
                return false;
        }
    }
    return true;
}

bool map_terrain_all_tiles_in_radius_are(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            if (!map_terrain_is(map_grid_offset(xx, yy), terrain))
                return false;
        }
    }
    return true;
}
bool map_terrain_has_only_rocks_trees_in_ring(int x, int y, int distance) {
    int start = map_ring_start(1, distance);
    int end = map_ring_end(1, distance);
    int base_offset = map_grid_offset(x, y);
    for (int i = start; i < end; i++) {
        const ring_tile *tile = map_ring_tile(i);
        if (map_ring_is_inside_map(x + tile->x, y + tile->y)) {
            if (!map_terrain_is(base_offset + tile->grid_offset, TERRAIN_ROCK | TERRAIN_TREE))
                return false;
        }
    }
    return true;
}
bool map_terrain_has_only_meadow_in_ring(int x, int y, int distance) {
    int start = map_ring_start(1, distance);
    int end = map_ring_end(1, distance);
    int base_offset = map_grid_offset(x, y);
    for (int i = start; i < end; i++) {
        const ring_tile *tile = map_ring_tile(i);
        if (map_ring_is_inside_map(x + tile->x, y + tile->y)) {
            if (!map_terrain_is(base_offset + tile->grid_offset, TERRAIN_MEADOW))
                return false;
        }
    }
    return true;
}
bool map_terrain_is_adjacent_to_wall(int x, int y, int size) {
    int base_offset = map_grid_offset(x, y);
    for (const int *tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        if (map_terrain_is(base_offset + *tile_delta, TERRAIN_WALL))
            return true;
    }
    return false;
}
bool map_terrain_is_adjacent_to_water(int x, int y, int size) {
    int base_offset = map_grid_offset(x, y);
    for (const int *tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        if (map_terrain_is(base_offset + *tile_delta, TERRAIN_WATER))
            return true;
    }
    return false;
}
bool map_terrain_is_adjacent_to_open_water(int x, int y, int size) {
    int base_offset = map_grid_offset(x, y);
    for (const int *tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        if (map_terrain_is(base_offset + *tile_delta, TERRAIN_WATER) &&
            map_routing_distance(base_offset + *tile_delta) > 0) {
            return true;
        }
    }
    return false;
}
bool map_terrain_get_adjacent_road_or_clear_land(int x, int y, int size, int *x_tile, int *y_tile) {
    int base_offset = map_grid_offset(x, y);
    for (const int *tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        int grid_offset = base_offset + *tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_ROAD) ||
            !map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)) {
            *x_tile = map_grid_offset_to_x(grid_offset);
            *y_tile = map_grid_offset_to_y(grid_offset);
            return true;
        }
    }
    return false;
}

static void add_road(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR))
        map_terrain_add(grid_offset, TERRAIN_ROAD);

}
void map_terrain_add_roadblock_road(int x, int y, int orientation) {
    // roads under roadblock
    map_terrain_add(map_grid_offset(x, y), TERRAIN_ROAD);
}
void map_terrain_add_gatehouse_roads(int x, int y, int orientation) {
    // roads under gatehouse
    map_terrain_add(map_grid_offset(x, y), TERRAIN_ROAD);
    map_terrain_add(map_grid_offset(x + 1, y), TERRAIN_ROAD);
    map_terrain_add(map_grid_offset(x, y + 1), TERRAIN_ROAD);
    map_terrain_add(map_grid_offset(x + 1, y + 1), TERRAIN_ROAD);

    // free roads before/after gate
    if (orientation == 1) {
        add_road(map_grid_offset(x, y - 1));
        add_road(map_grid_offset(x + 1, y - 1));
        add_road(map_grid_offset(x, y + 2));
        add_road(map_grid_offset(x + 1, y + 2));
    } else if (orientation == 2) {
        add_road(map_grid_offset(x - 1, y));
        add_road(map_grid_offset(x - 1, y + 1));
        add_road(map_grid_offset(x + 2, y));
        add_road(map_grid_offset(x + 2, y + 1));
    }
}
void map_terrain_add_triumphal_arch_roads(int x, int y, int orientation) {
    if (orientation == 1) {
        // road in the middle
        map_terrain_add(map_grid_offset(x + 1, y), TERRAIN_ROAD);
        map_terrain_add(map_grid_offset(x + 1, y + 1), TERRAIN_ROAD);
        map_terrain_add(map_grid_offset(x + 1, y + 2), TERRAIN_ROAD);
        // no roads on other tiles
        map_terrain_remove(map_grid_offset(x, y), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x, y + 1), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x, y + 2), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 2, y), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 2, y + 1), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 2, y + 2), TERRAIN_ROAD);
    } else if (orientation == 2) {
        // road in the middle
        map_terrain_add(map_grid_offset(x, y + 1), TERRAIN_ROAD);
        map_terrain_add(map_grid_offset(x + 1, y + 1), TERRAIN_ROAD);
        map_terrain_add(map_grid_offset(x + 2, y + 1), TERRAIN_ROAD);
        // no roads on other tiles
        map_terrain_remove(map_grid_offset(x, y), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 1, y), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 2, y), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x, y + 2), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 1, y + 2), TERRAIN_ROAD);
        map_terrain_remove(map_grid_offset(x + 2, y + 2), TERRAIN_ROAD);
    }
}

////

#include "map/data.h"
#include <stdlib.h>
#include <city/data_private.h>

floodplain_order floodplain_offsets[30];

int map_floodplain_rebuild_shoreorder() {

    // reset all to zero
    map_grid_fill(&terrain_floodplain_shoreorder, 0);
    map_grid_fill(&terrain_floodplain_growth, 0);
    map_grid_fill(&terrain_floodplain_fertility, 0);
    for (int order = 1; order <= 30; order++) {
        floodplain_offsets[order].initialized = false;
        floodplain_offsets[order].amount = 0;
    }
    river_total_tiles = 0;
    floodplain_total_tiles = 0;

    // fill in all water/river tiles
    int river_tile = 0;
    int floodplain_tile = 0;
    int grid_offset = map_data.start_offset;
    for (int y = 0; y < map_data.height; y++, grid_offset += map_data.border_size) {
        for (int x = 0; x < map_data.width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN + TERRAIN_WATER)) {
                all_river_tiles[river_tile] = grid_offset;
                all_river_tiles_x[river_tile] = x;
                all_river_tiles_y[river_tile] = y;
                river_total_tiles++;
                river_tile++;
            }
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER)) {
                all_floodplain_tiles[floodplain_tile] = grid_offset;
                floodplain_total_tiles++;
                floodplain_tile++;
            }
        }
    }

    // fill in shore order data
    for (int order = 1; order < 30; order++) {

        // temporary buffer to be transfered later into the offset caches
        int temp_cache_buffer[grid_total_size[ENGINE_ENV_PHARAOH]];
        int temp_cache_howmany = 0;

        // go through every river tile
        for (int i = 0; i < river_total_tiles; i++) {

            int current_tile = all_river_tiles[i];
            if ((order == 1 && map_terrain_is(current_tile, TERRAIN_WATER) && !map_terrain_is(current_tile, TERRAIN_FLOODPLAIN)) || // loop through every water tile
                (order > 1 && // or, through every floodplain tile of the previous round
                 map_terrain_is(current_tile, TERRAIN_FLOODPLAIN) &&
                 map_get_shoreorder(current_tile) == order - 1)) {

                // loop through for a 3x3 area around the tile
                int x_min = all_river_tiles_x[i] - 1;
                int x_max = all_river_tiles_x[i] + 1;
                int y_min = all_river_tiles_y[i] - 1;
                int y_max = all_river_tiles_y[i] + 1;

                map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
                int grid_offset = map_grid_offset(x_min, y_min);
                for (int yy = y_min; yy <= y_max; yy++) {
                    for (int xx = x_min; xx <= x_max; xx++) {
                        // do only on floodplain tiles
                        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && map_grid_is_valid_offset(grid_offset)) {

                            // set fertility data
                            int prev_fert = map_grid_get(&terrain_floodplain_fertility, grid_offset);
                            int this_fert = 101 - (order - 1) * 3.4;
                            if (this_fert < 0)
                                this_fert = 0;
                            if (prev_fert == 0)
                                map_grid_set(&terrain_floodplain_fertility, grid_offset, this_fert);

                            // only do new order cache tiles
                            if (map_get_shoreorder(grid_offset) == 0) {
                                map_grid_set(&terrain_floodplain_shoreorder, grid_offset, order);

                                // add current tile to temp list of offsets
                                temp_cache_buffer[temp_cache_howmany] = grid_offset;
                                temp_cache_howmany++;
                            }
                        }
                        ++grid_offset;
                    }
                    grid_offset += grid_size[GAME_ENV] - (x_max - x_min + 1);
                }
            }
        }

        // build long-term order list cache!
        floodplain_order *order_cache = &floodplain_offsets[order - 1];
        if (order_cache->initialized)
            free(order_cache->offsets);
        order_cache->offsets = (uint32_t*)malloc(temp_cache_howmany * sizeof(uint32_t));
        order_cache->initialized = true;
        order_cache->amount = temp_cache_howmany;
        for (int o = 0; o < temp_cache_howmany; o++)
            order_cache->offsets[o] = temp_cache_buffer[o];

        // no more shore tiles, return!
        if (temp_cache_howmany == 0)
            return order;
    }

    // if past 29, fill in all the rest with the same order
    int temp_cache_buffer[grid_total_size[ENGINE_ENV_PHARAOH]];
    int temp_cache_howmany = 0;
    for (int i = 0; i < floodplain_total_tiles; i++) {
        int offset = all_floodplain_tiles[i];
        if (map_get_shoreorder(offset) == 0) {
            map_grid_set(&terrain_floodplain_shoreorder, offset, 30);
            // add current tile to temp list of offsets
            temp_cache_buffer[temp_cache_howmany] = offset;
            temp_cache_howmany++;
        }
    }
    // fill in the last order!
    floodplain_order *order_cache = &floodplain_offsets[29];
    if (order_cache->initialized)
        free(order_cache->offsets);
    order_cache->offsets = (uint32_t*)malloc(temp_cache_howmany * sizeof(uint32_t));
    order_cache->initialized = true;
    order_cache->amount = temp_cache_howmany;
    for (int o = 0; o < temp_cache_howmany; o++)
        order_cache->offsets[o] = temp_cache_buffer[o];

    return 30;
}

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

uint8_t map_get_shoreorder(int grid_offset) {
    return map_grid_get(&terrain_floodplain_shoreorder, grid_offset);
}
uint8_t map_get_growth(int grid_offset) {
    return map_grid_get(&terrain_floodplain_growth, grid_offset);
}
uint8_t map_get_fertility(int grid_offset) { // actual percentage integer [0-99]
    int fert_value = map_grid_get(&terrain_floodplain_fertility, grid_offset); // start with the "theoretical" value

    // calculate and add malus
    int malus = map_grid_get(&terrain_floodplain_soil_depletion, grid_offset);
    if (malus != 0)
        fert_value += map_grid_get(&terrain_floodplain_soil_depletion, grid_offset);

    return max(0, min(99, fert_value));
}
uint8_t map_get_fertility_average(int grid_offset) {
    // returns average of fertility in 3x3 square starting on the top-left corner
    return (map_get_fertility(grid_offset) + map_get_fertility(grid_offset + 1) + map_get_fertility(grid_offset + 2)
          + map_get_fertility(grid_offset + 228) + map_get_fertility(grid_offset + 229) + map_get_fertility(grid_offset + 230)
          + map_get_fertility(grid_offset + 228 + 228) + map_get_fertility(grid_offset + 229 + 228) + map_get_fertility(grid_offset + 230 + 228)) / 9;
}
void map_set_growth(int grid_offset, int growth) {
    if (growth >= 0 && growth < 6)
        map_grid_set(&terrain_floodplain_growth, grid_offset, growth);
}
void map_soil_depletion(int grid_offset, int malus) {
    map_grid_set(&terrain_floodplain_soil_depletion, grid_offset, malus);
}

/////

void map_terrain_backup(void) {
    map_grid_copy(&terrain_grid, &terrain_grid_backup);
}
void map_terrain_restore(void) {
    map_grid_copy(&terrain_grid_backup, &terrain_grid);
}
void map_terrain_clear(void) {
    map_grid_clear(&terrain_grid);
}
void map_terrain_init_outside_map(void) {
    int map_width, map_height;
    map_grid_size(&map_width, &map_height);
    int y_start = (grid_size[GAME_ENV] - map_height) / 2;
    int x_start = (grid_size[GAME_ENV] - map_width) / 2;
    for (int y = 0; y < grid_size[GAME_ENV]; y++) {
        int y_outside_map = y < y_start || y >= y_start + map_height;
        for (int x = 0; x < grid_size[GAME_ENV]; x++) {
            if (y_outside_map || x < x_start || x >= x_start + map_width)
                map_grid_set(&terrain_grid, x + grid_size[GAME_ENV] * y, TERRAIN_TREE | TERRAIN_WATER);

        }
    }
}

void map_terrain_save_state(buffer *buf) {
    map_grid_save_buffer(&terrain_grid, buf);
}
void map_terrain_load_state(buffer *buf) {
    map_grid_load_buffer(&terrain_grid, buf);
}

void map_moisture_load_state(buffer *buf) {
    map_grid_load_buffer(&terrain_moisture, buf);
}
uint8_t map_moisture_get(int grid_offset) {
    return map_grid_get(&terrain_moisture, grid_offset);
}
uint8_t map_grasslevel_get(int grid_offset) {
    int moist = map_moisture_get(grid_offset);
//    if (moist & MOISTURE_TALLGRASS)
////        return moist - MOISTURE_TALLGRASS + 20;
//        return 64;
    if (moist & MOISTURE_TRANSITION)
        return moist - MOISTURE_TRANSITION + 16;
    if (moist & MOISTURE_GRASS)
        return (moist - MOISTURE_GRASS)/8 + 1;
    if (!moist)
        return 0;
    return 13;
}
bool map_is_4x4_tallgrass(int x, int y, int grid_offset) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, 1, 3, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            if (map_grasslevel_get(map_grid_offset(xx, yy)) != 12)
                return false;
        }
    }
    return true;
}

void map_temp_grid_load(buffer *buf, int g) {
    switch (g) {
        case 0:
            map_grid_load_buffer(&GRID01_8BIT, buf); break;
        case 1:
            map_grid_load_buffer(&GRID02_8BIT, buf); break;
        case 2:
            map_grid_load_buffer(&GRID03_32BIT, buf); break;
        case 3:
            map_grid_load_buffer(&terrain_floodplain_soil_depletion, buf); break;
    }
}
int64_t map_temp_grid_get(int grid_offset, int g) {
    switch (g) {
        case 0:
            return map_grid_get(&GRID01_8BIT, grid_offset); break;
        case 1:
            return map_grid_get(&GRID02_8BIT, grid_offset); break;
        case 2:
            return map_grid_get(&GRID03_32BIT, grid_offset); break;
        case 3:
            return map_grid_get(&terrain_floodplain_soil_depletion, grid_offset); break;
    }
}

