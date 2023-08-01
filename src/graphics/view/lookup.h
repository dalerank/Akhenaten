#ifndef OZYMANDIAS_LOOKUP_H
#define OZYMANDIAS_LOOKUP_H

#include "view.h"

void calculate_screentile_lookup_tables();
map_point screentile_to_mappoint(screen_tile screen);
screen_tile mappoint_to_screentile(map_point point);

void record_mappoint_pixelcoord(map_point point, pixel_coordinate pixel);
pixel_coordinate mappoint_to_pixel(map_point point);

pixel_coordinate pixel_to_viewport_coord(pixel_coordinate pixel);
camera_coordinate pixel_to_camera_coord(pixel_coordinate pixel, bool relative);
screen_tile pixel_to_screentile(pixel_coordinate pixel);


#endif // OZYMANDIAS_LOOKUP_H
