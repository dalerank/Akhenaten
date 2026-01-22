#include "road_network.h"

#include "city/city.h"
#include "core/profiler.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "scenario/map.h"

#include <string.h>

#define MAX_ROAD_QUEUE 1000

static const int ADJACENT_OFFSETS_PH[] = {-GRID_LENGTH, 1, GRID_LENGTH, -1};

static grid_xx network = {0, FS_UINT8};

struct grid_road_network_t {
    int items[MAX_ROAD_QUEUE];
    int head;
    int tail;
};

grid_road_network_t grid_road_network;

int adjacent_offsets(int i) {
    return ADJACENT_OFFSETS_PH[i];
}

void map_road_network_clear() {
    map_grid_clear(network);
}

int map_road_network_get(int grid_offset) {
    return map_grid_get(network, grid_offset);
}

static int mark_road_network(int grid_offset, uint8_t network_id) {
    memset(&grid_road_network, 0, sizeof(grid_road_network));
    int guard = 0;
    int next_offset;
    int size = 1;
    do {
        if (++guard >= GRID_SIZE_TOTAL)
            break;

        map_grid_set(network, grid_offset, network_id);
        next_offset = -1;
        for (int i = 0; i < 4; i++) {
            int new_offset = grid_offset + adjacent_offsets(i);
            if (map_routing_citizen_is_passable(new_offset) && !map_grid_get(network, new_offset)) {
                if (map_routing_citizen_is_road(new_offset) || map_terrain_is(new_offset, TERRAIN_ACCESS_RAMP)) {
                    map_grid_set(network, new_offset, network_id);
                    size++;
                    if (next_offset == -1)
                        next_offset = new_offset;
                    else {
                        grid_road_network.items[grid_road_network.tail++] = new_offset;
                        if (grid_road_network.tail >= MAX_ROAD_QUEUE)
                            grid_road_network.tail = 0;
                    }
                }
            }
        }
        if (next_offset == -1) {
            if (grid_road_network.head == grid_road_network.tail)
                return size;

            next_offset = grid_road_network.items[grid_road_network.head++];
            if (grid_road_network.head >= MAX_ROAD_QUEUE)
                grid_road_network.head = 0;
        }
        grid_offset = next_offset;
    } while (next_offset > -1);
    return size;
}

void city_map_t::update_road_network() {
    OZZY_PROFILER_FUNCTION();
    g_city.map.clear_largest_road_networks();
    map_grid_clear(network);
    int network_id = 1;
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_ROAD) && !map_grid_get(network, grid_offset)) {
                int size = mark_road_network(grid_offset, network_id);
                g_city.map.add_to_largest_road_networks(network_id, size);
                network_id++;
            }
        }
    }
}
