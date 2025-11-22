#include "building_academy.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_academy);

void building_academy::spawn_figure() {
    check_labor_problem();

    common_spawn_roamer(FIGURE_ACADEMY_SCRIBER, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);

    common_spawn_labor_seeker(current_params().min_houses_coverage);
}

void building_academy::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_academy::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);

    return true;
}
