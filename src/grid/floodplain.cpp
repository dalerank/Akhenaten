#include "floodplain.h"

#include "building_tiles.h"
#include "io/config/config.h"
#include "scenario/map.h"
#include "grid/tiles.h"
#include "terrain.h"
#include "water.h"

#include <cstdint>
#include <algorithm>

tile_cache floodplain_tiles_cache;
tile_cache floodplain_tiles_caches_by_row[MAX_FLOODPLAIN_ROWS + 1];

void foreach_floodplain_row(int row, void (*callback)(int grid_offset, int order)) {
    if (row < 0 || row > MAX_FLOODPLAIN_ROWS) {
        return;
    }

    auto &cache = floodplain_tiles_caches_by_row[row];
    for (const auto &grid_offset: cache) {
        callback(grid_offset, row);
    }
}

grid_xx g_terrain_floodplain_row = {0, {FS_UINT8, FS_UINT8}};
grid_xx g_terrain_floodplain_growth = {0, {FS_UINT8, FS_UINT8}};
grid_xx g_terrain_floodplain_fertility = {0, {FS_UINT8, FS_UINT8}};
grid_xx g_terrain_floodplain_max_fertile = {0, {FS_UINT8, FS_UINT8}};

int map_floodplain_rebuild_rows() {
    // reset all to zero
    map_grid_fill(&g_terrain_floodplain_row, -1);
    map_grid_fill(&g_terrain_floodplain_max_fertile, 0);

    for (int row = 0; row < MAX_FLOODPLAIN_ROWS; row++) {
        floodplain_tiles_caches_by_row[row].clear();
    }

    // fill in shore order data
    for (int row = -1; row < MAX_FLOODPLAIN_ROWS - 1; row++) {
        int found_floodplain_tiles_in_row = 0;

        // go through every river tile
        for (int i = 0; i < river_tiles_cache.size(); i++) {
            // get current river tile's grid offset and coords
            int tile_offset = river_tiles_cache.at(i);
            int tile_x = MAP_X(tile_offset);
            int tile_y = MAP_Y(tile_offset);

            bool is_vergin_water = (row == -1 && map_terrain_is(tile_offset, TERRAIN_WATER)
                                    && !map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN));
            bool is_vergin_floodplain = (row > -1 && map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN)
                                         && map_get_floodplain_row(tile_offset) == row);

            if (is_vergin_water            // loop through every virgin water tile
                || is_vergin_floodplain) { // or, through every floodplain tile of the previous round

                // loop through for a 3x3 area around the tile
                int x_min = tile_x - 1;
                int x_max = tile_x + 1;
                int y_min = tile_y - 1;
                int y_max = tile_y + 1;

                map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
                int grid_offset = MAP_OFFSET(x_min, y_min);
                for (int yy = y_min; yy <= y_max; yy++) {
                    for (int xx = x_min; xx <= x_max; xx++) {
                        // do only on floodplain tiles that haven't been calculated / cached yet
                        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) 
                            && map_grid_is_valid_offset(grid_offset)
                            && map_get_floodplain_row(grid_offset) == -1) {
                            // set fertility data
                            int tile_fert = 99 - ((99.0f / 30.0f) * (float)(row + 1));
                            map_grid_set(&g_terrain_floodplain_max_fertile, grid_offset, tile_fert);

                            // set the shore order cache
                            map_grid_set(&g_terrain_floodplain_row, grid_offset, row + 1);
                            floodplain_tiles_caches_by_row[row + 1].push_back(grid_offset);

                            // advance counter
                            found_floodplain_tiles_in_row++;
                        }
                        ++grid_offset;
                    }
                    grid_offset += GRID_LENGTH - (x_max - x_min + 1);
                }
            }
        }

        // no more shore tiles, return!
        if (found_floodplain_tiles_in_row == 0)
            return std::min(row + 2, MAX_FLOODPLAIN_ROWS);
    }

    // if past 29, fill in all the rest with the same order
    for (int i = 0; i < floodplain_tiles_cache.size(); i++) {
        int grid_offset = floodplain_tiles_cache.at(i);

        if (map_get_floodplain_row(grid_offset) == -1) {
            map_grid_set(&g_terrain_floodplain_row, grid_offset, MAX_FLOODPLAIN_ROWS);
            floodplain_tiles_caches_by_row[MAX_FLOODPLAIN_ROWS].push_back(grid_offset);
        }
    }

    return MAX_FLOODPLAIN_ROWS;
}

