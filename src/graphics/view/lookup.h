#pragma once

#include "view.h"

void calculate_screentile_lookup_tables();
tile2i screen_to_tile(vec2i screen);
vec2i tile_to_screen(tile2i point);

void clear_mappoint_pixelcoord();
void record_mappoint_pixelcoord(tile2i point, vec2i pixel);
vec2i tile_to_pixel(tile2i point);

vec2i pixel_to_viewport(vec2i pixel);
vec2i pixel_to_camera_coord(vec2i pixel, bool relative);
vec2i pixel_to_screentile(vec2i pixel);
