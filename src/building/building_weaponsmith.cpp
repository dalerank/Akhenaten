#include "building/building_weaponsmith.h"

#include "building/building_workshop.h"
#include "building/count.h"
#include "graphics/animation.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "city/city.h"
#include "empire/empire.h"

#include "dev/debug.h"
#include "city/city_resource.h"
#include <iostream>

declare_console_command(addweapons, game_cheat_add_resource<RESOURCE_WEAPONS>);

buildings::model_t<building_weaponsmith> weaponsmith_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_weaponsmith);
void config_load_building_weaponsmith() {
    weaponsmith_m.load();
}

void building_weaponsmith::on_create(int orientation) {
    data.industry.first_material_id = RESOURCE_COPPER;
}

void building_weaponsmith::on_place_checks() {
    if (building_count_industry_active(RESOURCE_COPPER) > 0) {
        return;
    }

    if (city_resource_count(RESOURCE_WEAPONS) <= 0 && city_resource_count(RESOURCE_COPPER) <= 0) {
        building_construction_warning_show(WARNING_IRON_NEEDED);

        if (g_city.can_produce_resource(RESOURCE_COPPER))
            building_construction_warning_show(WARNING_BUILD_IRON_MINE);
        else if (!g_empire.can_import_resource(RESOURCE_COPPER, true))
            building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
        else if (city_resource_trade_status(RESOURCE_COPPER) != TRADE_STATUS_IMPORT)
            building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
    }
}

void building_weaponsmith::update_graphic() {
    const xstring &animkey = (can_play_animation() && base.stored_amount() >= 100) 
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);

    building_impl::update_graphic();
}

bool building_weaponsmith::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &anim = weaponsmith_m.anim["copper"];
        ImageDraw::img_generic(ctx, anim.first_img() + amount, point + anim.pos, color_mask);
    }

    return true;
}

void building_weaponsmith::update_count() const {
    building_increase_industry_count(RESOURCE_WEAPONS, num_workers() > 0);
}
