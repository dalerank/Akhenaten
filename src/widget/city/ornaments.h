#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"
#include "building/building_type.h"

class building;

int get_farm_image(int grid_offset);
void draw_farm_crops(painter &ctx, e_building_type type, int progress, int grid_offset, vec2i tile, color color_mask);

void draw_ornaments_and_animations(vec2i pixel, tile2i point, painter &ctx);
void building_draw_normal_anim(painter &ctx, vec2i pixel, building *b, tile2i tile, int sprite_id, int color_mask, int base_id = 0, int max_frames = 0);