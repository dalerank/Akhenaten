#include "floodplain.h"

#include "building_tiles.h"
#include "building/building_farm.h"
#include "game/game_config.h"
#include "scenario/map.h"
#include "grid/tiles.h"
#include "terrain.h"
#include "water.h"
#include "graphics/image.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/random.h"
#include "city/city_floods.h"
#include "grid/building.h"
#include "core/calc.h"
#include "city/city.h"
#include "city/city_industry.h"
#include "js/js_game.h"

#include <cstdint>
#include <algorithm>
#include <random>

constexpr uint32_t PH_FLOODPLAIN_GROWTH_MAX = 6;

tile_cache floodplain_tiles_cache;
tile_cache floodplain_tiles_caches_by_row[MAX_FLOODPLAIN_ROWS + 1];
tile_cache floodplain_tiles_random;
tile_cache floodplain_tiles_local;

image_desc floodplain_tile;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_floodplain) {
    g_config_arch.r_section("floodplain", [] (archive arch) {
        arch.r_desc("floodplain_tile", floodplain_tile);
    });
}

void foreach_floodplain_row(int is_flooding, int row, void (*callback)(int is_flooding, int grid_offset, int order)) {
    if (row < 0 || row > MAX_FLOODPLAIN_ROWS) {
        return;
    }

    auto &cache = floodplain_tiles_caches_by_row[row];
    for (int grid_offset: cache) {
        callback(is_flooding, grid_offset, row);
    }
}

grid_xx g_terrain_floodplain_row = {0, FS_UINT8};
grid_xx g_terrain_floodplain_growth = { 0, FS_UINT8 };
grid_xx g_terrain_floodplain_fertility = {0, FS_UINT8};
grid_xx g_terrain_floodplain_max_fertile = {0, FS_UINT8};
grid_xx g_terrain_floodplain_flood_shore = {0, FS_UINT8};

void map_floodplain_advance_growth() {
    static int floodplain_growth_advance = 0;
    // do groups of 12 rows at a time. every 12 cycle, do another pass over them.
    if (!!game_features::gameplay_floodplain_random_grow) {
        //foreach_floodplain_row(0 + floodplain_growth_advance, map_floodplain_adv_growth_tile);
        floodplain_tiles_local.clear();
        std::copy_if(floodplain_tiles_random.begin(), floodplain_tiles_random.end(), std::back_inserter(floodplain_tiles_local), [] (auto grid_offset) {
            int value = map_image_alt_at(grid_offset);
            int image_id = (value & 0x00ffffff);
            int want_growth = map_get_floodplain_growth(grid_offset);
            return (image_id == 0 || want_growth == 0);
        });

        std::random_device rd;
        std::mt19937 random(rd());
        std::shuffle(floodplain_tiles_local.begin(), floodplain_tiles_local.end(), random);

        int size = std::min(floodplain_tiles_random.size() / 12, floodplain_tiles_local.size());
        for (int i = 0; i < size; ++i) {
            int grid_offset = floodplain_tiles_local[i];
            map_floodplain_adv_growth_tile(0, grid_offset, 0);
        }
    } else {
        foreach_floodplain_row(0, 0 + floodplain_growth_advance, map_floodplain_adv_growth_tile);
        foreach_floodplain_row(0, 12 + floodplain_growth_advance, map_floodplain_adv_growth_tile);
        foreach_floodplain_row(0, 24 + floodplain_growth_advance, map_floodplain_adv_growth_tile);

        floodplain_growth_advance++;
        if (floodplain_growth_advance >= 12) {
            floodplain_growth_advance = 0;
        }
    }
}

void map_floodplain_sub_growth() {
    if (!game_features::gameplay_floodplain_random_grow) {
        return;
    }
    
    for (auto grid_offset : floodplain_tiles_cache) {
        if (!map_get_floodplain_growth(grid_offset)) {
            continue;
        }
        map_floodplain_sub_growth_tile(grid_offset, 0);
    }
}

