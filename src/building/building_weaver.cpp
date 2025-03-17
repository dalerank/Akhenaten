#include "building_weaver.h"

#include "building/count.h"
#include "building/building_workshop.h"
#include "graphics/graphics.h"
#include "city/city_resource.h"
#include "city/city_warnings.h"
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

    construction_warnings warnings("#building_needs_flax");
    const bool can_produce = g_city.can_produce_resource(RESOURCE_FLAX);
    warnings.add_if(can_produce, "#build_flax_farm");

    const bool can_import = g_empire.can_import_resource(RESOURCE_FLAX, true);
    warnings.add_if(!can_import, "#setup_trade_route_to_import");
    
    const bool trade_import = (city_resource_trade_status(RESOURCE_FLAX) != TRADE_STATUS_IMPORT);
    warnings.add_if(trade_import, "#overseer_of_commerce_to_import");
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
