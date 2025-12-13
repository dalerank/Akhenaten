#include "malaria_risk.h"

#include "building/building.h"
#include "building/building_type.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "grid/trees.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "city/city.h"

grid_xx g_malaria_risk_grid = {0, FS_INT8};

malaria_risk_t ANK_VARIABLE_N(g_malaria_risk, "malaria_risk");

static void add_tree_malaria_reduction(int grid_offset) {
    tile2i tile(grid_offset);
    g_malaria_risk.add_to_terrain(tile, 1, g_malaria_risk.tree_risk, 1, g_malaria_risk.tree_step_delta, g_malaria_risk.tree_risk_range);
}

void malaria_risk_t::add_to_terrain_at_distance(tile2i tile, int size, int distance, int risk) {
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
                int new_risk = map_grid_get(g_malaria_risk_grid, base_offset + tile->grid_offset) + risk;
                map_grid_set(g_malaria_risk_grid, base_offset + tile->grid_offset, calc_bound(new_risk, 0, max_risk));
            }
        }
    } else {
        for (int i = start; i < end; i++) {
            const ring_tile* tile = map_ring_tile(i);
            int new_risk = map_grid_get(g_malaria_risk_grid, base_offset + tile->grid_offset) + risk;
            map_grid_set(g_malaria_risk_grid, base_offset + tile->grid_offset, calc_bound(new_risk, 0, max_risk));
        }
    }
}

void malaria_risk_t::add_to_terrain(tile2i tile, int size, int risk, int step, int step_size, int range) {
    if (size <= 0) {
        return;
    }

    range = std::min<int>(range, max_range);
    int tiles_within_step = 0;
    int distance = 1;
    while (range > 0) {
        add_to_terrain_at_distance(tile, size, distance, risk);
        distance++;
        range--;
        tiles_within_step++;
        if (tiles_within_step >= step) {
            risk += step_size;
            tiles_within_step = 0;
        }
    }
}

void malaria_risk_t::update_buildings() {
    buildings_valid_do([this] (building &b) {
        if (b.type == BUILDING_APOTHECARY && b.state == BUILDING_STATE_VALID && b.num_workers > 0) {
            add_to_terrain(b.tile, b.size, -30, 1, 0, 3);
        }
    });

    buildings_valid_do([this] (building &b) {
        if (b.type == BUILDING_WELL) {
            add_to_terrain(b.tile, b.size, -20, 1, 0, 4);
        }
    });
}

void malaria_risk_t::update_terrain() {
    int grid_offset = scenario_map_data()->start_offset;
    tile2i tile(grid_offset);
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            int terrain = map_terrain_get(grid_offset);
            tile2i tile(x, y);
            
            if (terrain & TERRAIN_WATER) {
                add_to_terrain(tile, 1, water_risk, 1, water_step_delta, water_risk_range);
            }
            
            if (terrain & TERRAIN_FLOODPLAIN) {
                add_to_terrain(tile, 1, floodplain_risk, 1, floodplain_step_delta, floodplain_risk_range);
            }
            
            if (terrain & TERRAIN_MARSHLAND) {
                add_to_terrain(tile, 1, marshland_risk, 1, marshland_step_delta, marshland_risk_range);
            }
        }
    }

    // Trees reduce malaria risk around them
    if (tree_risk < 0 && tree_risk_range > 0) {
        map_tree_foreach_tile(add_tree_malaria_reduction);
    }
}

void malaria_risk_t::clear_map() {
    map_grid_clear(g_malaria_risk_grid);
}

void malaria_risk_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Malaria Risk Update");
    clear_map();
    update_terrain();
    update_buildings();
}

int malaria_risk_t::get(int grid_offset) {
    return map_grid_get(g_malaria_risk_grid, grid_offset);
}

int malaria_risk_t::get_max(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_malaria_risk_grid, tile.grid_offset());
    }

    int max = 0;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            tile2i t = tile.shifted(dx, dy);
            int value = map_grid_get(g_malaria_risk_grid, t.grid_offset());
            max = std::max(value, max);
        }
    }
    return max;
}

int malaria_risk_t::get_avg(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_malaria_risk_grid, tile.grid_offset());
    }
    grid_area area = map_grid_get_area(tile.shifted(-size, -size), tile.shifted(size, size));

    int summ = 0;
    int count = 1;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            summ += map_grid_get(g_malaria_risk_grid, grid_offset);
            count++;
        }
    }

    return summ / count;
}

io_buffer* iob_malaria_risk_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_malaria_risk_grid);
});

