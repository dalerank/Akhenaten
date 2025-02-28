#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "building/count.h"
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
#include "config/config.h"
#include "window/building/common.h"
#include "graphics/text.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "city/labor.h"
#include "widget/city/ornaments.h"
#include "grid/random.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "figure/figure.h"
#include "js/js_game.h"
#include "graphics/animation.h"
#include "construction/build_planner.h"

building_mine_copper::static_params copper_mine_m;
buildings::model_t<building_clay_pit> clay_pit_m;
buildings::model_t<building_mine_gold> gold_mine_m;
buildings::model_t<building_mine_gems> gems_mine_m;
buildings::model_t<building_reed_gatherer> gatherer_m;

void building_mine::on_create(int orientation) {
    base.output_resource_first_id = params().output_resource;
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

int building_mine_gold::get_produce_uptick_per_day() const {
    if (config_get(CONFIG_GP_CH_GOLDMINE_TWICE_PRODUCTION)) {
        return base.num_workers / 5.f;
    } else {
        return base.num_workers / 10.f;
    }
}

void building_mine_gold::update_count() const {
    building_increase_industry_count(RESOURCE_GOLD, num_workers() > 0);
}


bool building_mine_copper::static_params::planer_is_need_flag(e_building_flags flag) const {
    switch (flag) {
    case e_building_flag::Ore:
        return !config_get(CONFIG_GP_CH_COPPER_NEAR_MOUNTAINS) && needs.ore;
    }

    return building_industry::static_params::planer_is_need_flag(flag);
}

void building_mine_copper::update_count() const {
    building_increase_industry_count(RESOURCE_COPPER, num_workers() > 0);
}

void building_mine_gems::update_count() const {
    building_increase_industry_count(RESOURCE_GEMS, num_workers() > 0);
}

int building_clay_pit::get_fire_risk(int value) const {
    if (config_get(CONFIG_GP_CH_CLAY_PIT_FIRE_RISK_REDUCED)) {
        return value / 2;
    }

    return value;
}

bool building_clay_pit::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_clay_pit::update_count() const {
    building_increase_industry_count(RESOURCE_CLAY, num_workers() > 0);
}

void building_reed_gatherer::on_create(int orientation) {
    runtime_data().max_gatheres = 1;
}

bool building_reed_gatherer::can_spawn_gatherer(int max_gatherers_per_building, int carry_per_person) {
    bool resource_reachable = false;
    resource_reachable = map_routing_citizen_found_terrain(base.road_access, nullptr, TERRAIN_MARSHLAND);

    if (!resource_reachable) {
        return false;
    }

    int gatherers_this_yard = base.get_figures_number(FIGURE_REED_GATHERER);

    // can only spawn if there's space for more reed in the building
    int max_loads = 500 / carry_per_person;
    if (gatherers_this_yard < max_gatherers_per_building
        && gatherers_this_yard + (base.stored_amount() / carry_per_person) < (max_loads - gatherers_this_yard)) {
        return true;
    }

    return false;
}

bool building_reed_gatherer::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = gatherer_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_reed_gatherer::update_count() const {
    building_increase_industry_count(RESOURCE_REEDS, num_workers() > 0);
}

void building_reed_gatherer::spawn_figure() {
    check_labor_problem();
    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(100);
    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;

        if (can_spawn_gatherer(runtime_data().max_gatheres, 50)) {
            auto f = create_figure_generic(FIGURE_REED_GATHERER, ACTION_8_RECALCULATE, BUILDING_SLOT_SERVICE, DIR_4_BOTTOM_LEFT);
            random_generate_next();
            f->wait_ticks = random_short() % 30; // ok
            return;
        }
    }

    base.common_spawn_goods_output_cartpusher();
}
