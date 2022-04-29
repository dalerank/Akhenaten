#ifndef OZYMANDIAS_LOOKUP_H
#define OZYMANDIAS_LOOKUP_H

#include "view.h"

#define TILE_WIDTH_PIXELS 60
#define TILE_HEIGHT_PIXELS 30
#define HALF_TILE_WIDTH_PIXELS 30
#define HALF_TILE_HEIGHT_PIXELS 15

void calculate_lookup();

pixel_coordinate city_view_grid_offset_to_pixel(int grid_offset);
pixel_coordinate city_view_grid_offset_to_pixel(int tile_x, int tile_y);

void cache_pixel_coord(map_point tile, pixel_coordinate coord);

int screentile_to_pixel(int screen_x, int screen_y);
screen_tile mappoint_to_viewtile(map_point point);
int pixel_to_screentile(int x, int y, screen_tile *screen);
int viewtile_to_mappoint(const screen_tile *tile);

#endif //OZYMANDIAS_LOOKUP_H
