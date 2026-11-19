#include "elevation.h"
#include "grid/elevation_chunks.h"
#include "io/io_buffer.h"

#include "grid/grid.h"
#include <scenario/map.h>

int map_elevation_at(int grid_offset) {
    return map_grid_get(elevation_grid_chunk::grid, grid_offset);
}
void map_elevation_set(int grid_offset, int value) {
    map_grid_set(elevation_grid_chunk::grid, grid_offset, value);
}

void map_elevation_clear(void) {
    map_grid_clear(elevation_grid_chunk::grid);
}
static void fix_cliff_tiles(int grid_offset) {
    // reduce elevation when the surrounding tiles are at least 2 lower
    int max = map_grid_get(elevation_grid_chunk::grid, grid_offset) - 1;
    if (map_grid_get(elevation_grid_chunk::grid, grid_offset + GRID_OFFSET(-1, 0)) < max
        || map_grid_get(elevation_grid_chunk::grid, grid_offset + GRID_OFFSET(0, -1)) < max
        || map_grid_get(elevation_grid_chunk::grid, grid_offset + GRID_OFFSET(1, 0)) < max
        || map_grid_get(elevation_grid_chunk::grid, grid_offset + GRID_OFFSET(0, 1)) < max) {
        map_grid_set(elevation_grid_chunk::grid, grid_offset, max);
    }
}
void map_elevation_remove_cliffs(void) {
    // elevation is max 5, so we need 4 passes to fix the lot
    for (int level = 0; level < 4; level++) {
        int grid_offset = scenario_map_data()->start_offset;
        for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
            for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
                if (map_grid_get(elevation_grid_chunk::grid, grid_offset) > 0)
                    fix_cliff_tiles(grid_offset);
            }
        }
    }
}
