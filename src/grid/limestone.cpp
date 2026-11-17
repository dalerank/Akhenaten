#include "limestone.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <vector>
#include <algorithm>
#include <cmath>

grid_xx g_terrain_limestone(FS_UINT16);

int map_get_limestone(int grid_offset) {
    return map_grid_get(g_terrain_limestone, grid_offset);
}

void map_limestone_deplete(int grid_offset, int amount) {
    int current = map_grid_get(g_terrain_limestone, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(g_terrain_limestone, grid_offset, new_value);
    }
}

void map_limestone_init() {
    map_grid_mark_near(
      g_terrain_limestone, [](int grid_offset) { return map_terrain_is(grid_offset, TERRAIN_ROCK); }, 2, 65000);
}

io_buffer* iob_limestone = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_limestone);
}, [](size_t version) {
    // saves older than this grid carry no ore at all
    map_grid_clear(g_terrain_limestone);
});