static void map_floodplain_update_inundation_row(int floodplain_is_flooding, int grid_offset, int order) {
    int randm = map_random_get(grid_offset);
    int ticks = g_floods.fticks;
    int local_tick_bound = calc_bound(ticks - order * 25, 0, 25);
    bool flooded = randm % 25 < local_tick_bound;

    int b_id = map_building_at(grid_offset);
    building_farm* farm = building_get(b_id)->dcast_farm();

    // tile is FLOODING
    if (floodplain_is_flooding == 1) {
        // tile is updating!
        if (flooded == map_terrain_is(grid_offset, TERRAIN_WATER)) {
            return;
        }

        map_terrain_add(grid_offset, TERRAIN_WATER);

        map_soil_set_depletion(grid_offset, 0);

        // hide / destroy farm
        if (farm && farm->is_valid() && map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            if (g_city.religion.osiris_flood_will_destroy_active > 0) { // destroy farm
                farm->deplete_soil();
                farm->destroy_by_poof(/*clouds*/false);
                g_city.religion.osiris_flood_will_destroy_active = 2;
                for (int _y = farm->tiley(); _y < farm->tiley() + farm->size(); _y++) {
                    for (int _x = farm->tilex(); _x < farm->tilex() + farm->size(); _x++) {
                        int _offset = MAP_OFFSET(_x, _y);
                        map_soil_set_depletion(_offset, -65);
                        map_terrain_remove(_offset, TERRAIN_BUILDING);
                        //                            map_property_set_multi_tile_size(_offset, 1);
                        map_refresh_river_image_at(_offset, true);
                    }
                }
            } else { // hide building by unsetting the TERRAIN_BUILDING bitflag
                auto &d = farm->runtime_data();
                d.progress = 0;
                d.labor_state = LABOR_STATE_NONE;
                d.labor_days_left = 0;
                for (int _y = farm->tiley(); _y < farm->tiley() + farm->size(); _y++) {
                    for (int _x = farm->tilex(); _x < farm->tilex() + farm->size(); _x++) {
                        int _offset = MAP_OFFSET(_x, _y);
                        map_terrain_remove(_offset, TERRAIN_BUILDING);
                        map_property_set_multi_tile_size(_offset, 1);
                        map_refresh_river_image_at(_offset, true);
                    }
                }
            }
        }

        // flood roads
        if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
            map_terrain_remove(grid_offset, TERRAIN_ROAD);
            map_terrain_add(grid_offset, TERRAIN_SUBMERGED_ROAD);
        }

    } else if (floodplain_is_flooding == -1) { // tile is RESURFACING
        map_terrain_remove(grid_offset, TERRAIN_WATER);

        // bring back flooded buildings
        if (farm && farm->state() == BUILDING_STATE_VALID && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            // check if any other tile of the farm is still submerged
            bool still_flooded = false;
            for (int _y = farm->tiley(); _y < farm->tiley() + farm->size(); _y++) {
                for (int _x = farm->tilex(); _x < farm->tilex() + farm->size(); _x++) {
                    if (map_terrain_is(MAP_OFFSET(_x, _y), TERRAIN_WATER)) {
                        still_flooded = true;
                    }
                }
            }

            if (!still_flooded) {                
                farm->add_tiles();
            }
        }

        // resurface roads
        if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
            map_terrain_remove(grid_offset, TERRAIN_SUBMERGED_ROAD);
            map_terrain_add(grid_offset, TERRAIN_ROAD);
        } else {
            int fertility_value = map_get_fertility(grid_offset, FERT_WITH_MALUS);
            int fertility_index = std::clamp(fertility_value / 25, 0, 3);
            int image_id = image_group(floodplain_tile);
            image_id += 12 * fertility_index;
            map_image_set(grid_offset, image_id);
        }
    }
    map_refresh_river_image_at(grid_offset, true);
}

void map_floodplain_update_inundation(int leading_row, int is_flooding, int flooding_ticks) {
    if (is_flooding == 0) {
        return;
    }
    // no need to update every single row -- only update the "leading" shore
    foreach_floodplain_row(is_flooding, 29 - leading_row, map_floodplain_update_inundation_row);
}

