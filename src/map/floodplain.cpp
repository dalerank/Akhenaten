#include <cstdint>
#include <core/config.h>
#include "floodplain.h"
#include "building_tiles.h"
#include "data.h"
#include "terrain.h"
#include "water.h"

struct {
    int all_floodplain_tiles[GRID_SIZE_PH * GRID_SIZE_PH];
    int floodplain_total_tiles = 0;

    struct {
        std::vector<uint32_t> offsets;
    } order_caches[MAX_FLOODPLAIN_ORDER_RANGE + 1];
} tile_cache;
void tile_cache_floodplain_clear() {
    tile_cache.floodplain_total_tiles = 0;
}
void tile_cache_floodplain_add(int grid_offset) {
    tile_cache.all_floodplain_tiles[tile_cache.floodplain_total_tiles] = grid_offset;
    tile_cache.floodplain_total_tiles++;
}
int tile_cache_floodplain_total() {
    return tile_cache.floodplain_total_tiles;
}
void foreach_floodplain_order(int order, void (*callback)(int x, int y, int grid_offset, int order)) {
    if (order < 0 || order > MAX_FLOODPLAIN_ORDER_RANGE)
        return;
    auto offsets = tile_cache.order_caches[order].offsets;
    for (int i = 0; i < offsets.size(); i++) {
        int grid_offset = offsets.at(i);
        callback(map_grid_offset_to_x(grid_offset), map_grid_offset_to_y(grid_offset), grid_offset, order);
    }
}

static grid_xx terrain_floodplain_shoreorder = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_growth = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_fertility = {0, {FS_UINT8, FS_UINT8}};
static grid_xx terrain_floodplain_max_fertile = {0, {FS_UINT8, FS_UINT8}};

static void build_shoreorder_from_tile(int x, int y, int grid_offset) {

}
int map_floodplain_rebuild_shoreorder() {

    // reset all to zero
    map_grid_fill(&terrain_floodplain_shoreorder, -1);
    map_grid_fill(&terrain_floodplain_growth, 0);
    map_grid_fill(&terrain_floodplain_max_fertile, 0);
    for (int order = 0; order < MAX_FLOODPLAIN_ORDER_RANGE; order++)
        tile_cache.order_caches[order].offsets.clear();

    // fill in shore order data
    for (int order = -1; order < MAX_FLOODPLAIN_ORDER_RANGE - 1; order++) {

        int found_floodplain_tiles_in_order = 0;

        // go through every river tile
        for (int i = 0; i < tile_cache_river_total(); i++) {

            // get current river tile's grid offset and coords
            int tile_offset = -1;
            int tile_x = -1;
            int tile_y = -1;
            tile_cache_river_get(i, &tile_offset, &tile_x, &tile_y);

            bool is_vergin_water = (order == -1
                    && map_terrain_is(tile_offset, TERRAIN_WATER)
                    && !map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN));
            bool is_vergin_floodplain = (order > -1
                    && map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN)
                    && map_get_floodplain_shoreorder(tile_offset) == order);

            if (is_vergin_water // loop through every virgin water tile
                || is_vergin_floodplain) { // or, through every floodplain tile of the previous round

                // loop through for a 3x3 area around the tile
                int x_min = tile_x - 1;
                int x_max = tile_x + 1;
                int y_min = tile_y - 1;
                int y_max = tile_y + 1;

                map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
                int grid_offset = map_grid_offset(x_min, y_min);
                for (int yy = y_min; yy <= y_max; yy++) {
                    for (int xx = x_min; xx <= x_max; xx++) {

                        // do only on floodplain tiles that haven't been calculated / cached yet
                        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && map_grid_is_valid_offset(grid_offset)
                            && map_get_floodplain_shoreorder(grid_offset) == -1) {

                            // set fertility data
                            int tile_fert = 99 - ((99.0f/30.0f) * (float)(order + 1));
                            map_grid_set(&terrain_floodplain_max_fertile, grid_offset, tile_fert);

                            // set the shore order cache
                            map_grid_set(&terrain_floodplain_shoreorder, grid_offset, order + 1);
                            tile_cache.order_caches[order + 1].offsets.push_back(grid_offset);

                            // advance counter
                            found_floodplain_tiles_in_order++;
                        }
                        ++grid_offset;
                    }
                    grid_offset += grid_size[GAME_ENV] - (x_max - x_min + 1);
                }
            }
        }

        // no more shore tiles, return!
        if (found_floodplain_tiles_in_order == 0)
            return order;
    }

    // if past 29, fill in all the rest with the same order
    for (int i = 0; i < tile_cache.floodplain_total_tiles; i++) {
        int grid_offset = tile_cache.all_floodplain_tiles[i];
        if (map_get_floodplain_shoreorder(grid_offset) == -1) {
            map_grid_set(&terrain_floodplain_shoreorder, grid_offset, MAX_FLOODPLAIN_ORDER_RANGE);
            tile_cache.order_caches[MAX_FLOODPLAIN_ORDER_RANGE].offsets.push_back(grid_offset);
        }
    }

    return MAX_FLOODPLAIN_ORDER_RANGE;
}

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

