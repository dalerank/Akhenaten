#include "routed.h"

#include "core/calc.h"
#include "building/model.h"
#include "game/undo.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "graphics/window.h"
#include <algorithm>

static int place_routed_building(int x_start, int y_start, int x_end, int y_end, routed_int type, int *items) {
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
    *items = 0;
    int grid_offset = MAP_OFFSET(x_end, y_end);
    int guard = 0;
    // reverse routing
    while (true) {
        if (++guard >= 400)
            return 0;
        int distance = map_routing_distance(grid_offset);
        if (distance <= 0)
            return 0;
        switch (type) {
            default:
            case ROUTED_BUILDING_ROAD:
                *items += map_tiles_set_road(x_end, y_end);
                break;
            case ROUTED_BUILDING_WALL:
                *items += map_tiles_set_wall(x_end, y_end);
                break;
            case ROUTED_BUILDING_AQUEDUCT:
                *items += map_tiles_set_aqueduct(x_end, y_end);
                break;
            case ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC:
                *items += 1;
                break;
        }
        int direction = calc_general_direction(x_end, y_end, x_start, y_start);
        if (direction == DIR_8_NONE)
            return 1; // destination reached

        int routed = 0;
        for (int i = 0; i < 4; i++) {
            int index = direction_indices[direction][i];
            int new_grid_offset = grid_offset + map_grid_direction_delta(index);
            int new_dist = map_routing_distance(new_grid_offset);
            if (new_dist > 0 && new_dist < distance) {
                grid_offset = new_grid_offset;
                x_end = MAP_X(grid_offset);
                y_end = MAP_Y(grid_offset);
                routed = 1;
                break;
            }
        }

        // update land graphics
        map_tiles_update_region_empty_land(false, x_end - 4, y_end - 4, x_end + 4, y_end + 4);
        if (!routed)
            return 0;
    }
}

int building_construction_place_road(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    game_undo_restore_map(0);
    int items_placed = 0;
    if (map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, x_start, y_start) &&
        place_routed_building(x_start, y_start, x_end, y_end, ROUTED_BUILDING_ROAD, &items_placed)) {
        if (!measure_only) {
            map_routing_update_land();
            window_invalidate();
        }
    }
    return items_placed;
}
int building_construction_place_wall(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    game_undo_restore_map(0);

    int start_offset = MAP_OFFSET(x_start, y_start);
    int end_offset = MAP_OFFSET(x_end, y_end);
    int forbidden_terrain_mask =
            TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING |
            TERRAIN_SHRUB | TERRAIN_ROAD | TERRAIN_GARDEN | TERRAIN_ELEVATION |
            TERRAIN_RUBBLE | TERRAIN_AQUEDUCT | TERRAIN_ACCESS_RAMP;
    if (map_terrain_is(start_offset, forbidden_terrain_mask))
        return 0;

    if (map_terrain_is(end_offset, forbidden_terrain_mask))
        return 0;

    int items_placed = 0;
    if (place_routed_building(x_start, y_start, x_end, y_end, ROUTED_BUILDING_WALL, &items_placed)) {
        if (!measure_only) {
            map_routing_update_land();
            map_routing_update_walls();
            window_invalidate();
        }
    }
    return items_placed;
}
int building_construction_place_aqueduct(bool measure_only, int x_start, int y_start, int x_end, int y_end) {
    game_undo_restore_map(0);
    int items_placed = 0;
    if (map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, x_start, y_start) &&
        place_routed_building(x_start, y_start, x_end, y_end, ROUTED_BUILDING_AQUEDUCT, &items_placed)) {
        if (!measure_only) {
            map_tiles_update_all_aqueducts(0);
            map_routing_update_land();
            window_invalidate();
        }
    }
    return items_placed;
}
int building_construction_place_aqueduct_for_reservoir(bool measure_only, int x_start, int y_start, int x_end, int y_end,
                                                       int *items) {
    routed_int type = measure_only ? ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC : ROUTED_BUILDING_AQUEDUCT;
    return place_routed_building(x_start, y_start, x_end, y_end, type, items);
}
