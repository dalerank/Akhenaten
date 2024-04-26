#include "building/building_brewery.h"

#include "building/building_workshop.h"
#include "widget/city/ornaments.h"
#include "city/labor.h"
#include "city/resource.h"
#include "city/warning.h"

#include "js/js_game.h"
#include "graphics/window.h"
#include "dev/debug.h"

#include <iostream>

declare_console_command(addbeer, game_cheat_add_resource<RESOURCE_BEER>);

buildings::model_t<building_brewery> brewery_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_brewery);
void config_load_building_brewery() {
    brewery_m.load();
}

void building_brewery::on_create(int orientation) {
    data.industry.first_material_id = RESOURCE_BARLEY;
    base.output_resource_first_id = RESOURCE_BEER;
}

void building_brewery::window_info_background(object_info& c) {
    e_resource input_resource = RESOURCE_BARLEY;
    e_resource output_resource = RESOURCE_BEER;

    building_workshop_draw_background(c, 96, "brewery", 122, output_resource, input_resource);
}

void building_brewery::window_info_foreground(object_info &c) {
    building_workshop_draw_foreground(c);
}

bool building_brewery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = brewery_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}