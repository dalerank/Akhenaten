#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"

void city_draw_bridge(vec2i pixel, map_point point);
void city_draw_bridge_tile(int x, int y, int bridge_sprite_id, color_t color_mask);
