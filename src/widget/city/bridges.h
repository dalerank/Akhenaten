#ifndef WIDGET_CITY_BRIDGE_H
#define WIDGET_CITY_BRIDGE_H

#include "graphics/color.h"
#include "city/view/view.h"

void city_draw_bridge(pixel_coordinate pixel, map_point point);

void city_draw_bridge_tile(int x, int y, int bridge_sprite_id, color_t color_mask);

#endif // WIDGET_CITY_BRIDGE_H
