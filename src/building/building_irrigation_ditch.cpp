#include "building_irrigation_ditch.h"

#include "grid/routing/routing.h"

building_irrigation_ditch::static_params irrigation_ditch_m;

bool building_irrigation_ditch::static_params::planer_can_construction_start(build_planner &p, tile2i start) const {
    return map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start);
}

building_irrigation_ditch::building_irrigation_ditch(building &b) : building_impl(b) {
}

void building_irrigation_ditch::on_place_checks() {
    // nothing
}
