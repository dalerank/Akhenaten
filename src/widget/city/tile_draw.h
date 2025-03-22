#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"
#include "grid/point.h"

enum e_render_state {
    RENDER_TALL_TILE = 1,
};

struct local_render_context_t {
    uint32_t last_water_animation_time;
    int advance_water_animation;

    int image_id_water_first;
    int image_id_water_last;

    int image_id_deepwater_first;
    int image_id_deepwater_last;

    void init();
};

void map_render_clear();

void map_render_set(tile2i tile, int flag);
void map_render_set(int grid_offset, int flag);
bool map_render_is(int grid_offset, int render_mask);

void draw_isometrics_overlay_flat(vec2i pixel, tile2i point, painter &ctx);
void draw_isometrics_overlay_height(vec2i pixel, tile2i point, painter &ctx);
void draw_ornaments_overlay(vec2i pixel, tile2i point, painter &ctx);
