#ifndef OZYMANDIAS_LOOKUP_H
#define OZYMANDIAS_LOOKUP_H

#include "view.h"

#define TILE_WIDTH_PIXELS 60
#define TILE_HEIGHT_PIXELS 30
#define HALF_TILE_WIDTH_PIXELS 30
#define HALF_TILE_HEIGHT_PIXELS 15


map_point screentile_to_mappoint(screen_tile screen);
screen_tile mappoint_to_screentile(map_point point);

pixel_coordinate mappoint_to_pixel(map_point point);
void record_pixel_coord(map_point point, pixel_coordinate coord);

screen_tile pixel_to_screentile(pixel_coordinate pixel);

void calculate_lookup();

#endif //OZYMANDIAS_LOOKUP_H
