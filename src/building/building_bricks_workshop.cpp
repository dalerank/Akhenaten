#include "building_bricks_workshop.h"

#include "js/js_game.h"
#include "building/building_workshop.h"
#include "building/count.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/labor.h"

buildings::model_t<building_bricks_workshop> bricks_workshop_m;

void building_bricks_workshop::window_info_background(object_info &c) {
    building_workshop_draw_background(c, RESOURCE_CLAY);
}

void building_bricks_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_BRICKS, num_workers() > 0);
}

bool building_bricks_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    int amount = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_CLAY) / 100.0) - 1);
    int amount2 = std::min<int>(2, ceil((float)base.stored_amount(RESOURCE_STRAW) / 100.0) - 1);
    if (amount >= 0) {
        const auto &ranim = anim(animkeys().clay);
        ImageDraw::img_generic(ctx, ranim.first_img() + amount, point + ranim.pos, color_mask);
    }

    if (amount2 >= 0) {
        const auto &ranim = anim(animkeys().straw);
        ImageDraw::img_generic(ctx, ranim.first_img() + amount, point + ranim.pos, color_mask);
    }

    return true;
}