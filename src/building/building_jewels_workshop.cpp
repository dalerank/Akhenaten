#include "building_jewels_workshop.h"

#include "building/count.h"
#include "building/building_workshop.h"
#include "empire/empire.h"
#include "city/city_resource.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "city/city.h"

buildings::model_t<building_jewels_workshop> jewels_workshop_m;

bool building_jewels_workshop::can_play_animation() const {
    if (base.stored_amount() < 100) {
        return false;
    }

    return building_industry::can_play_animation();
}

void building_jewels_workshop::on_place_checks() {
    if (building_count_industry_active(RESOURCE_GEMS) > 0) {
        return;
    }

    if (g_city.resource.warehouses_stored(RESOURCE_LUXURY_GOODS) > 0 || g_city.resource.warehouses_stored(RESOURCE_GEMS) > 0) {
        return;
    }

    building_construction_warning_show(WARNING_TIMBER_NEEDED);
    if (g_city.can_produce_resource(RESOURCE_GEMS))
        building_construction_warning_show(WARNING_BUILD_TIMBER_YARD);
    else if (!g_empire.can_import_resource(RESOURCE_GEMS, true))
        building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
    else if (city_resource_trade_status(RESOURCE_GEMS) != TRADE_STATUS_IMPORT)
        building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
}

bool building_jewels_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_GEMS_2) + amount, x + 65, y + 3,
    //            color_mask);
    return true;
}

void building_jewels_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_LUXURY_GOODS, num_workers() > 0);
}
