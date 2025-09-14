#include "building/building_weaponsmith.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"

#include "js/js_game.h"
#include "city/city_warnings.h"
#include "city/city.h"
#include "empire/empire.h"

#include "dev/debug.h"
#include "city/city_resource.h"
#include <iostream>

building_weaponsmith::static_params weaponsmith_m;

declare_console_command(addweapons, game_cheat_add_resource<RESOURCE_WEAPONS>);
declare_console_command(addcopper, game_cheat_add_resource<RESOURCE_COPPER>);

void building_weaponsmith::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_COPPER) > 0) {
        return;
    }
       
    if (g_city.resource.yards_stored(RESOURCE_COPPER) >= 100) {
        return;
    }
        
    construction_warnings warnings("#building_needs_copper_ore");

    const bool can_produce_copper = g_city.can_produce_resource(RESOURCE_COPPER);
    const bool can_import_copper = g_empire.can_import_resource(RESOURCE_COPPER, true);
    const bool is_import_copper = (city_resource_trade_status(RESOURCE_COPPER) == TRADE_STATUS_IMPORT);

    warnings.add_if(!can_produce_copper, "#build_copper_mine");
    warnings.add_if(!can_import_copper, "#setup_trade_route_to_import");
    warnings.add_if(!is_import_copper, "#overseer_of_commerce_to_import");
}

bool building_weaponsmith::can_play_animation() const {
    if (base.stored_amount() < 100) {
        return false;
    }

    return building_impl::can_play_animation();
}

bool building_weaponsmith::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().copper);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}