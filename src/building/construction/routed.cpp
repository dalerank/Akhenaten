#include "routed.h"

#include "building/building_wall.h"
#include "building/building_road.h"
#include "core/calc.h"
#include "game/undo.h"
#include "graphics/window.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"

#include <algorithm>

static const int direction_indices[8][4] = {
    {0, 2, 6, 4},
    {0, 2, 6, 4},
    {2, 4, 0, 6},
    {2, 4, 0, 6},
    {4, 6, 2, 0},
    {4, 6, 2, 0},
    {6, 0, 4, 2},
    {6, 0, 4, 2}
};

routed_building_result place_routed_building(tile2i start, tile2i end, e_routed_mode type) {
    int items = 0;
    int grid_offset = end.grid_offset();
    int guard = 0;
    // reverse routing
    while (true) {
        if (++guard >= 400) {
            return { false, 0 };
        }

        int distance = map_routing_distance(grid_offset);
        if (distance <= 0) {
            return { false, 0 };
        }

        switch (type) {
        default:
        case ROUTED_BUILDING_ROAD:
            items += (building_road::set_road(end) ? 1 : 0);
            break;

        case ROUTED_BUILDING_WALL:
            items += (building_mud_wall::set_wall(end) ? 1 : 0);
            break;

        case ROUTED_BUILDING_CANALS:
            items += map_tiles_set_canal(end);
            break;

        case ROUTED_BUILDING_CANALS_WITHOUT_GRAPHIC:
            items += 1;
            break;
        }

        int direction = calc_general_direction(end, start);
        if (direction == DIR_8_NONE) {
            return { true, items }; // destination reached
        }

        int routed = 0;
        for (int i = 0; i < 4; i++) {
            int index = direction_indices[direction][i];
            int new_grid_offset = grid_offset + map_grid_direction_delta(index);
            int new_dist = map_routing_distance(new_grid_offset);
            if (new_dist > 0 && new_dist < distance) {
                grid_offset = new_grid_offset;
                end = tile2i(grid_offset);
                routed = 1;
                break;
            }
        }

        // update land graphics
        map_tiles_update_region_empty_land(false, end.shifted(-4, -4), end.shifted(4, 4));
        if (!routed) {
            return { false, 0 };
        }
    }

    return { true, items };
}