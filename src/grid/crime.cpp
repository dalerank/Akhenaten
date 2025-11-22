#include "crime.h"

#include "building/building.h"
#include "building/building_house.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "js/js_game.h"

grid_xx g_crime_grid = {0, FS_INT8};
 
crime_t ANK_VARIABLE_N(g_crime, "crime");

void crime_t::add_to_terrain_at_distance(tile2i tile, int size, int distance, int crime) {
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
                int newc = map_grid_get(g_crime_grid, base_offset + tile->grid_offset) + crime;
                map_grid_set(g_crime_grid, base_offset + tile->grid_offset, calc_bound(newc, -100, 100));
            }
        }
    } else {
        for (int i = start; i < end; i++) {
            const ring_tile* tile = map_ring_tile(i);
            int newc = map_grid_get(g_crime_grid, base_offset + tile->grid_offset) + crime;
            map_grid_set(g_crime_grid, base_offset + tile->grid_offset, calc_bound(newc, -100, 100));
        }
    }
}

void crime_t::add_to_terrain(tile2i tile, int size, int crime, int step, int step_size, int range) {
    if (size <= 0) {
        return;
    }

    range = std::min(range, 6);
    int tiles_within_step = 0;
    int distance = 1;
    while (range > 0) {
        add_to_terrain_at_distance(tile, size, distance, crime);
        distance++;
        range--;
        tiles_within_step++;
        if (tiles_within_step >= step) {
            crime += step_size;
            tiles_within_step = 0;
        }
    }
}

void crime_t::update_buildings() {
    buildings_valid_do([this] (building &b) {
        const auto &crime_influence = b.crime_influence;
        if (crime_influence.size > 0 || crime_influence.value != 0) {
            add_to_terrain(b.tile, b.size, crime_influence.value, crime_influence.step, crime_influence.step_size, crime_influence.range);
        }
    });
}

void crime_t::update_houses() {
    buildings_house_do([this] (building_house *house) {
        if (!house->house_population()) {
            return;
        }

        auto &housed = house->runtime_data();
        int criminal_active = housed.criminal_active;
        
        if (criminal_active > 0) {
            int crime_value = criminal_active / 10; // 0-10
            int range = 2; 
            add_to_terrain(house->tile(), house->size(), crime_value, 1, -1, range);
        }
    });
}

void crime_t::update_terrain() {
    
}

void crime_t::clear_map() {
    map_grid_clear(g_crime_grid);
}

void crime_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Crime Update");
    clear_map();
    update_buildings();
    update_houses();
    update_terrain();
}

int crime_t::get(int grid_offset) {
    return map_grid_get(g_crime_grid, grid_offset);
}

int crime_t::get_max(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_crime_grid, tile.grid_offset());
    }

    int max = -9999;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            tile2i t = tile.shifted(dx, dy);
            int value = map_grid_get(g_crime_grid, t.grid_offset());
            max = std::max(value, max);
        }
    }
    return max;
}

int crime_t::get_avg(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_crime_grid, tile.grid_offset());
    }
    grid_area area = map_grid_get_area(tile.shifted(-size, -size), tile.shifted(size, size));

    int summ = 0;
    int count = 1;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            summ += map_grid_get(g_crime_grid, grid_offset);
            count++;
        }
    }

    return summ / count;
}

io_buffer* iob_crime_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_crime_grid);
});

