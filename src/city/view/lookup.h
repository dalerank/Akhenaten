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

void cache_pixel_coord(int tile_x, int tile_y, pixel_coordinate coord);

int viewtile_to_pixel(int x_view, int y_view);
void mappoint_to_viewtile(int grid_offset, int *x_view, int *y_view);
int pixel_to_viewtile(int x, int y, view_tile *tile);
int viewtile_to_mappoint(const view_tile *tile);

#endif //OZYMANDIAS_LOOKUP_H
