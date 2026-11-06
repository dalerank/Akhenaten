#include "building_warship_wharf.h"

#include "city/city.h"
#include "figure/figure.h"
#include "grid/water.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_warship_wharf);

void building_warship_wharf::clear_invalid_boat() {
    // OG spawn_wharf: drop ship_id when the figure is dead or not a warship.
    const int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
    if (!boat_id) {
        return;
    }

    figure *boat = figure_get(boat_id);
    if (!boat->is_valid() || boat->type != FIGURE_WARSHIP) {
        base.set_figure(BUILDING_SLOT_BOAT, 0);
    }
}

void building_warship_wharf::spawn_figure() {
    // OG: mark_problem + clear stale boat + labor seeker when houses_covered < 51.
    check_labor_problem();
    clear_invalid_boat();

    if (has_road_access()) {
        common_spawn_labor_seeker(current_params().min_houses_coverage);
    }
}

void building_warship_wharf::update_day() {
    building_wharf::update_day();
    clear_invalid_boat();
}

void building_warship_wharf::update_month() {
    building_wharf::update_month();

    // Remake shipwright polls request counters; OG shipwright_boat_needed counts
    // staffed warship wharves without a live boat.
    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        if (!boat->is_valid()) {
            g_city.buildings.request_warship_ship();
        }
    }

    map_water_update_docking_points(base, get_orientation(), 2);
}

void building_warship_wharf::on_undo() {
    base.set_figure(BUILDING_SLOT_BOAT, 0);
}
