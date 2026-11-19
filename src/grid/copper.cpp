#include "copper.h"
#include "grid/copper_chunks.h"

#include "core/log.h"
#include "dev/debug.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <vector>
#include <algorithm>
#include <cmath>


int map_get_copper(int grid_offset) {
    return map_grid_get(copper_grid_chunk::grid, grid_offset);
}

void map_copper_deplete(int grid_offset, int amount) {
    int current = map_grid_get(copper_grid_chunk::grid, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(copper_grid_chunk::grid, grid_offset, new_value);
    }
}

declare_console_command_p(recalc_copper) {
    map_copper_init();
    logs::info("copper map recalculated");
}

void map_copper_init() {
    map_grid_mark_near(
      copper_grid_chunk::grid, [](int grid_offset) { return map_terrain_is(grid_offset, TERRAIN_ORE); }, 2, 65000);
}
