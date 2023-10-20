#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"

void city_draw_bridge(vec2i pixel, tile2i point, view_context &ctx);
void city_draw_bridge_tile(view_context &ctx, int x, int y, int bridge_sprite_id, color color_mask);
