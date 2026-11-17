#include "copper.h"

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

grid_xx g_terrain_copper(FS_UINT16);

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

declare_console_command_p(recalc_copper) {
    map_copper_init();
    logs::info("copper map recalculated");
}

void map_copper_init() {
    map_grid_mark_near(
      g_terrain_copper, [](int grid_offset) { return map_terrain_is(grid_offset, TERRAIN_ORE); }, 2, 65000);
}

io_buffer* iob_copper = new io_buffer(
    [](io_buffer* iob, size_t version) { iob->bind(BIND_SIGNATURE_GRID, &g_terrain_copper); }, 
    [](size_t version) { map_grid_clear(g_terrain_copper); }
);

