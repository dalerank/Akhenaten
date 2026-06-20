#include "building/building_water_supply.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_water_supply);

void building_water_supply::spawn_figure() {
    if (!base.has_water_access) {
        base.show_on_problem_overlay = 2;
    }

    common_spawn_roamer(FIGURE_WATER_CARRIER, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
}

bool building_water_supply::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}
