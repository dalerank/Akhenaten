#include "building/building_water_supply.h"

#include "figuretype/figure_water_carrier.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_water_supply);

void building_water_supply::spawn_figure() {
    if (!base.has_water_access) {
        base.show_on_problem_overlay = 2;
    }

    common_spawn_roamer(FIGURE_WATER_CARRIER, current_params().min_houses_coverage,
                        (e_figure_action)ACTION_72_WATER_CARRIER_ROAMING);
}
