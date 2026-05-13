#include "building_scribal_school.h"

#include "js/js_game.h"
#include "core/calc.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "city/city_resource_handle.h"
#include "empire/empire.h"
#include "widget/city/ornaments.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_scribal_school);

void building_scribal_school::update_month() {
    if (stored_amount(RESOURCE_PAPYRUS) <= 0) {
        return;
    }

    short want_spent = calc_adjust_with_percentage<short>(base.num_workers, 50);
    short spent = std::min<short>(stored_amount(RESOURCE_PAPYRUS), want_spent);
    consume_resource(RESOURCE_PAPYRUS, spent);
}

void building_scribal_school::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_PAPYRUS) > 0) {
        return;
    }
        
    if (g_city.resource.yards_stored(RESOURCE_PAPYRUS) > 0) {
        return;
    }

    construction_warnings warnings("#needs_papyrus");

    const bool is_import_papyrus = (city_resource_papyrus.trade_status() == TRADE_STATUS_IMPORT);

    warnings.add_if(!city_resource_papyrus.can_produce(), "#build_papyrus_maker");
    warnings.add_if(!city_resource_papyrus.can_import(true), "#import_papyrus_overseer");
    warnings.add_if(!is_import_papyrus, "#import_papyrus_trade_route");
}

bool building_scribal_school::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_PAPYRUS, amount);
    return true;
}

void building_scribal_school::spawn_figure() {
    if (common_spawn_figure_trigger(current_params().min_houses_coverage, BUILDING_SLOT_SERVICE)) {
        create_roaming_figure(FIGURE_TEACHER, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
}

void building_scribal_school::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_scribal_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, mask);

    int amount = ceil((float)stored_amount(RESOURCE_PAPYRUS) / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().papyrus);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
            command.image_id = ranim.first_img();
            command.pixel = point + pos;
            command.mask = mask;

            pos += {5, -5};
        }
    }

    return true;
}
