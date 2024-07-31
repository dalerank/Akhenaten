#include "building/building_dentist.h"

#include "building/building_health.h"
#include "city/labor.h"
#include "io/gamefiles/lang.h"
#include "widget/city/ornaments.h"
#include "building/count.h"
#include "js/js_game.h"

buildings::model_t<building_dentist> dentist_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_dentist);
void config_load_building_dentist() {
    dentist_m.load();
}

void building_dentist::window_info_background(object_info &c) {
    building_health_draw_info(c, FIGURE_DENTIST);
}

bool building_dentist::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = dentist_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_dentist::spawn_figure() {
    common_spawn_roamer(FIGURE_DENTIST, 50, FIGURE_ACTION_125_ROAMING);
}