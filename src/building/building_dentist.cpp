#include "building/building_dentist.h"

#include "building/building_health.h"
#include "io/gamefiles/lang.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dentist);

void building_dentist::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_dentist::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_dentist::spawn_figure() {
    common_spawn_roamer(FIGURE_DENTIST, current_params().min_houses_coverage, ACTION_125_ROAMER_ROAMING);
}