#include "building_workshop_papyrus.h"

#include "building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"

#include "js/js_game.h"

buildings::model_t<building_papyrus_maker> papyrus_maker_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_papyrus_maker);
void config_load_building_papyrus_maker() {
    papyrus_maker_m.load();
}

void building_papyrus_maker::on_create() {
    data.industry.first_material_id = RESOURCE_REEDS;
    base.output_resource_first_id = RESOURCE_PAPYRUS;
}

void building_papyrus_maker::window_info_background(object_info &c) {
    e_resource output_resource = RESOURCE_PAPYRUS;
    building_workshop_draw_info(c, 1, "papyrus_workshop", 190, output_resource, RESOURCE_REEDS);
}

bool building_papyrus_maker::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point, &base, tile, papyrus_maker_m.anim["work"], color_mask);
    return true;
}
