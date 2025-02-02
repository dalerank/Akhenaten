#include "building_warship_wharf.h"

#include "city/labor.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "city/city.h"
#include "building/count.h"
#include "construction/build_planner.h"

building_warship_wharf::static_params warship_wharf_m;

void building_warship_wharf::static_params::load(archive arch) {
}

void building_warship_wharf::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    planer.set_tiles_building(anim[animkeys().base].first_img() + planer.relative_orientation, building_size);
}

void building_warship_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(100);
    }
}

void building_warship_wharf::update_count() const {
    building_increase_type_count(BUILDING_WARSHIP_WHARF, num_workers() > 0);
}

bool building_warship_wharf::ship_moored() const {
    figure *f = base.get_figure(BUILDING_SLOT_BOAT);
    if (!f->is_valid()) {
        return false;
    }

    const bool moored = (f->action_state == FIGURE_ACTION_203_WARSHIP_MOORED);
    return moored;
}

void building_warship_wharf::update_month() {
    building_wharf::update_month();

    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_warship_ship();
        }
    }

    map_water_update_docking_points(base, get_orientation(), 2);
}
