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

int city_view_to_grid_offset(int x_view, int y_view);
void city_view_grid_offset_to_xy_view(int grid_offset, int *x_view, int *y_view);
int city_view_pixels_to_view_tile(int x, int y, view_tile *tile);
int city_view_tile_to_grid_offset(const view_tile *tile);

#endif //OZYMANDIAS_LOOKUP_H
