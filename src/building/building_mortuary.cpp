#include "building_mortuary.h"

#include "building/building_house.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "city/city_resource_handle.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "empire/empire.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mortuary);

void building_mortuary::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_LINEN) > 0) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_LINEN) > 0) {
        return;
    }

    construction_warnings warnings("#building_needs_linen");

    const bool trade_import = (city_resource_linen.trade_status() != TRADE_STATUS_IMPORT);

    warnings.add_if(city_resource_linen.can_produce(), "#build_weaver_or_import_linen");
    warnings.add_if(!city_resource_linen.can_import(true), "#setup_trade_route_to_import");
    warnings.add_if(trade_import, "#overseer_of_commerce_to_import");
}

void building_mortuary::spawn_figure() {
    if (g_city.resource.is_mothballed(RESOURCE_LINEN)) {
        return;
    }
    
    if (num_workers() <= 0) {
        return;
    }

    const auto &params = current_params();
    if (base.stored_amount(RESOURCE_LINEN) < params.linen_required_for_spawn) {
        return;
    }

    if (common_spawn_figure_trigger(params.min_houses_coverage, BUILDING_SLOT_SERVICE)) {
        const short spent = std::min<short>(base.stored_amount(RESOURCE_LINEN), params.linen_required_for_spawn);
        consume_resource(RESOURCE_LINEN, spent);

        create_roaming_figure(FIGURE_EMBALMER, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}

bool building_mortuary::can_play_animation() const {
    if (g_city.resource.is_mothballed(RESOURCE_LINEN)) {
        return false;
    }

    const auto &params = current_params();
    if (base.stored_amount(RESOURCE_LINEN) < params.linen_required_for_animation) {
        return false;
    }

    return building_impl::can_play_animation();
}

void building_mortuary::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_mortuary::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = base.stored_amount(RESOURCE_LINEN) / 100;
    if (amount > 0) {
        const auto &ranim = anim(animkeys().linen);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = color_mask;

            pos += {5, -5};
        }
    }

    return true;
}

void building_mortuary::update_count() const {
    g_city.health.add_mortuary_workers(num_workers());
}

void building_mortuary::update_month() {
    building_impl::update_month();
    
    auto &data = runtime_data();
    
    // Update statistics
    if (data.residents_served_this_month > 0) {
        data.months_active++;
    }
    data.total_residents_served += data.residents_served_this_month;
    data.residents_served_this_year += data.residents_served_this_month;
    
    // Reset monthly counter
    data.residents_served_this_month = 0;
    
    // Monthly linen consumption if there are workers and road access
    if (num_workers() > 0 && has_road_access()) {
        const auto &params = current_params();
        if (params.monthly_linen_consumption > 0) {
            int pct_workers = worker_percentage();
            int consumption = calc_adjust_with_percentage<int>(params.monthly_linen_consumption, pct_workers);
            
            int available = base.stored_amount(RESOURCE_LINEN);
            int to_consume = std::min<int>(available, consumption);
            consume_resource(RESOURCE_LINEN, to_consume);
        }
    }
}

void building_mortuary::update_year() {
    building_impl::update_year();
    runtime_data().residents_served_this_year = 0;
}