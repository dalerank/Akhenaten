#include "building/building_physician.h"

#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "sound/sound_building.h"
#include "io/gamefiles/lang.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "figuretype/figure_physician.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_physician);

void building_physician::spawn_figure() {
    common_spawn_roamer(FIGURE_PHYSICIAN, current_params().min_houses_coverage, (e_figure_action)ACTION_60_PHYSICIAN_CREATED);
}

void building_physician::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_physician::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}