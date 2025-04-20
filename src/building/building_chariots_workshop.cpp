#include "building_chariots_workshop.h"

buildings::model_t<building_chariots_workshop> chariots_workshop_m;

bool building_chariots_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}
