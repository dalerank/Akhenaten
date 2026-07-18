#include "building_well.h"

#include "grid/water_supply.h"
#include "widget/city/ornaments.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_well);

bool building_well::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_well::update_animation() {
    const e_well_status status = map_water_supply_is_well_unnecessary(id(), current_params().unnecessary_range_check);
    base.play_animation = (status == WELL_NECESSARY);
    es(__func__);
}
