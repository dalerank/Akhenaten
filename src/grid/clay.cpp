#include "clay.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <vector>
#include <algorithm>
#include <cmath>

grid_xx g_terrain_clay = {0, FS_UINT16};

int map_get_clay(int grid_offset) {
    return map_grid_get(g_terrain_clay, grid_offset);
}

void map_clay_deplete(int grid_offset, int amount) {
    int current = map_grid_get(g_terrain_clay, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(g_terrain_clay, grid_offset, new_value);
    }
}

void map_clay_init() {
    // Initialize clay grid: mark all tiles within 2 tiles of water with value 65000
    constexpr int CLAY_MAX = 65000;
    constexpr int RADIUS = 2;
    
    int grid_offset = scenario_map_data()->start_offset;
    int map_width = scenario_map_data()->width;
    int map_height = scenario_map_data()->height;
    
    // First pass: identify all water tiles and mark them
    std::vector<tile2i> water_tiles;
    for (int y = 0; y < map_height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            // Check for water: TERRAIN_WATER, TERRAIN_DEEPWATER, or floodplain with water
            if (map_terrain_is(grid_offset, TERRAIN_WATER) || 
                map_terrain_is(grid_offset, TERRAIN_DEEPWATER) ||
                map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN | TERRAIN_WATER)) {
                water_tiles.push_back(tile2i(grid_offset));
            }
            // Initialize all tiles to 0
            map_grid_set(g_terrain_clay, grid_offset, 0);
        }
    }
    
    grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < map_height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            // Skip water tiles - clay should not be on water
            if (map_terrain_is(grid_offset, TERRAIN_WATER) || 
                map_terrain_is(grid_offset, TERRAIN_DEEPWATER) ||
                map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN | TERRAIN_WATER)) {
                continue;
            }
            
            tile2i current_tile(grid_offset);
            
            // Check if within RADIUS of any water tile
            for (const auto& water_tile : water_tiles) {
                int dx = std::abs(current_tile.x() - water_tile.x());
                int dy = std::abs(current_tile.y() - water_tile.y());
                int distance = std::max(dx, dy); // Chebyshev distance (king move)
                
                if (distance <= RADIUS) {
                    map_grid_set(g_terrain_clay, grid_offset, CLAY_MAX);
                    break;
                }
            }
        }
    }
}

io_buffer* iob_clay = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_clay);
});

