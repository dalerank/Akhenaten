#include "building/building_pottery.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "city/labor.h"

#include "widget/city/ornaments.h"

#include "js/js_game.h"

namespace model {

struct pottery_t {
    static constexpr e_building_type type = BUILDING_POTTERY_WORKSHOP;
    e_labor_category labor_category;
    animations_t anim;
};

pottery_t pottery;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_pottery);
void config_load_building_pottery() {
    g_config_arch.r_section("building_pottery", [] (archive arch) {
        model::pottery.labor_category = arch.r_type<e_labor_category>("labor_category");
        model::pottery.anim.load(arch);
    });

    city_labor_set_category(model::pottery);
}

void building_pottery::on_create() {
    data.industry.first_material_id = RESOURCE_CLAY;
    base.output_resource_first_id = RESOURCE_POTTERY;
}

void building_pottery::window_info_background(object_info& c) {
    e_resource output_resource = RESOURCE_POTTERY;

    building_workshop_draw_info(c, 1, "pottery_workshop", 126, output_resource, RESOURCE_CLAY);
}

bool building_pottery::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        const animation_t &anim = model::pottery.anim["work"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}