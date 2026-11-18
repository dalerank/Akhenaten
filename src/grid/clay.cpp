#include "clay.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"
#include "grid/tiles.h"

#include <vector>
#include <algorithm>
#include <cmath>

grid_xx g_terrain_clay(FS_UINT16);

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

static bool clay_water(int grid_offset) {
    return map_terrain_is(grid_offset, TERRAIN_WATER) || map_terrain_is(grid_offset, TERRAIN_DEEPWATER)
           || map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN | TERRAIN_WATER);
}

void map_clay_init() {
    constexpr int CLAY_MAX = 65000;
    constexpr int RADIUS = 3;

    map_grid_clear(g_terrain_clay);

    const int map_width = scenario_map_data()->width;
    const std::vector<uint8_t> distance = map_grid_king_distance(clay_water, RADIUS);
    map_tiles_foreach_map_tile([&](int grid_offset) {
        const tile2i tile(grid_offset);
        const bool near_water = !clay_water(grid_offset) && distance[(size_t)tile.y() * map_width + tile.x()] <= RADIUS;
        map_grid_set(g_terrain_clay, grid_offset, near_water ? CLAY_MAX : 0);
    });
}

io_buffer* iob_clay = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_terrain_clay);
}, [](size_t version) {
    // saves older than this grid carry no ore at all
    map_grid_clear(g_terrain_clay);
});

