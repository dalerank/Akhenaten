#include "building_mine.h"

#include "building/building.h"
#include "graphics/animation.h"
#include "widget/city/ornaments.h"

void building_mine::on_create(int orientation) {
    building_industry::on_create(orientation);
}

void building_mine::update_graphic() {
    update_graphic_work_anim();
}

bool building_mine::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

