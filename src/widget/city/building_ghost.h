#ifndef WIDGET_CITY_BUILDING_GHOST_H
#define WIDGET_CITY_BUILDING_GHOST_H

#include "graphics/color.h"
#include "grid/point.h"

void draw_building(int image_id, int x, int y, color_t color_mask = COLOR_MASK_GREEN);

bool city_building_ghost_mark_deleting(map_point tile);

#endif // WIDGET_CITY_BUILDING_GHOST_H
