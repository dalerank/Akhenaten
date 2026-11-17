#include "golden.h"

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

grid_xx g_terrain_golden(FS_UINT16);

int map_get_golden(int grid_offset) {
    return map_grid_get(g_terrain_golden, grid_offset);
}

void map_golden_deplete(int grid_offset, int amount) {
    int current = map_grid_get(g_terrain_golden, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(g_terrain_golden, grid_offset, new_value);
    }
}

declare_console_command_p(recalc_gold) {
    map_golden_init();
    logs::info("gold map recalculated");
}

void map_golden_init() {
    map_grid_mark_near(
      g_terrain_golden, [](int grid_offset) { return map_terrain_is(grid_offset, TERRAIN_ORE); }, 2, 65000);
}

io_buffer* iob_golden = new io_buffer(
    [](io_buffer* iob, size_t version) { iob->bind(BIND_SIGNATURE_GRID, &g_terrain_golden); }, 
    [](size_t version) { map_grid_clear(g_terrain_golden); }
);

