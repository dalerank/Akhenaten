#include "building/building_dentist.h"

#include "building/building_health.h"
#include "city/labor.h"
#include "io/gamefiles/lang.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_dentist> dentist_m;

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
    common_spawn_roamer(FIGURE_DENTIST, 50, FIGURE_ACTION_125_ROAMING);
}