int map_floodplain_rebuild_rows() {
    // reset all to zero
    map_grid_fill(g_terrain_floodplain_row, -1);
    map_grid_fill(g_terrain_floodplain_max_fertile, 0);

    for (int row = 0; row < MAX_FLOODPLAIN_ROWS; row++) {
        floodplain_tiles_caches_by_row[row].clear();
    }

    foreach_river_tile([&] (int tile_offset) {
        bool is_vergin_floodplain = map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN);
        if (is_vergin_floodplain) {
            floodplain_tiles_random.push_back(tile_offset);
        }
    });

    std::random_device rd;
    std::mt19937 random(rd());
    std::shuffle(floodplain_tiles_random.begin(), floodplain_tiles_random.end(), random);

    // fill in shore order data
    for (int row = -1; row < MAX_FLOODPLAIN_ROWS - 1; row++) {
        int found_floodplain_tiles_in_row = 0;

        // go through every river tile
        foreach_river_tile([&] (int tile_offset) {
            // get current river tile's grid offset and coords
            tile2i tile(tile_offset);

            bool is_vergin_water = (row == -1 && map_terrain_is(tile_offset, TERRAIN_WATER) && !map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN));
            bool is_vergin_floodplain = (row > -1 && map_terrain_is(tile_offset, TERRAIN_FLOODPLAIN) && map_get_floodplain_row(tile_offset) == row);

            // loop through every virgin water tile or, 
            // through every floodplain tile of the previous round
            if (is_vergin_water || is_vergin_floodplain) { 

                // loop through for a 3x3 area around the tile
                tile2i tmin = tile.shifted(-1, -1);
                tile2i tmax = tile.shifted(1, 1);

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
                            map_grid_set(g_terrain_floodplain_max_fertile, grid_offset, tile_fert);

                            // set the shore order cache
                            map_grid_set(g_terrain_floodplain_row, grid_offset, row + 1);
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

    // if past 29, clamp all the rest into the last processable row
    for (auto grid_offset: floodplain_tiles_cache) {
        if (map_get_floodplain_row(grid_offset) == -1) {
            map_grid_set(g_terrain_floodplain_row, grid_offset, MAX_FLOODPLAIN_ROWS - 1);
            floodplain_tiles_caches_by_row[MAX_FLOODPLAIN_ROWS - 1].push_back(grid_offset);
        }
    }

    return MAX_FLOODPLAIN_ROWS;
}

void map_floodplain_rebuild_shores() {
    map_grid_fill(g_terrain_floodplain_flood_shore, 0);

    foreach_river_tile([&] (int tile_offset) {
        // get current river tile's grid offset and coords
        tile2i tile(tile_offset);
        grid_area area = map_grid_get_area(tile, 1, 1);

        map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i shore) {
            if (map_get_floodplain_edge(shore)) {
                return;
            }

            int base_offset = shore.grid_offset();
            if (map_terrain_is(base_offset, TERRAIN_WATER) || map_terrain_is(base_offset, TERRAIN_FLOODPLAIN)) {
                return;
            }

            offsets_array offsets;
            map_grid_adjacent_offsets_xy(1, 1, offsets);
            for (const auto &tile_delta: offsets) {
                int grid_offset = base_offset + tile_delta;
                if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
                    map_grid_set(g_terrain_floodplain_flood_shore, base_offset, 1);
                    break;
                }
            }
        });
    });
}

int8_t map_get_floodplain_row(int grid_offset) {
    return map_grid_get(g_terrain_floodplain_row, grid_offset);
}

uint8_t map_get_floodplain_growth(int grid_offset) {
    return map_grid_get(g_terrain_floodplain_growth, grid_offset);
}

void map_clear_floodplain_growth() {
    map_grid_fill(g_terrain_floodplain_growth, 0);
}

