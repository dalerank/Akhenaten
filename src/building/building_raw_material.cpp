#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/random.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "graphics/text.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "widget/city/ornaments.h"
#include "grid/random.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "figure/figure.h"
#include "graphics/animation.h"
#include "construction/build_planner.h"
#include "city/city_finance.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_copper);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_clay_pit);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_gold);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mine_gems);

void building_mine::on_create(int orientation) {
    building_industry::on_create(orientation);
}

void building_mine::update_graphic() {
    const xstring &animkey = can_play_animation() 
                                ? animkeys().work
                                : animkeys().none;

    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_mine::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

int building_mine_gold::produce_uptick_per_day() const {
    if (!!game_features::gameplay_change_goldmine_twice_production) {
        return base.num_workers / 5.f;
    } else {
        return base.num_workers / 10.f;
    }
}

bool building_mine_copper::preview::is_need_flag(build_planner &planer, e_building_flags flag) const {
    const auto &params = building_static_params::get(planer.build_type);
    switch (flag) {
    case e_building_flag::Ore:
        return !game_features::gameplay_copper_mine_can_build_near_mountains && params.needs.ore;
    }

    return building_planer_renderer::is_need_flag(planer, flag);
}

int building_clay_pit::get_fire_risk(int value) const {
    if (!!game_features::gameplay_change_fire_risk_clay_pit_reduced) {
        return value / 2;
    }

    return value;
}

void building_clay_pit::on_before_flooded() {
    building_industry::on_before_flooded();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_mine_copper::on_before_collapse() {
    building_mine::on_before_collapse();

    if (!!game_features::gameplay_change_random_mine_or_pit_collapses_take_money) {
        events::emit(event_finance_request{ efinance_request_disasters, 250 });
    }
}
