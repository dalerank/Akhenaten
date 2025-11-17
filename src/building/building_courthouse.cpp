#include "building/building_courthouse.h"

#include "widget/city/ornaments.h"
#include "figuretype/figure_magistrate.h"
#include "js/js_game.h"
#include "graphics/animation.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_courthouse);

void building_courthouse::spawn_figure() {
    common_spawn_roamer(FIGURE_MAGISTRATE, current_params().min_houses_coverage, (e_figure_action)ACTION_125_MAGISTRATE_ROAMING);
}

void building_courthouse::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
    building_impl::update_graphic();
}

bool building_courthouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}
