#include "architect_reach.h"

#include "grid/road_access.h"

grid_xx g_architect_reach_distance(FS_UINT16);

namespace {

constexpr int MAX_REACH_QUEUE = GRID_SIZE_TOTAL;

struct reach_queue_t {
    int head = 0;
    int tail = 0;
    int items[MAX_REACH_QUEUE];
};

reach_queue_t g_reach_queue;

int route_offset(int i) {
    switch (i) {
    case 0:
        return -GRID_LENGTH;
    case 1:
        return 1;
    case 2:
        return GRID_LENGTH;
    case 3:
        return -1;
    default:
        return 0;
    }
}

void enqueue(int offset, int distance) {
    map_grid_set(g_architect_reach_distance, offset, distance);
    g_reach_queue.items[g_reach_queue.tail++] = offset;
    if (g_reach_queue.tail >= MAX_REACH_QUEUE) {
        g_reach_queue.tail = 0;
    }
}

} // namespace

void map_architect_reach_calculate(tile2i origin, e_permission perm, int max_tiles) {
    map_grid_clear(g_architect_reach_distance);

    if (!origin.valid() || max_tiles < 0) {
        return;
    }

    const int source = origin.grid_offset();
    if (!map_grid_is_valid_offset(source) || !map_grid_inside_map_area(source, 1)) {
        return;
    }

    g_reach_queue.head = g_reach_queue.tail = 0;
    enqueue(source, 1); // stored distance = actual + 1

    while (g_reach_queue.head != g_reach_queue.tail) {
        const int offset = g_reach_queue.items[g_reach_queue.head];
        if (++g_reach_queue.head >= MAX_REACH_QUEUE) {
            g_reach_queue.head = 0;
        }

        const int actual_dist = map_grid_get(g_architect_reach_distance, offset) - 1;
        if (actual_dist >= max_tiles) {
            continue;
        }

        int road_tiles[8] = {0};
        map_get_adjacent_road_tiles_for_roaming(offset, road_tiles, perm);

        // Cardinal directions only: N=0, E=2, S=4, W=6 (same as roaming)
        static const int roam_dirs[4] = {0, 2, 4, 6};
        static const int offset_dirs[4] = {0, 1, 2, 3};
        for (int i = 0; i < 4; i++) {
            if (!road_tiles[roam_dirs[i]]) {
                continue;
            }

            const int next = offset + route_offset(offset_dirs[i]);
            if (!map_grid_is_valid_offset(next) || !map_grid_inside_map_area(next, 1)) {
                continue;
            }
            if (map_grid_get(g_architect_reach_distance, next) != 0) {
                continue;
            }

            enqueue(next, actual_dist + 2); // (actual_dist + 1) + 1 stored form
        }
    }
}

int map_architect_reach_distance(tile2i tile) {
    if (!tile.valid()) {
        return -1;
    }
    const int stored = map_grid_get(g_architect_reach_distance, tile.grid_offset());
    return stored > 0 ? stored - 1 : -1;
}
