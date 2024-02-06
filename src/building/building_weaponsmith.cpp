#include "building/building_weaponsmith.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"

#include "js/js_game.h"
#include "city/labor.h"

namespace model {

struct courthouse_t {
    static constexpr e_building_type type = BUILDING_WEAPONSMITH;
    e_labor_category labor_category;
    animations_t anim;
};

courthouse_t weaponsmith;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_weaponsmith);
void config_load_building_weaponsmith() {
    g_config_arch.r_section("building_weaponsmith", [] (archive arch) {
        model::weaponsmith.labor_category = arch.r_type<e_labor_category>("labor_category");
        model::weaponsmith.anim.load(arch);
    });

    city_labor_set_category(model::weaponsmith);
}

void building_weaponsmith::on_create() {
    data.industry.first_material_id = RESOURCE_COPPER;
    base.output_resource_first_id = RESOURCE_WEAPONS;
}

void building_weaponsmith::window_info_background(object_info& c) {
    e_resource output_resource = RESOURCE_WEAPONS;
    building_workshop_draw_info(c, 98, "weapons_workshop", 124, output_resource, RESOURCE_COPPER);
}

bool building_weaponsmith::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const animation_t &anim = model::weaponsmith.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}