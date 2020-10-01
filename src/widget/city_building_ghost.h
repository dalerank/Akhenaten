#ifndef WIDGET_CITY_BUILDING_GHOST_H
#define WIDGET_CITY_BUILDING_GHOST_H

#include "map/point.h"
#include "graphics/color.h"

void draw_building(int image_id, int x, int y, color_t color_mask = COLOR_MASK_GREEN);

int city_building_ghost_mark_deleting(const map_tile *tile);
void city_building_ghost_draw(const map_tile *tile);

#endif // WIDGET_CITY_BUILDING_GHOST_H
