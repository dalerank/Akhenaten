#include "building_quarry.h"

#include "building/building_raw_material.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_sandstone_quarry> sandstone_quarry_m;
buildings::model_t<building_stone_quarry> stone_quarry_m;
buildings::model_t<building_limestone_quarry> limestone_quarry_m;
buildings::model_t<building_granite_quarry> granite_quarry_m;

bool building_sandstone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point + vec2i{54, 15}, &base, tile, anim("work"), color_mask);
    return true;
}

bool building_stone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point + vec2i{54, 15}, &base, tile, anim("work"), color_mask);
    return true;
}

bool building_limestone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point + vec2i{54, 15}, &base, tile, anim("work"), color_mask);
    return true;
}

bool building_granite_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &ranim = anim("work");
    building_draw_normal_anim(ctx, point + vec2i{54, 15}, &base, tile, ranim, color_mask);
    return true;
}