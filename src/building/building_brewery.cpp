#include "building/building_brewery.h"

#include "building/building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
#include "empire/empire.h"

#include "js/js_game.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "dev/debug.h"

#include <iostream>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_brewery);

declare_console_command(addbeer, game_cheat_add_resource<RESOURCE_BEER>);
declare_console_command(addbarley, game_cheat_add_resource<RESOURCE_BARLEY>);

bool building_brewery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &ranim = anim(animkeys().work);
    building_draw_normal_anim(ctx, point, &base, tile, ranim, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().barley);

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
        command.image_id = ranim.first_img() + amount;
        command.pixel = point + ranim.pos;
        command.mask = color_mask;
    }

    return true;
}

void building_brewery::on_place_checks() {
    if (g_city.buildings.count_industry_active(RESOURCE_BARLEY) > 0) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_BARLEY) > 0) {
        return;
    }

    construction_warnings warnings("#needs_barley");

    const bool can_produce_barley = g_city.can_produce_resource(RESOURCE_BARLEY);
    const bool can_import_barley = g_empire.can_import_resource(RESOURCE_BARLEY, true);
    const bool is_import_barley = (city_resource_trade_status(RESOURCE_BARLEY) == TRADE_STATUS_IMPORT);
    
    warnings.add_if(!can_produce_barley, "#needs_barley");
    warnings.add_if(!can_import_barley, "#setup_trade_route_to_import");
    warnings.add_if(!is_import_barley, "#overseer_of_commerce_to_import");
}
