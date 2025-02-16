#include "building_wall.h"

#include "game/undo.h"
#include "grid/terrain.h"
#include "construction/routed.h"
#include "grid/routing/routing_terrain.h"

building_mud_wall::static_params building_mud_wall_m;

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

    auto result = place_routed_building(start, end, ROUTED_BUILDING_WALL);
    if (result.ok && !measure_only) {
        map_routing_update_land();
        map_routing_update_walls();
    }

    return result.ok;
}

int building_mud_wall::static_params::planer_construction_update(build_planner &p, tile2i start, tile2i end) const {
    int items_placed = building_construction_place_wall(true, start, end);
    return items_placed;
}

int building_mud_wall::static_params::planer_construction_place(build_planner &planer, tile2i start, tile2i end, int orientation, int variant) const {
    int items_placed = building_construction_place_wall(false, start, end);
    return items_placed;
}

bool building_mud_wall::static_params::planer_can_construction_start(build_planner &p, tile2i start) const {
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_WALL, start);
}

building_mud_wall::building_mud_wall(building &b) : building_impl(b) {
    // nothing
}

void building_mud_wall::on_place_checks() {
    // nothing
}
