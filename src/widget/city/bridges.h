#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"

void city_draw_bridge(vec2i pixel, tile2i point, painter &ctx);
void city_draw_bridge_tile(painter &ctx, int x, int y, int bridge_sprite_id, color color_mask);
