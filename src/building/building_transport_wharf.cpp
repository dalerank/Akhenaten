#include "building_transport_wharf.h"

#include "grid/water.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_transport_wharf);

void building_transport_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
    }
}

void building_transport_wharf::update_month() {
    building_wharf::update_month();

    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_transport_ship();
        }
    }

    map_water_update_docking_points(base, get_orientation(), 2);
}