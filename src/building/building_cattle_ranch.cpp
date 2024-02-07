#include "building/building_cattle_ranch.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "city/labor.h"

#include "js/js_game.h"
#include "widget/city/ornaments.h"

namespace model {

struct cattle_ranch_t {
    static constexpr e_building_type type = BUILDING_CATTLE_RANCH;
    e_labor_category labor_category;
    animations_t anim;
};

cattle_ranch_t cattle_ranch;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_cattle_ranch);
void config_load_building_cattle_ranch() {
    g_config_arch.r_section("building_cattle_ranch", [] (archive arch) {
        model::cattle_ranch.labor_category = arch.r_type<e_labor_category>("labor_category");
        model::cattle_ranch.anim.load(arch);
    });

    city_labor_set_category(model::cattle_ranch);
}


void building_cattle_ranch::on_create() {
    data.industry.first_material_id = RESOURCE_STRAW;
    base.output_resource_first_id = RESOURCE_MEAT;
}

void building_cattle_ranch::window_info_background(object_info &c) {
    e_resource output_resource = RESOURCE_MEAT;
    building_workshop_draw_info(c, 1, "cattle_ranch", 117, output_resource, RESOURCE_STRAW);
}

bool building_cattle_ranch::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        const animation_t &anim = model::cattle_ranch.anim["work"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}
