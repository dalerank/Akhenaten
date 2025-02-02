#include "building_transport_wharf.h"

#include "grid/water.h"
#include "city/city.h"
#include "building/count.h"
#include "construction/build_planner.h"

building_transport_wharf::static_params transport_wharf_m;

void building_transport_wharf::static_params::load(archive arch) {

}

void building_transport_wharf::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    planer.set_tiles_building(anim[animkeys().base].first_img() + planer.relative_orientation, building_size);
}

void building_transport_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(100);
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

void building_transport_wharf::update_count() const {
    building_increase_type_count(BUILDING_TRANSPORT_WHARF, num_workers() > 0);
}