int8_t map_get_floodplain_row(int grid_offset) {
    return map_grid_get(&g_terrain_floodplain_row, grid_offset);
}

uint8_t map_get_floodplain_growth(int grid_offset) {
    return map_grid_get(&g_terrain_floodplain_growth, grid_offset);
}

void map_clear_floodplain_growth() {
    map_grid_fill(&g_terrain_floodplain_growth, 0);
}

void map_tiles_update_floodplain_images() {
    auto callback = [] (int grid_offset, int order) { map_refresh_river_image_at(grid_offset); };
    for (int i = 0; i < 12; ++i) {
        foreach_floodplain_row(0 + i, callback);
        foreach_floodplain_row(12 + i, callback);
        foreach_floodplain_row(24 + i, callback);
    }
}

int map_get_fertility(int grid_offset, int tally_type) { // actual percentage integer [0-99]
    switch (tally_type) {
    case FERT_WITH_MALUS:
        return map_grid_get(&g_terrain_floodplain_fertility, grid_offset);
        break;

    case FERT_ONLY_MALUS:
        return map_grid_get(&g_terrain_floodplain_fertility, grid_offset)
               - map_grid_get(&g_terrain_floodplain_max_fertile, grid_offset);
        break;

    case FERT_NO_MALUS:
        return map_grid_get(&g_terrain_floodplain_max_fertile, grid_offset);
        break;
    }
    return 0;
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
        grid_offset += GRID_LENGTH - (x_max - x_min + 1);
    }
    return fert_total / (size * size);
}

void map_update_area_fertility(int grid_offset, int x, int y, int size, int delta) {
    // returns average of fertility in square starting on the top-left corner
    int x_min = x;
    int y_min = y;
    int x_max = x_min + size - 1;
    int y_max = y_min + size - 1;

    map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            map_update_tile_fertility(grid_offset, delta);
            ++grid_offset;
        }
        grid_offset += GRID_LENGTH - (x_max - x_min + 1);
    }
}

uint8_t map_get_fertility_for_farm(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    bool is_irrigated = false;
    if (config_get(CONFIG_GP_FIX_IRRIGATION_RANGE)) {
        is_irrigated = map_terrain_exists_tile_in_area_with_type(x, y, 3, TERRAIN_IRRIGATION_RANGE);
    } else {
        is_irrigated = map_terrain_exists_tile_in_radius_with_type(x, y, 1, 2, TERRAIN_IRRIGATION_RANGE);
    }
    int irrigation_bonus = 40;

    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        irrigation_bonus = 20;
    }

    return std::min(2 + map_get_fertility_average(grid_offset, x, y, 3) + is_irrigated * irrigation_bonus, 99);
}

void map_set_floodplain_growth(int grid_offset, int growth) {
    if (growth >= 0 && growth < 6) {
        map_grid_set(&g_terrain_floodplain_growth, grid_offset, growth);
    }
}

void map_update_tile_fertility(int grid_offset, int delta) {
    int new_fert = map_get_fertility(grid_offset, FERT_WITH_MALUS) + delta;
    map_grid_set(&g_terrain_floodplain_fertility, grid_offset, std::clamp(new_fert, 3, 99));
}

void map_soil_set_depletion(int grid_offset, int malus) {
    int new_fert = map_get_fertility(grid_offset, FERT_NO_MALUS) + malus;
    map_grid_set(&g_terrain_floodplain_fertility, grid_offset, std::clamp(new_fert, 3, 99));
}

io_buffer* iob_soil_fertility_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_floodplain_fertility);
});

io_buffer* iob_terrain_floodplain_growth = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_floodplain_growth);
});