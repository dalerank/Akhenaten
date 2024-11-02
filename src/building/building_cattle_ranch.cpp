#include "building/building_cattle_ranch.h"

#include "building/building_workshop.h"
#include "graphics/animation.h"
#include "city/labor.h"

#include "js/js_game.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_cattle_ranch> cattle_ranch_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_cattle_ranch);
void config_load_building_cattle_ranch() {
    cattle_ranch_m.load();
}

void building_cattle_ranch::on_create(int orientation) {
    base.first_material_id = RESOURCE_STRAW;
}

bool building_cattle_ranch::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (worker_percentage() > 50) {
        const animation_t &anim = cattle_ranch_m.anim["work"];
        building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);
    }

    return true;
}
