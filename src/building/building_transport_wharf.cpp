#include "building_transport_wharf.h"

#include "grid/water.h"
#include "city/city.h"
#include "construction/build_planner.h"

building_transport_wharf::static_params transport_wharf_m;

void building_transport_wharf::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    planer.set_tiles_building(params.base_img() + planer.relative_orientation, params.building_size);
}

int building_transport_wharf::static_params::planer_construction_update(build_planner &planer, tile2i start, tile2i end) const {
    planer.draw_as_constructing = map_shore_determine_orientation(end, building_size, true).match;
    return 1;
}

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