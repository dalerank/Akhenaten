#include "building_workshop_papyrus.h"

#include "building_workshop.h"
#include "building/count.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "city/city_resource.h"
#include "city/warning.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "empire/empire.h"
#include "dev/debug.h"

#include <iostream>

buildings::model_t<building_papyrus_maker> papyrus_maker_m;

declare_console_command(addpapyrus, game_cheat_add_resource<RESOURCE_PAPYRUS>);

bool building_papyrus_maker::can_play_animation() const {
    if (base.stored_amount() < 100) {
        return false;
    }

    return building_industry::can_play_animation();
}

void building_papyrus_maker::update_count() const {
    building_increase_industry_count(RESOURCE_PAPYRUS, num_workers() > 0);
}

bool building_papyrus_maker::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().reeds);
        ImageDraw::img_generic(ctx, ranim.first_img() + amount, point + ranim.pos, color_mask);
    }
    return true;
}

void building_papyrus_maker::on_place_checks() {
    if (building_count_industry_active(RESOURCE_REEDS) > 0) {
        return;
    }

    if (g_city.resource.warehouses_stored(RESOURCE_REEDS) > 0) {
        return;
    }

    construction_warnings warnings(WARNING_NEED_REEDS);

    const bool can_produce_reeds = g_city.can_produce_resource(RESOURCE_REEDS);
    const bool can_import_reeds = g_empire.can_import_resource(RESOURCE_REEDS, true);
    const bool is_import_reeds = (city_resource_trade_status(RESOURCE_REEDS) == TRADE_STATUS_IMPORT);
    
    warnings.add_if(!can_produce_reeds, WARNING_BUILD_REEDS_GATHERER);
    warnings.add_if(!can_import_reeds, WARNING_OPEN_TRADE_TO_IMPORT_REED);
    warnings.add_if(!is_import_reeds, WARNING_TRADE_IMPORT_RESOURCE);
}