void set_floodplain_land_tiles_image(int grid_offset, bool force) {
    bool is_floodpain = map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)
                            && !map_terrain_is(grid_offset, TERRAIN_WATER)
                            && !map_terrain_is(grid_offset, TERRAIN_BUILDING)
                            && !map_terrain_is(grid_offset, TERRAIN_ROAD)
                            && !map_terrain_is(grid_offset, TERRAIN_CANAL);

    if (!is_floodpain) {
        return;
    }

    int growth = map_get_floodplain_growth(grid_offset);
    int image_id = image_group(floodplain_tile) + growth;
    int image_alt_id = image_id;
    int fertility_index = 0;

    int fertility_value = map_get_fertility(grid_offset, FERT_WITH_MALUS);
    fertility_index = std::clamp(fertility_value / 25, 0, 3);
    int fertility_next_index = std::clamp(fertility_index + 1, 0, 3);
    int alpha = std::clamp((fertility_value % 25) * 10, 0, 0xff);

    image_id += 12 * fertility_index;
    image_alt_id += 12 * fertility_next_index;
    if (map_property_is_alternate_terrain(grid_offset) && fertility_index < 7) {
        image_id += 6;
        image_alt_id += 6;
    }

    if (force) {
        map_image_set(grid_offset, image_id);
    } else {
        if (!!game_features::gameplay_floodplain_random_grow) {
            map_image_alt_set(grid_offset, image_alt_id, -1);
        } else {
            map_image_set(grid_offset, image_id);
        }
    }

    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
}

void map_floodplain_adv_growth_tile(int _, int grid_offset, int /*order*/) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER) || map_terrain_is(grid_offset, TERRAIN_BUILDING)
        || map_terrain_is(grid_offset, TERRAIN_ROAD) || map_terrain_is(grid_offset, TERRAIN_CANAL)) {
        map_set_floodplain_growth(grid_offset, 0);
        set_floodplain_land_tiles_image(grid_offset, false);
        map_refresh_river_image_at(grid_offset, false);
        return;
    }

    int growth_current = map_get_floodplain_growth(grid_offset);
    if (growth_current < PH_FLOODPLAIN_GROWTH_MAX - 1) {
        map_set_floodplain_growth(grid_offset, growth_current + 1);
        set_floodplain_land_tiles_image(grid_offset, false);
        map_refresh_river_image_at(grid_offset, false);
    }
}

void map_floodplain_sub_growth_tile(int grid_offset, int order) {
    int value = map_image_alt_at(grid_offset);
    int image_id = (value & 0x00ffffff);
    if (image_id <= 0) {
        return;
    }

    int bid = map_building_at(grid_offset);
    if (bid) {
        return;
    }

    int alpha = (value >> 24) & 0xff;
    if (alpha + 1 > 0xfe) {
        map_image_set(grid_offset, image_id);
        map_image_alt_set(grid_offset, 0, 0);
    } else {
        map_image_alt_set(grid_offset, -1, alpha + 5);
    }
}

void map_image_set_road_floodplain(tile2i tile) {
    const int grid_offset = tile.grid_offset();
    const terrain_image img = map_image_context_get_dirt_road(tile);
    if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_FLOODPLAIN)) {
        map_image_set(grid_offset, image_group(floodplain_tile) + 84);
    } else if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_FLOODPLAIN)) {
        map_image_set(grid_offset, image_group(floodplain_tile) + 85);
    } else if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_FLOODPLAIN)) {
        map_image_set(grid_offset, image_group(floodplain_tile) + 86);
    } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_FLOODPLAIN)) {
        map_image_set(grid_offset, image_group(floodplain_tile) + 87);
    } else {
        int base_img = building_static_params::get(BUILDING_ROAD).base_img();
        map_image_set(grid_offset, base_img + img.group_offset + img.item_offset + 49);
    }
}

