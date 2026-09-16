#include "building_scribal_school.h"

#include "js/js_game.h"
#include "grid/road_access.h"
#include "figure/figure.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_scribal_school);

bool building_scribal_school::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_PAPYRUS, amount);
    return true;
}

void building_scribal_school::spawn_figure() {
    if (common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_SERVICE)) {
        create_roaming_figure(FIGURE_TEACHER, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}
