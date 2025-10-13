#include "building_senet_house.h"

#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "io/gamefiles/lang.h"
#include "window/building/common.h"
#include "city/buildings.h"
#include "figuretype/figure_drunkard.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "empire/empire.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_senet_house);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_bullfight_school);

void building_senet_house::on_place_checks() {
    construction_warnings warnings;

    const bool has_senet_master = (g_city.buildings.count_active(BUILDING_BULLFIGHT_SCHOOL) > 0);
    const bool nobrewery = g_city.buildings.count_industry_active(RESOURCE_BEER) <= 0;
    const bool nostored_beer = g_city.resource.yards_stored(RESOURCE_BEER) <= 0;
    const bool can_produce_beer = g_city.can_produce_resource(RESOURCE_BEER);
    const bool can_import_beer = g_empire.can_import_resource(RESOURCE_BEER, true);
    const bool is_import_beer = (city_resource_trade_status(RESOURCE_BEER) == TRADE_STATUS_IMPORT);

    warnings.add_if(!has_senet_master, "#build_senet_master");
    warnings.add_if(!nostored_beer, "#need_beer");
    warnings.add_if(!nobrewery, "#need_brewery");
    warnings.add_if(!can_produce_beer, "#build_brewery");
    warnings.add_if(!can_import_beer, "#import_beer_overseer");
    warnings.add_if(!is_import_beer, "#import_beer_trade_route");
}

void building_senet_house::on_destroy() {
    city_buildings_remove_senet_house();
}

bool building_senet_house::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_BEER) {
        return false;
    }

    assert(id() > 0);
    base.stored_amount_first += amount;
    return true;
}

void building_senet_house::spawn_figure() {
    const bool can_spawn_master = common_spawn_figure_trigger(100, BUILDING_SLOT_SERVICE);
    if (can_spawn_master) {
        create_roaming_figure(FIGURE_SENET_PLAYER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
        return;
    }

    if (base.stored_amount_first <= 0) {
        return;
    }

    auto &d = runtime_data();
    const bool can_spawn_drunk = common_spawn_figure_trigger(100, BUILDING_SLOT_DRUNKARD);
    if (can_spawn_drunk) {
        const short spent = std::min<short>(base.stored_amount_first, 20);
        base.stored_amount_first -= spent;

        create_roaming_figure(FIGURE_DRUNKARD, (e_figure_action)ACTION_14_DRUNKARD_CREATED, BUILDING_SLOT_DRUNKARD);
        return;
    }
}

void building_senet_house::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_senet_house::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().beer);
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

bool building_bullfight_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    int amount = ceil((float)base.stored_amount() / 100.0) - 1;
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().straw);
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