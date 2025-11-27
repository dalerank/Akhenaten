#include "building_library.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_library)

void building_library::spawn_figure() {
    common_spawn_roamer(FIGURE_LIBRARIAN, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
    check_labor_problem();
}

void building_library::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().base;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_library::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);
    return true;
}
