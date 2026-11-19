#include "limestone.h"
#include "grid/limestone_chunks.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <vector>
#include <algorithm>
#include <cmath>


int map_get_limestone(int grid_offset) {
    return map_grid_get(limestone_grid_chunk::grid, grid_offset);
}

void map_limestone_deplete(int grid_offset, int amount) {
    int current = map_grid_get(limestone_grid_chunk::grid, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(limestone_grid_chunk::grid, grid_offset, new_value);
    }
}

void map_limestone_init() {
    map_grid_mark_near(
      limestone_grid_chunk::grid, [](int grid_offset) { return map_terrain_is(grid_offset, TERRAIN_ROCK); }, 2, 65000);
}
