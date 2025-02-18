#include "building_irrigation_ditch.h"

#include "grid/routing/routing.h"
#include "building/construction/routed.h"
#include "grid/tiles.h"
#include "grid/routing/routing_terrain.h"
#include "game/undo.h"

building_irrigation_ditch::static_params irrigation_ditch_m;

int building_construction_place_canal(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        return 0;
    }

    auto result = place_routed_building(start, end, ROUTED_BUILDING_CANALS);
    if (result.ok && !measure_only) {
        map_tiles_update_all_canals(0);
        map_routing_update_land();
    }

    return result.items;
}

routed_building_result building_construction_place_canal_for_lift(bool measure_only, tile2i start, tile2i end) {
    e_routed_mode type = measure_only ? ROUTED_BUILDING_CANALS_WITHOUT_GRAPHIC : ROUTED_BUILDING_CANALS;
    return place_routed_building(start, end, type);
}


bool building_irrigation_ditch::static_params::planer_can_construction_start(build_planner &p, tile2i start) const {
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start);
}

int building_irrigation_ditch::static_params::planer_construction_update(build_planner &p, tile2i start, tile2i end) const {
    int items_placed = building_construction_place_canal(/*measure_only*/true, start, end);
    map_tiles_update_all_canals(0);

    return items_placed;
}

building_irrigation_ditch::building_irrigation_ditch(building &b) : building_impl(b) {
}

void building_irrigation_ditch::on_place_checks() {
    // nothing
}
