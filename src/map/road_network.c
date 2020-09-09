#include "road_network.h"

#include "city/map.h"
#include "map/data.h"
#include "map/grid.h"
#include "map/routing_terrain.h"
#include "map/terrain.h"

#include <string.h>

#define MAX_QUEUE 1000

static const int ADJACENT_OFFSETS_C3[] = {-GRID_SIZE_C3, 1, GRID_SIZE_C3, -1};
static const int ADJACENT_OFFSETS_PH[] = {-GRID_SIZE_PH, 1, GRID_SIZE_PH, -1};

static grid_xx network = {0, {FS_UINT8, FS_UINT8}};

static struct {
    int items[MAX_QUEUE];
    int head;
    int tail;
} queue;

int adjacent_offsets(int i)
{
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            return ADJACENT_OFFSETS_C3[i];
        case ENGINE_ENV_PHARAOH:
            return ADJACENT_OFFSETS_PH[i];
    }
}

void map_road_network_clear(void)
{
    map_grid_clear(&network);
}
int map_road_network_get(int grid_offset)
{
    return map_grid_get(&network, grid_offset);
}

static int mark_road_network(int grid_offset, uint8_t network_id)
{
    memset(&queue, 0, sizeof(queue));
    int guard = 0;
    int next_offset;
    int size = 1;
    do {
        if (++guard >= grid_total_size[GAME_ENV]) {
            break;
        }
        map_grid_set(&network, grid_offset, network_id);
        next_offset = -1;
        for (int i = 0; i < 4; i++) {
            int new_offset = grid_offset + adjacent_offsets(i);
            if (map_routing_citizen_is_passable(new_offset) && !map_grid_get(&network, new_offset)) {
                if (map_routing_citizen_is_road(new_offset) || map_terrain_is(new_offset, TERRAIN_ACCESS_RAMP)) {
                    map_grid_set(&network, new_offset, network_id);
                    size++;
                    if (next_offset == -1) {
                        next_offset = new_offset;
                    } else {
                        queue.items[queue.tail++] = new_offset;
                        if (queue.tail >= MAX_QUEUE) {
                            queue.tail = 0;
                        }
                    }
                }
            }
        }
        if (next_offset == -1) {
            if (queue.head == queue.tail) {
                return size;
            }
            next_offset = queue.items[queue.head++];
            if (queue.head >= MAX_QUEUE) {
                queue.head = 0;
            }
        }
        grid_offset = next_offset;
    } while (next_offset > -1);
    return size;
}

void map_road_network_update(void)
{
    city_map_clear_largest_road_networks();
    map_grid_clear(&network);
    int network_id = 1;
    int grid_offset = map_data.start_offset;
    for (int y = 0; y < map_data.height; y++, grid_offset += map_data.border_size) {
        for (int x = 0; x < map_data.width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_ROAD) && !map_grid_get(&network, grid_offset)) {
                int size = mark_road_network(grid_offset, network_id);
                city_map_add_to_largest_road_networks(network_id, size);
                network_id++;
            }
        }
    }
}
