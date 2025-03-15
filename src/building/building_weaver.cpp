#include "building_weaver.h"

#include "building/count.h"
#include "building/building_workshop.h"
#include "graphics/graphics.h"
#include "city/city_resource.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "city/city.h"
#include "empire/empire.h"
#include "js/js_game.h"

buildings::model_t<building_weaver> bweaver_m;

void building_weaver::on_place_checks() {
    if (building_count_industry_active(RESOURCE_FLAX) <= 0) {
        return;
    }

    if (g_city.resource.warehouses_stored(RESOURCE_FLAX) > 0) {
        return;
    }

    building_construction_warning_show(WARNING_OLIVES_NEEDED);
    if (g_city.can_produce_resource(RESOURCE_STRAW)) {
        building_construction_warning_show(WARNING_BUILD_OLIVE_FARM);
        return;
    } 
    
    if (!g_empire.can_import_resource(RESOURCE_FLAX, true)) {
        building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
        return;
    } 
    
    if (city_resource_trade_status(RESOURCE_FLAX) != TRADE_STATUS_IMPORT) {
        building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
        return;
    }
}

bool building_weaver::can_play_animation() const {
    if (base.stored_amount() < 100) {
        return false;
    }

    return building_industry::can_play_animation();
}

bool building_weaver::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    int amount = std::min<int>(2, ceil((float)base.stored_amount() / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().flax);
        ImageDraw::img_generic(ctx, ranim.first_img() + amount, point + ranim.pos, color_mask);
    }

    return true;
}

void building_weaver::update_count() const {
    building_increase_industry_count(RESOURCE_LINEN, num_workers() > 0);
}