int8_t map_get_floodplain_shoreorder(int grid_offset) {
    return map_grid_get(&terrain_floodplain_shoreorder, grid_offset);
}
uint8_t map_get_floodplain_growth(int grid_offset) {
    return map_grid_get(&terrain_floodplain_growth, grid_offset);
}
int map_get_fertility(int grid_offset, int tally_type) { // actual percentage integer [0-99]
    switch (tally_type) {
        case FERT_WITH_MALUS:
            return map_grid_get(&terrain_floodplain_fertility, grid_offset);
            break;
        case FERT_ONLY_MALUS:
            return map_grid_get(&terrain_floodplain_fertility, grid_offset) - map_grid_get(&terrain_floodplain_max_fertile, grid_offset);
            break;
        case FERT_NO_MALUS:
            return map_grid_get(&terrain_floodplain_max_fertile, grid_offset);
            break;
    }
}

static uint8_t map_get_fertility_average(int grid_offset, int x, int y, int size) {
    // returns average of fertility in square starting on the top-left corner
    int x_min = x;
    int y_min = y;
    int x_max = x_min + size - 1;
    int y_max = y_min + size - 1;

    int fert_total = 0;
    map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            fert_total += map_get_fertility(grid_offset, FERT_WITH_MALUS);
            ++grid_offset;
        }
        grid_offset += grid_size[GAME_ENV] - (x_max - x_min + 1);
    }
    return fert_total / (size * size);
}
uint8_t map_get_fertility_for_farm(int grid_offset) {
    int x = map_grid_offset_to_x(grid_offset);
    int y = map_grid_offset_to_y(grid_offset);
    bool is_irrigated = false;
    if (config_get(CONFIG_GP_FIX_IRRIGATION_RANGE))
        is_irrigated = map_terrain_exists_tile_in_area_with_type(x, y, 3, TERRAIN_IRRIGATION_RANGE);
    else
        is_irrigated = map_terrain_exists_tile_in_radius_with_type(x, y, 1, 2, TERRAIN_IRRIGATION_RANGE);
    int irrigation_bonus = 40;
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN))
        irrigation_bonus = 20;
    return min(2 + map_get_fertility_average(grid_offset, x, y, 3) + is_irrigated * irrigation_bonus, 99);
}
void map_set_floodplain_growth(int grid_offset, int growth) {
    if (growth >= 0 && growth < 6)
        map_grid_set(&terrain_floodplain_growth, grid_offset, growth);
}
void map_soil_set_depletion(int grid_offset, int malus) {
    int new_fert = map_get_fertility(grid_offset, FERT_NO_MALUS) + malus;
    map_grid_set(&terrain_floodplain_fertility, grid_offset, max(3, min(99, new_fert)));
}

io_buffer *iob_soil_fertility_grid = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_GRID, &terrain_floodplain_fertility);
});