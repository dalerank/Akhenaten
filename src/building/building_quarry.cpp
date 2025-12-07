#include "building_quarry.h"

#include "building/building_raw_material.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include "grid/sandstone.h"
#include "grid/stone.h"
#include "grid/grid.h"

#include <algorithm>
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sandstone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_stone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_limestone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_granite_quarry);

bool building_sandstone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

bool building_stone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

bool building_limestone_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

bool building_granite_quarry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

void building_sandstone_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_sandstone(t); },
        [](tile2i t, int amount) { map_sandstone_deplete(t, amount); }
    );
}

void building_stone_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_stone(t); },
        [](tile2i t, int amount) { map_stone_deplete(t, amount); }
    );
}