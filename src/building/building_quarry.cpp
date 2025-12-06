#include "building_quarry.h"

#include "building/building_raw_material.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include "grid/sandstone.h"
#include "grid/grid.h"

#include <algorithm>
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sandstone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_stone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_limestone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_granite_quarry);

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

void building_sandstone_quarry::update_production() {
    auto &d = runtime_data();
    int current_progress = d.progress;

    tile2i best_tile = tile2i::invalid;
    int best_sandstone = 0;

    grid_area search_area = map_grid_get_area(base.tile, base.size, 0);
    map_grid_area_foreach(search_area.tmin, search_area.tmax, [&] (tile2i t) {
        int sandstone = map_get_sandstone(t);
        if (sandstone > 0 && sandstone > best_sandstone) {
            best_tile = t;
            best_sandstone = sandstone;
        }
    });

    if (best_sandstone <= 0) {
        return;
    }
    
    building_industry::update_production();
    int delta_progess = d.progress - current_progress;
   
    map_sandstone_deplete(best_tile, delta_progess);
}