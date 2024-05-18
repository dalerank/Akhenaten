#include "building_weaver.h"

#include "building/count.h"
#include "building/building_workshop.h"
#include "city/resource.h"
#include "city/warnings.h"
#include "city/labor.h"
#include "empire/empire_city.h"
#include "js/js_game.h"

buildings::model_t<building_weaver> bweaver_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_weaver);
void config_load_building_weaver() {
    bweaver_m.load();
}

void building_weaver::on_create(int orientation) {
    data.industry.first_material_id = RESOURCE_FLAX;
    base.output_resource_first_id = RESOURCE_LINEN;
}

void building_weaver::on_place_checks() {
    if (building_count_industry_active(RESOURCE_FLAX) <= 0) {
        return;
    }

    if (city_resource_count(RESOURCE_FLAX) > 0) {
        return;
    }

    building_construction_warning_show(WARNING_OLIVES_NEEDED);
    if (empire_can_produce_resource(RESOURCE_STRAW, true))
        building_construction_warning_show(WARNING_BUILD_OLIVE_FARM);
    else if (!empire_can_import_resource(RESOURCE_STRAW, true))
        building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
    else if (city_resource_trade_status(RESOURCE_STRAW) != TRADE_STATUS_IMPORT)
        building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
}

void building_weaver::window_info_background(object_info &ctx) {
    e_resource input_resource = RESOURCE_FLAX;
    e_resource output_resource = RESOURCE_LINEN;
    building_workshop_draw_background(ctx, 97, "flax_workshop", 123, output_resource, input_resource);
}

bool building_weaver::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_FLAX_2) + amount, x + 65, y + 3,
    //            color_mask);
    return true;
}

void building_weaver::update_count() const {
    building_increase_industry_count(RESOURCE_LINEN, num_workers() > 0);
}
