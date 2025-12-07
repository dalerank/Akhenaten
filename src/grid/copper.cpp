#include "copper.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <vector>
#include <algorithm>
#include <cmath>

grid_xx g_terrain_copper = {0, FS_UINT16};

int map_get_copper(int grid_offset) {
    return map_grid_get(g_terrain_copper, grid_offset);
}

void map_copper_deplete(int grid_offset, int amount) {
    int current = map_grid_get(g_terrain_copper, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(g_terrain_copper, grid_offset, new_value);
    }
}

void map_copper_init() {
    // Initialize copper grid: mark all ore tiles and tiles within 2 tiles of ore with value 65000
    constexpr int COPPER_MAX = 65000;
    constexpr int RADIUS = 2;
    
    int grid_offset = scenario_map_data()->start_offset;
    int map_width = scenario_map_data()->width;
    int map_height = scenario_map_data()->height;
    
    // First pass: identify all ore tiles and mark them
    std::vector<tile2i> ore_tiles;
    for (int y = 0; y < map_height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_ORE)) {
                ore_tiles.push_back(tile2i(grid_offset));
                map_grid_set(g_terrain_copper, grid_offset, COPPER_MAX);
            } else {
                map_grid_set(g_terrain_copper, grid_offset, 0);
            }
        }
    }
    
    // Second pass: mark all tiles within RADIUS distance from any ore
    grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < map_height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            tile2i current_tile(grid_offset);
            int current_value = map_grid_get(g_terrain_copper, grid_offset);
            
            // If already marked as ore, skip
            if (current_value == COPPER_MAX) {
                continue;
            }
            
            // Check if within RADIUS of any ore tile
            for (const auto& ore_tile : ore_tiles) {
                int dx = std::abs(current_tile.x() - ore_tile.x());
                int dy = std::abs(current_tile.y() - ore_tile.y());
                int distance = std::max(dx, dy); // Chebyshev distance (king move)
                
                if (distance <= RADIUS) {
                    map_grid_set(g_terrain_copper, grid_offset, COPPER_MAX);
                    break;
                }
            }
        }
    }
}

io_buffer* iob_copper = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_copper);
});

