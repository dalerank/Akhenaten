#include "floodplain.h"

#include "building_tiles.h"
#include "config/config.h"
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
grid_xx g_terrain_floodplain_flood_shore = {0, {FS_UINT8, FS_UINT8}};

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
        foreach_river_tile([&] (int tile_offset) {
            // get current river tile's grid offset and coords
            int tile_x = MAP_X(tile_offset);
            int tile_y = MAP_Y(tile_offset);

            bool is_vergin_water = (row == -1 && map_terrain_is(tile_offset, TERRAIN_WATER) && !map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN));
            bool is_vergin_floodplain = (row > -1 && map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN) && map_get_floodplain_row(tile_offset) == row);

            // loop through every virgin water tile or, 
            // through every floodplain tile of the previous round
            if (is_vergin_water || is_vergin_floodplain) { 

                // loop through for a 3x3 area around the tile
                tile2i tmin(tile_x - 1, tile_y - 1);
                tile2i tmax(tile_x + 1, tile_y + 1);

                map_grid_bound_area(tmin, tmax);
                int grid_offset = tmin.grid_offset();
                for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
                    for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
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
                    grid_offset += GRID_LENGTH - (tmax.x() - tmin.x() + 1);
                }
            }
        });

        // no more shore tiles, return!
        if (found_floodplain_tiles_in_row == 0) {
            return std::min(row + 2, MAX_FLOODPLAIN_ROWS);
        }
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

void map_floodplain_rebuild_shores() {
    map_grid_fill(&g_terrain_floodplain_flood_shore, 0);

    foreach_river_tile([&] (int tile_offset) {
        // get current river tile's grid offset and coords
        tile2i tile(tile_offset);

        grid_area area = map_grid_get_area(tile, 1, 1);

        map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i shore) {
            if (map_get_floodplain_edge(shore)) {
                return;
            }

            if (map_terrain_is(shore.grid_offset(), TERRAIN_WATER) || map_terrain_is(shore.grid_offset(), TERRAIN_FLOODPLAIN)) {
                return;
            }

            int base_offset = shore.grid_offset();
            offsets_array offsets;
            map_grid_adjacent_offsets_xy(1, 1, offsets);
            for (const auto &tile_delta: offsets) {
                int grid_offset = base_offset + tile_delta;
                if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
                    map_grid_set(&g_terrain_floodplain_flood_shore, base_offset, 1);
                    break;
                }
            }
        });
    });
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

int map_get_floodplain_edge(tile2i tile) {
    return map_grid_get(&g_terrain_floodplain_flood_shore, tile.grid_offset());
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

static uint8_t map_get_fertility_average(int x, int y, int size) {
    // returns average of fertility in square starting on the top-left corner
    tile2i tmin(x, y);
    tile2i tmax(x + size - 1, y + size - 1);

    int fert_total = 0;
    map_grid_bound_area(tmin, tmax);

    map_grid_area_foreach(tmin, tmax, [&] (tile2i tile) {
        fert_total += map_get_fertility(tile.grid_offset(), FERT_WITH_MALUS);
    });

    return fert_total / (size * size);
}

void map_update_area_fertility(int x, int y, int size, int delta) {
    // returns average of fertility in square starting on the top-left corner
    tile2i tmin(x, y);
    tile2i tmax(x + size - 1, y + size - 1);

    map_grid_bound_area(tmin, tmax);

    map_grid_area_foreach(tmin, tmax, [&] (tile2i tile) {
        map_update_tile_fertility(tile.grid_offset(), delta);
    });
}

uint8_t map_get_fertility_for_farm(int grid_offset) {
    tile2i tile(grid_offset);

    bool is_irrigated = false;
    if (config_get(CONFIG_GP_FIX_IRRIGATION_RANGE)) {
        is_irrigated = map_terrain_exists_tile_in_area_with_type(tile.x(), tile.y(), 3, TERRAIN_IRRIGATION_RANGE);
    } else {
        is_irrigated = map_terrain_exists_tile_in_radius_with_type(tile, 1, 2, TERRAIN_IRRIGATION_RANGE);
    }
    int irrigation_bonus = 40;

    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        irrigation_bonus = 20;
    }

    return std::min(2 + map_get_fertility_average(tile.x(), tile.y(), 3) + is_irrigated * irrigation_bonus, 99);
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