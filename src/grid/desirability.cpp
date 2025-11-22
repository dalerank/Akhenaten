#include "desirability.h"

#include "building/building.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "city/city.h"
#include "js/js_game.h"

grid_xx g_desirability_grid = {0, FS_INT8};
 
desirability_t ANK_VARIABLE_N(g_desirability, "desirability");

void desirability_t::add_to_terrain_at_distance(tile2i tile, int size, int distance, int desirability) {
    int partially_outside_map = 0;
    int x = tile.x();
    int y = tile.y();
    if (x - distance < -1 || x + distance + size - 1 > scenario_map_data()->width) {
        partially_outside_map = 1;
    }

    if (y - distance < -1 || y + distance + size - 1 > scenario_map_data()->height) {
        partially_outside_map = 1;
    }

    int base_offset = MAP_OFFSET(x, y);
    int start = map_ring_start(size, distance);
    int end = map_ring_end(size, distance);

    if (partially_outside_map) {
        for (int i = start; i < end; i++) {
            const ring_tile* tile = map_ring_tile(i);
            if (map_ring_is_inside_map(x + tile->x, y + tile->y)) {
                int newd = map_grid_get(g_desirability_grid, base_offset + tile->grid_offset) + desirability;
                map_grid_set(g_desirability_grid, base_offset + tile->grid_offset, calc_bound(newd, -100, 100));
            }
        }
    } else {
        for (int i = start; i < end; i++) {
            const ring_tile* tile = map_ring_tile(i);
            int newd = map_grid_get(g_desirability_grid, base_offset + tile->grid_offset) + desirability;
            map_grid_set(g_desirability_grid, base_offset + tile->grid_offset, calc_bound(newd, -100, 100));
        }
    }
}

void desirability_t::add_to_terrain(tile2i tile, int size, int desirability, int step, int step_size, int range) {
    if (size <= 0) {
        return;
    }

    range = std::min(range, 6);
    int tiles_within_step = 0;
    int distance = 1;
    while (range > 0) {
        add_to_terrain_at_distance(tile, size, distance, desirability);
        distance++;
        range--;
        tiles_within_step++;
        if (tiles_within_step >= step) {
            desirability += step_size;
            tiles_within_step = 0;
        }
    }
}

void desirability_t::update_buildings() {
    buildings_valid_do([this] (building &b) {
        const auto &desirability = b.des_influence;
        add_to_terrain(b.tile, b.size, desirability.value, desirability.step, desirability.step_size, desirability.range);
    });
}

void desirability_t::update_terrain() {
    int grid_offset = scenario_map_data()->start_offset;
    tile2i tile(grid_offset);
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            int terrain = map_terrain_get(grid_offset);
            tile2i tile(x, y);
            influence_t tileinf;
            if (map_property_is_plaza_or_earthquake(tile)) {                
                if (terrain & TERRAIN_ROAD) {
                    tileinf = env_influence.plaza;
                } else if (terrain & TERRAIN_ROCK) {
                    // earthquake fault line: slight negative
                    tileinf = env_influence.earthquake;
                } else {
                    // invalid plaza/earthquake flag
                    assert(false);
                    map_property_clear_plaza_or_earthquake(grid_offset);
                    continue;
                }
            } else if (terrain & TERRAIN_GARDEN) {
                tileinf = env_influence.garden;
            } else if (terrain & TERRAIN_RUBBLE) {
                tileinf = env_influence.rubble;
            }

            if (tileinf.size > 0) {
                add_to_terrain(tile, tileinf.size, tileinf.value, tileinf.step, tileinf.step_size, tileinf.range);
            }
        }
    }
}

void desirability_t::clear_map() {
    map_grid_clear(g_desirability_grid);
}

void desirability_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Desirability Update");
    clear_map();
    update_buildings();
    update_terrain();
}

int desirability_t::get(int grid_offset) {
    return map_grid_get(g_desirability_grid, grid_offset);
}

int desirability_t::get_max(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_desirability_grid, tile.grid_offset());
    }

    int max = -9999;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            tile2i t = tile.shifted(dx, dy);
            int value = map_grid_get(g_desirability_grid, t.grid_offset());
            max = std::max(value, max);
        }
    }
    return max;
}

int desirability_t::get_avg(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_desirability_grid, tile.grid_offset());
    }
    grid_area area = map_grid_get_area(tile.shifted(-size, -size), tile.shifted(size, size));

    int summ = 0;
    int count = 1;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            summ += map_grid_get(g_desirability_grid, grid_offset);
            count++;
        }
    }

    return summ / count;
}

io_buffer* iob_desirability_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_desirability_grid);
});
