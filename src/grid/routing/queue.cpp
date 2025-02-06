#include "queue.h"
#include "routing_grids.h"

#define GUARD 50000

// static const int ROUTE_OFFSETS[2][8] = {
//         {-162, 1, 162, -1, -161, 163, 161, -163},
//         {-228, 1, 228, -1, -227, 229, 227, -229}
// };
static int ROUTE_OFFSETS(int i) {
    switch (i) {
    // perpendiculars
    case 0:
        return -GRID_LENGTH;
    case 1:
        return 1;
    case 2:
        return GRID_LENGTH;
    case 3:
        return -1;
    // diagonals
    case 4:
        return -GRID_LENGTH + 1;
    case 5:
        return +GRID_LENGTH + 1;
    case 6:
        return +GRID_LENGTH - 1;
    case 7:
        return -GRID_LENGTH - 1;
    ///
    default:
        return 0;
    }
}

struct grid_rounting_t {
    int head;
    int tail;
    int items[MAX_QUEUE];
};

grid_rounting_t g_grid_rounting;

void clear_distances(void) {
    map_grid_clear(routing_distance);
}

int valid_offset(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(routing_distance, grid_offset) == 0
           && map_grid_inside_map_area(grid_offset, 1);
}

void enqueue(int offset, int distance) {
    map_grid_set(routing_distance, offset, distance);
    g_grid_rounting.items[g_grid_rounting.tail++] = offset;
    if (g_grid_rounting.tail >= MAX_QUEUE)
        g_grid_rounting.tail = 0;
}
void route_queue(int source, int dest, void (*callback)(int next_offset, int distance)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (offset == dest)
            break;
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS(i)))
                callback(offset + ROUTE_OFFSETS(i), distance);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
void route_queue_until(int source, bool (*callback)(int next_offset, int distance)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS(i))) {
                if (!callback(offset + ROUTE_OFFSETS(i), distance))
                    break;
            }
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
bool route_queue_until_found(int source, tile2i &dst, bool (*callback)(int, int)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            int next_offset = offset + ROUTE_OFFSETS(i);
            if (valid_offset(next_offset)) {
                if (callback(next_offset, distance)) {
                    dst = tile2i(next_offset);
                    return true;
                }
            }
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
    dst = tile2i(-1, -1);
    return false;
}
bool route_queue_until_terrain(int source, int terrain_type, tile2i* dst, bool (*callback)(int, int, int)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            int next_offset = offset + ROUTE_OFFSETS(i);
            if (valid_offset(next_offset)) {
                if (callback(next_offset, distance, terrain_type)) {
                    if (dst != nullptr ) {
                        *dst = tile2i( MAP_X(next_offset), MAP_Y(next_offset) );
                    }
                    return true;
                }
            }
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }

    if (dst != nullptr ) {
        *dst = tile2i(-1, -1);
    }

    return false;
}
void route_queue_max(int source, int dest, int max_tiles, void (*callback)(int, int)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (offset == dest)
            break;
        if (++tiles > max_tiles)
            break;
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS(i)))
                callback(offset + ROUTE_OFFSETS(i), distance);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}

void route_queue_boat(int source, void (*callback)(int, int)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    map_grid_clear(water_drag);
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (++tiles > GUARD)
            break;

        int drag = map_grid_get(routing_tiles_water, offset) == WATER_N2_MAP_EDGE ? 4 : 0;
        int v = map_grid_get(water_drag, offset);
        if (drag && v < drag) {
            queue.items[queue.tail++] = offset;
            if (queue.tail >= MAX_QUEUE)
                queue.tail = 0;
        } else {
            int distance = 1 + map_grid_get(routing_distance, offset);
            for (int i = 0; i < 4; i++) {
                if (valid_offset(offset + ROUTE_OFFSETS(i)))
                    callback(offset + ROUTE_OFFSETS(i), distance);
            }
        }
        map_grid_set(water_drag, offset, v + 1);
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
void route_queue_dir8(int source, void (*callback)(int, int)) {
    auto &queue = g_grid_rounting;
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        if (++tiles > GUARD)
            break;
        int offset = queue.items[queue.head];
        int distance = 1 + map_grid_get(routing_distance, offset);
        for (int i = 0; i < 8; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS(i)))
                callback(offset + ROUTE_OFFSETS(i), distance);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}

bool queue_has(int offset) {
    auto &queue = g_grid_rounting;
    for (int i = 0; i < MAX_QUEUE; i++)
        if (queue.items[i] == offset)
            return true;
    return false;
}
int queue_get(int i) {
    auto &queue = g_grid_rounting;
    if (i < 0 || i >= MAX_QUEUE)
        return -1;
    return queue.items[i];
}