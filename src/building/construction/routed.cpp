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

int place_routed_building(tile2i start, tile2i end, e_routed_mode type, int* items) {
    *items = 0;
    int grid_offset = end.grid_offset();
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
            *items += map_tiles_set_road(end);
            break;
        case ROUTED_BUILDING_WALL:
            *items += map_tiles_set_wall(end);
            break;
        case ROUTED_BUILDING_AQUEDUCT:
            *items += map_tiles_set_canal(end);
            break;
        case ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC:
            *items += 1;
            break;
        }
        int direction = calc_general_direction(end, start);
        if (direction == DIR_8_NONE)
            return 1; // destination reached

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
        if (!routed)
            return 0;
    }
}

int building_construction_place_wall(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);

    int start_offset = start.grid_offset();
    int end_offset = end.grid_offset();
    int forbidden_terrain_mask = TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_SHRUB
                                 | TERRAIN_ROAD | TERRAIN_GARDEN | TERRAIN_ELEVATION | TERRAIN_RUBBLE | TERRAIN_CANAL
                                 | TERRAIN_ACCESS_RAMP;
    if (map_terrain_is(start_offset, forbidden_terrain_mask))
        return 0;

    if (map_terrain_is(end_offset, forbidden_terrain_mask))
        return 0;

    int items_placed = 0;
    if (place_routed_building(start, end, ROUTED_BUILDING_WALL, &items_placed)) {
        if (!measure_only) {
            map_routing_update_land();
            map_routing_update_walls();
        }
    }
    return items_placed;
}

int building_construction_place_canal(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    int items_placed = 0;
    if (map_routing_calculate_distances_for_building(ROUTED_BUILDING_AQUEDUCT, start)
        && place_routed_building(start, end, ROUTED_BUILDING_AQUEDUCT, &items_placed)) {
        if (!measure_only) {
            map_tiles_update_all_canals(0);
            map_routing_update_land();
        }
    }
    return items_placed;
}
int building_construction_place_canal_for_reservoir(bool measure_only, tile2i start, tile2i end, int* items) {
    e_routed_mode type = measure_only ? ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC : ROUTED_BUILDING_AQUEDUCT;
    return place_routed_building(start, end, type, items);
}
