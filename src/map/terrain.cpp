#include <game/io/io_buffer.h>
#include "terrain.h"

#include "map/grid.h"
#include "map/ring.h"
#include "map/routing.h"
#include "core/game_environment.h"
#include "city/floods.h"
#include "floodplain.h"
#include "water.h"
#include "data.h"

static grid_xx terrain_grid = {0, {FS_UINT16, FS_UINT32}};
static grid_xx terrain_grid_backup = {0, {FS_UINT16, FS_UINT32}};

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
void map_terrain_add_in_area(int x_min, int y_min, int x_max, int y_max, int terrain) {
    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            map_terrain_add(map_grid_offset(xx, yy), terrain);
        }
    }
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

void build_terrain_caches() {
    tile_cache_floodplain_clear();
    tile_cache_river_clear();

    // fill in all water/river tiles
    int river_tile = 0;
    int floodplain_tile = 0;
    int grid_offset = map_data.start_offset;
    for (int y = 0; y < map_data.height; y++, grid_offset += map_data.border_size) {
        for (int x = 0; x < map_data.width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN + TERRAIN_WATER)) {
                tile_cache_river_add(grid_offset, x, y);
//                all_river_tiles[river_tile] = grid_offset;
//                all_river_tiles_x[river_tile] = x;
//                all_river_tiles_y[river_tile] = y;
//                river_total_tiles++;
                river_tile++;
            }
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER)) {
                tile_cache_floodplain_add(grid_offset);
//                all_floodplain_tiles[floodplain_tile] = grid_offset;
//                floodplain_total_tiles++;
                floodplain_tile++;
            }
        }
    }
}

// unknown data grid
static grid_xx GRID03_32BIT = {0, {FS_INT8, FS_INT32}}; // ?? routing
int64_t map_get_UNK32bit(int grid_offset) {
    return map_grid_get(&GRID03_32BIT, grid_offset);
}

io_buffer *iob_terrain_grid = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &terrain_grid);
});
io_buffer *iob_GRID03_32BIT = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &GRID03_32BIT);
});
