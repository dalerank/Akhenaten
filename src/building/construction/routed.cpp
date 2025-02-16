#include "routed.h"

#include "building/model.h"
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
            items += map_tiles_set_road(end);
            break;

        case ROUTED_BUILDING_WALL:
            items += map_tiles_set_wall(end);
            break;

        case ROUTED_BUILDING_AQUEDUCT:
            items += map_tiles_set_canal(end);
            break;

        case ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC:
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

int building_construction_place_canal(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, start)) {
        return 0;
    }
        
    auto result = place_routed_building(start, end, ROUTED_BUILDING_AQUEDUCT);
    if (result.ok && !measure_only) {
        map_tiles_update_all_canals(0);
        map_routing_update_land();
    }

    return result.items;
}

routed_building_result building_construction_place_canal_for_reservoir(bool measure_only, tile2i start, tile2i end) {
    e_routed_mode type = measure_only ? ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC : ROUTED_BUILDING_AQUEDUCT;
    return place_routed_building(start, end, type);
}
