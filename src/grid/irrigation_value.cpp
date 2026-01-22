#include "irrigation_value.h"

#include "building/building.h"
#include "building/building_water_lift.h"
#include "building/building_irrigation_ditch.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "grid/grid.h"
#include "grid/ring.h"
#include "grid/terrain.h"
#include "grid/canals.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "city/city.h"

grid_xx g_irrigation_value_grid = {0, FS_INT8};

irrigation_value_t g_irrigation_value;

void irrigation_value_t::add_irrigation_at_distance(tile2i tile, int size, int distance, int value) {
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
            const ring_tile* ring_t = map_ring_tile(i);
            if (map_ring_is_inside_map(x + ring_t->x, y + ring_t->y)) {
                int grid_offset = base_offset + ring_t->grid_offset;
                int current = map_grid_get(g_irrigation_value_grid, grid_offset);
                int new_value = std::max(current, value);
                map_grid_set(g_irrigation_value_grid, grid_offset, new_value);
            }
        }
    } else {
        for (int i = start; i < end; i++) {
            const ring_tile* ring_t = map_ring_tile(i);
            int grid_offset = base_offset + ring_t->grid_offset;
            int current = map_grid_get(g_irrigation_value_grid, grid_offset);
            int new_value = std::max(current, value);
            map_grid_set(g_irrigation_value_grid, grid_offset, new_value);
        }
    }
}

void irrigation_value_t::add_irrigation(tile2i tile, int size, int base_value, int range) {
    if (size <= 0 || base_value <= 0) {
        return;
    }

    range = std::min(range, 20); // reasonable max range
    int distance = 1;
    int current_value = base_value;
    
    // Add value at distance 0 (the building/canal itself)
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            tile2i t = tile.shifted(dx, dy);
            if (map_ring_is_inside_map(t.x(), t.y())) {
                int grid_offset = t.grid_offset();
                int current = map_grid_get(g_irrigation_value_grid, grid_offset);
                int new_value = std::max(current, base_value);
                map_grid_set(g_irrigation_value_grid, grid_offset, new_value);
            }
        }
    }
    
    // Spread to surrounding tiles, decreasing by 2 each distance
    while (range > 0 && current_value > 0) {
        add_irrigation_at_distance(tile, size, distance, current_value);
        distance++;
        range--;
        current_value -= 2;
        if (current_value < 0) {
            current_value = 0;
        }
    }
}

void irrigation_value_t::update_water_lifts() {
    buildings_valid_do<building_water_lift>([this] (building_water_lift *water_lift) {
        // Check if has workers and water access
        if (water_lift->num_workers() <= 0) {
            return;
        }
        
        if (!water_lift->base.has_water_access) {
            return;
        }
        
        // Get base irrigation value from config
        const auto &params = water_lift->current_params();
        int base_value = params.base_irrigation_value;
        if (base_value == 0) {
            base_value = 20; // default value
        }
        
        int range = params.irrigation_radius;
        if (range == 0) {
            range = 2; // default range
        }
        
        add_irrigation(water_lift->tile(), params.building_size, base_value, range);
    });
}

void irrigation_value_t::update_canals() {
    // Get multiplier from irrigation_ditch config
    const auto &ditch_params = building_static_params::get(BUILDING_IRRIGATION_DITCH);
    int multiplier = 2; // default
    // Cast to static_params (safe because we know it's irrigation_ditch)
    const auto &ditch_static = static_cast<const building_irrigation_ditch::static_params&>(ditch_params);
    multiplier = ditch_static.canal_irrigation_value_multiplier;
    if (multiplier == 0) {
        multiplier = 2; // default
    }
    
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_CANAL)) {
                continue;
            }
            
            // Check if canal has water
            int canal_water = map_canal_at(grid_offset);
            if (canal_water <= 0) {
                continue;
            }
            
            // Canal with water spreads irrigation value
            // Base value based on water level multiplied by config value
            int base_value = canal_water * multiplier;
            int range = canal_water; // Range equals water level
            
            tile2i tile(grid_offset);
            add_irrigation(tile, 1, base_value, range);
        }
    }
}

void irrigation_value_t::clear_map() {
    map_grid_clear(g_irrigation_value_grid);
}

void irrigation_value_t::update() {
    OZZY_PROFILER_FUNCTION();
    clear_map();
    update_water_lifts();
    update_canals();
}

int irrigation_value_t::get(int grid_offset) {
    return map_grid_get(g_irrigation_value_grid, grid_offset);
}

int irrigation_value_t::get_max(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_irrigation_value_grid, tile.grid_offset());
    }

    int max = 0;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            tile2i t = tile.shifted(dx, dy);
            int value = map_grid_get(g_irrigation_value_grid, t.grid_offset());
            max = std::max(value, max);
        }
    }
    return max;
}

int irrigation_value_t::get_avg(tile2i tile, int size) {
    if (size == 1) {
        return map_grid_get(g_irrigation_value_grid, tile.grid_offset());
    }
    
    grid_area area = map_grid_get_area(tile, size, size);

    int summ = 0;
    int count = 0;
    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int grid_offset = MAP_OFFSET(x, y);
            summ += map_grid_get(g_irrigation_value_grid, grid_offset);
            count++;
        }
    }

    return count > 0 ? summ / count : 0;
}

io_buffer* iob_irrigation_value_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_irrigation_value_grid);
});

