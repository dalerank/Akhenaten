#include "building_temple.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_bast);

void building_temple::spawn_figure() {
    if (is_main()) {
        common_spawn_roamer(FIGURE_PRIEST, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
    }
}
