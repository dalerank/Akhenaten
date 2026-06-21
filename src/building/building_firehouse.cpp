#include "building_firehouse.h"

#include "figuretype/figure_fireman.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_firehouse)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_firehouse);

void building_firehouse::spawn_figure() {
    common_spawn_roamer(FIGURE_FIREMAN, current_params().min_houses_coverage, (e_figure_action)ACTION_70_FIREMAN_CREATED);
}

bool building_firehouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_firehouse::update_month() {
    building_impl::update_month();

    auto &data = runtime_data();
    data.months_active += (data.buildings_served_this_month > 0) ? 1 : 0;
    data.total_buildings_served += data.buildings_served_this_month;
    data.buildings_served_this_year += data.buildings_served_this_month;
    data.buildings_served_this_month = 0;
}

void building_firehouse::update_year() {
    building_impl::update_year();
    runtime_data().buildings_served_this_year = 0;
}