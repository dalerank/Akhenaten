#include "gems.h"

#include "core/log.h"
#include "dev/debug.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"
#include "grid/point.h"

#include <algorithm>
#include <vector>

grid_xx g_terrain_gems(FS_UINT16);

namespace {
constexpr int GEMS_MAX = 65000;
constexpr int GEMS_HALO = 1;

bool rock_cluster_unused(tile2i origin, int size, const std::vector<uint8_t> &used) {
    if (!map_terrain_all_tiles_in_area_are(origin, size, TERRAIN_ROCK)) {
        return false;
    }
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int offset = origin.shifted(dx, dy).grid_offset();
            if (offset < 0 || offset >= GRID_SIZE_TOTAL || used[offset]) {
                return false;
            }
        }
    }
    return true;
}

void seed_gems_box(tile2i origin, int size) {
    for (int dy = -GEMS_HALO; dy < size + GEMS_HALO; dy++) {
        for (int dx = -GEMS_HALO; dx < size + GEMS_HALO; dx++) {
            tile2i t = origin.shifted(dx, dy);
            if (!t.valid()) {
                continue;
            }
            int offset = t.grid_offset();
            if (offset >= 0 && offset < GRID_SIZE_TOTAL) {
                map_grid_set(g_terrain_gems, offset, GEMS_MAX);
            }
        }
    }
}
}

int map_get_gems(int grid_offset) {
    return map_grid_get(g_terrain_gems, grid_offset);
}

void map_gems_deplete(int grid_offset, int amount) {
    int current = map_grid_get(g_terrain_gems, grid_offset);
    if (current > 0) {
        int new_value = std::max(0, current - amount);
        map_grid_set(g_terrain_gems, grid_offset, new_value);
    }
}

declare_console_command_p(recalc_gems) {
    map_gems_init();
    logs::info("gems map recalculated");
}

void map_gems_init() {
    map_grid_clear(g_terrain_gems);

    std::vector<uint8_t> used(GRID_SIZE_TOTAL, 0);

    int grid_offset = scenario_map_data()->start_offset;
    int map_width = scenario_map_data()->width;
    int map_height = scenario_map_data()->height;

    for (int y = 0; y < map_height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            if (used[grid_offset] || !map_terrain_is(grid_offset, TERRAIN_ROCK)) {
                continue;
            }

            tile2i origin(x, y);
            int size = 1;
            if (rock_cluster_unused(origin, 3, used)) {
                size = 3;
            } else if (rock_cluster_unused(origin, 2, used)) {
                size = 2;
            }

            seed_gems_box(origin, size);

            for (int dy = 0; dy < size; dy++) {
                for (int dx = 0; dx < size; dx++) {
                    int offset = origin.shifted(dx, dy).grid_offset();
                    if (offset >= 0 && offset < GRID_SIZE_TOTAL) {
                        used[offset] = 1;
                    }
                }
            }
        }
    }
}

io_buffer *iob_gems = new io_buffer(
    [] (io_buffer *iob, size_t version) { iob->bind(BIND_SIGNATURE_GRID, &g_terrain_gems); },
    [] (size_t version) { map_grid_clear(g_terrain_gems); }
);
