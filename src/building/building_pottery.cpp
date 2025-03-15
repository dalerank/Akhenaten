#include "building/building_pottery.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "city/labor.h"
#include "city/city_resource.h"
#include "city/warnings.h"
#include "city/city.h"
#include "empire/empire.h"

#include "widget/city/ornaments.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "dev/debug.h"
#include "building/count.h"

#include <iostream>

buildings::model_t<building_pottery> pottery_m;

declare_console_command(addpottery, game_cheat_add_resource<RESOURCE_POTTERY>);

bool building_pottery::can_play_animation() const {
    if (base.stored_amount() < 100) {
        return false;
    }

    return building_industry::can_play_animation();
}

void building_pottery::on_place_checks() {
    if (building_count_industry_active(RESOURCE_CLAY) > 0) {
        return;
    }

    if (g_city.resource.warehouses_stored(RESOURCE_POTTERY) > 0 || g_city.resource.warehouses_stored(RESOURCE_CLAY) > 0) {
        return;
    }

    building_construction_warning_show(WARNING_CLAY_NEEDED);
    if (g_city.can_produce_resource(RESOURCE_CLAY))
        building_construction_warning_show(WARNING_BUILD_CLAY_PIT);
    else if (!g_empire.can_import_resource(RESOURCE_CLAY, true))
        building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
    else if (city_resource_trade_status(RESOURCE_CLAY) != TRADE_STATUS_IMPORT)
        building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
}

bool building_pottery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = ceilf(base.stored_amount() / 100.f);
    if (amount > 0) {
        const auto &ranim = anim(animkeys().clay);
        vec2i pos = ranim.pos;
        for (int i = 0; i < amount; ++i) {
            ImageDraw::img_generic(ctx, ranim.first_img(), point + pos, color_mask);
            pos += {5, -5};
        }
    }

    return true;
}

void building_pottery::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
}

void building_pottery::update_count() const {
    building_increase_industry_count(RESOURCE_POTTERY, num_workers() > 0);
}