void set_floodplain_edges_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_BUILDING)
        || (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER))) { // non-flooded floodplain, skip
        return;
    }

    int image_id = 0;
    if (!map_terrain_is(grid_offset, TERRAIN_WATER)) { // NOT floodplain, but not water either -- dry land shoreline
        if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
            return;
        }

        const terrain_image img = map_image_context_get_floodplain_shore(tile2i(grid_offset)); // this checks against FLOODPLAIN tiles
        image_id = image_group(floodplain_tile) + 48 + img.group_offset + img.item_offset;

    } else { // floodplain which is ALSO flooded --  this is a waterline
        const terrain_image img = map_image_context_get_floodplain_waterline(tile2i(grid_offset)); // this checks against WATER tiles
        image_id = image_id_from_group(GROUP_TERRAIN_FLOODSYSTEM) + 209 + img.group_offset + img.item_offset;
        if (!img.is_valid) { // else, normal water tile
            image_id = 0;
        }
        //            image_id = image_id_from_group(GROUP_TERRAIN_BLACK); // temp

        //        if (map_terrain_is(grid_offset, TERRAIN_GROUNDWATER)) {
        //            if (map_terrain_get(grid_offset - 1) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset + 1) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset - 228) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset + 228) == TERRAIN_GROUNDWATER)
        //            image_id = 0;
        //        }
    }

    if (image_id) {
        map_image_set(grid_offset, image_id);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void map_tiles_update_floodplain_images() {
    auto callback = [] (int flooding, int grid_offset, int order) { map_refresh_river_image_at(grid_offset, true); };
    if (!!game_features::gameplay_floodplain_random_grow) {
        for (int i = 0; i < 12; ++i) {
            foreach_floodplain_row(0, 0 + i, callback);
        }
    } else {
        for (int i = 0; i < 12; ++i) {
            foreach_floodplain_row(0, 0 + i, callback);
            foreach_floodplain_row(0, 12 + i, callback);
            foreach_floodplain_row(0, 24 + i, callback);
        }
    }
}

int map_get_floodplain_edge(tile2i tile) {
    return map_grid_get(g_terrain_floodplain_flood_shore, tile.grid_offset());
}

int map_get_fertility(int grid_offset, int tally_type) { // actual percentage integer [0-99]
    switch (tally_type) {
    case FERT_WITH_MALUS:
        return map_grid_get(g_terrain_floodplain_fertility, grid_offset);
        break;

    case FERT_ONLY_MALUS:
        return map_grid_get(g_terrain_floodplain_fertility, grid_offset)
               - map_grid_get(g_terrain_floodplain_max_fertile, grid_offset);
        break;

    case FERT_NO_MALUS:
        return map_grid_get(g_terrain_floodplain_max_fertile, grid_offset);
        break;
    }
    return 0;
}

static uint8_t map_get_fertility_average(tile2i tile, int size) {
    // returns average of fertility in square starting on the top-left corner
    tile2i tmin = tile;
    tile2i tmax = tile.shifted(size - 1, size - 1);

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
    if (!!game_features::gameplay_fix_irrigation_range) {
        is_irrigated = map_terrain_exists_tile_in_area_with_type(tile, 3, TERRAIN_IRRIGATION_RANGE);
    } else {
        is_irrigated = map_terrain_exists_tile_in_radius_with_type(tile, 1, 2, TERRAIN_IRRIGATION_RANGE);
    }
    int irrigation_bonus = 40;

    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        irrigation_bonus = 20;
    }

    return std::min(2 + map_get_fertility_average(tile, 3) + is_irrigated * irrigation_bonus, 99);
}

void map_set_floodplain_growth(int grid_offset, int growth) {
    if (growth >= 0 && growth < 6) {
        map_grid_set(g_terrain_floodplain_growth, grid_offset, growth);
    }
}

void map_update_tile_fertility(int grid_offset, int delta) {
    int new_fert = map_get_fertility(grid_offset, FERT_WITH_MALUS) + delta;
    map_grid_set(g_terrain_floodplain_fertility, grid_offset, std::clamp(new_fert, 3, 99));
}

void map_soil_set_depletion(int grid_offset, int malus) {
    int new_fert = map_get_fertility(grid_offset, FERT_NO_MALUS) + malus;
    map_grid_set(g_terrain_floodplain_fertility, grid_offset, std::clamp(new_fert, 3, 99));
}

io_buffer* iob_soil_fertility_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_floodplain_fertility);
});

io_buffer* iob_terrain_floodplain_growth = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_floodplain_growth);
});