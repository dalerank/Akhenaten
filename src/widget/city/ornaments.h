#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"
#include "building/building.h"

int get_farm_image(int grid_offset);
void draw_farm_crops(e_building_type type, int progress, int grid_offset, vec2i tile, color_t color_mask);

void draw_ornaments_and_animations(vec2i pixel, map_point point);