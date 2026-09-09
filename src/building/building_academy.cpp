#include "building_academy.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_academy);

void building_academy::spawn_figure() {
    check_labor_problem();

    common_spawn_roamer(FIGURE_ACADEMY_SCRIBER, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);

    common_spawn_labor_seeker(current_params().min_houses_coverage);
}
