#include "building_sandstone_quarry.h"

#include "building/building_raw_material.h"
#include "building/count.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include "city/labor.h"

buildings::model_t<building_sandstone_quarry> sandstone_quarry_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_sandstone_quarry);
void config_load_building_sandstone_quarry() {
    sandstone_quarry_m.load();
}

void building_sandstone_quarry::window_info_background(object_info &c) {
    building_raw_material_draw_info(c, "sandstone_quarry", RESOURCE_SANDSTONE);
}

void building_sandstone_quarry::on_create(int orientration) {
    base.output_resource_first_id = RESOURCE_SANDSTONE;
}

bool building_sandstone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point + vec2i{54, 15}, &base, tile, sandstone_quarry_m.anim["work"], color_mask);
    return false;
}

void building_sandstone_quarry::update_count() const {
    building_increase_industry_count(RESOURCE_SANDSTONE, num_workers() > 0);
}
