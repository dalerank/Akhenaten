#include "building_workshop_papyrus.h"

#include "building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "city/city_resource_handle.h"
#include "city/city_warnings.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "empire/empire.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_papyrus_maker);

declare_console_command(addpapyrus, game_cheat_add_resource<RESOURCE_PAPYRUS>);

bool building_papyrus_maker::can_play_animation() const {
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_REEDS) < 100 && d.progress == 0) {
        return false;
    }

    return building_industry::can_play_animation();
}

bool building_papyrus_maker::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_REEDS) / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().reeds);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }
    return true;
}

void building_papyrus_maker::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_REEDS) > 0) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_REEDS) > 0) {
        return;
    }

    construction_warnings warnings("#building_needs_reeds");

    const bool is_import_reeds = (city_resource_reeds.trade_status() == TRADE_STATUS_IMPORT);
    
    warnings.add_if(!city_resource_reeds.can_produce(), "#build_reed_gatherer");
    warnings.add_if(!city_resource_reeds.can_import(true), "#setup_trade_route_to_import");
    warnings.add_if(!is_import_reeds, "#overseer_of_commerce_to_import");
}
