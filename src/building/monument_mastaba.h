#pragma once

#include "grid/point.h"
#include "core/vec2i.h"

struct painter;
class building;

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
void draw_small_mastaba_anim_flat(painter &ctx, int x, int y, building *b, int color_mask);
int building_small_mastabe_get_image(tile2i tile, tile2i start, vec2i size);