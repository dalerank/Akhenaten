#include "building/building_physician.h"

#include "widget/city/ornaments.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_physician)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_physician);

void building_physician::update_month() {
    building_impl::update_month();
    runtime_data().residents_served_this_month = 0;
}

bool building_physician::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile,
  color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}