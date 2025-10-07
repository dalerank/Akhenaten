#include "building_warship_wharf.h"

#include "grid/water.h"
#include "grid/figure.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "city/city.h"
#include "construction/build_planner.h"

building_warship_wharf::static_params warship_wharf_m;

void building_warship_wharf::static_params::planer_setup_preview_graphics(build_planner &planer) const {
    planer.set_tiles_building(base_img() + planer.relative_orientation, building_size);
}

int building_warship_wharf::static_params::planer_construction_update(build_planner &planer, tile2i start, tile2i end) const {
    planer.draw_as_constructing = map_shore_determine_orientation(end, building_size, true).match;
    return 1;
}

void building_warship_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(params().min_houses_coverage);
    }
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
