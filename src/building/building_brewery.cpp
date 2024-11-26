#include "building/building_brewery.h"

#include "building/building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/city.h"
#include "city/labor.h"
#include "city/city_resource.h"
#include "city/warnings.h"
#include "building/count.h"
#include "empire/empire.h"

#include "js/js_game.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "dev/debug.h"

#include <iostream>

declare_console_command(addbeer, game_cheat_add_resource<RESOURCE_BEER>);

building_brewery::static_params brewery_m;

void building_brewery::static_params::load(archive arch) {

}

bool building_brewery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &ranim = anim(animkeys().work);
    building_draw_normal_anim(ctx, point, &base, tile, ranim, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().barley);
        ImageDraw::img_generic(ctx, ranim.first_img() + amount, point + ranim.pos, color_mask);
    }

    return true;
}

void building_brewery::update_count() const {
    building_increase_industry_count(RESOURCE_BEER, num_workers() > 0);
}

void building_brewery::on_place_checks() {
    if (building_count_industry_active(RESOURCE_BARLEY) > 0) {
        return;
    }

    if (city_resource_warehouse_stored(RESOURCE_BEER) > 0 || city_resource_warehouse_stored(RESOURCE_BARLEY) > 0) {
        return;
    }

    building_construction_warning_show(WARNING_VINES_NEEDED);
    if (g_city.can_produce_resource(RESOURCE_BARLEY)) {
        building_construction_warning_show(WARNING_BUILD_VINES_FARM);
    } else if (!g_empire.can_import_resource(RESOURCE_BARLEY, true)) {
        building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
    } else if (city_resource_trade_status(RESOURCE_BARLEY) != TRADE_STATUS_IMPORT) {
        building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
    }
}
