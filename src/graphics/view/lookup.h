#pragma once

#include "view.h"

void calculate_screentile_lookup_tables();
map_point screentile_to_mappoint(screen_tile screen);
screen_tile mappoint_to_screentile(map_point point);

void record_mappoint_pixelcoord(map_point point, vec2i pixel);
vec2i mappoint_to_pixel(map_point point);

vec2i pixel_to_viewport_coord(vec2i pixel);
camera_coordinate pixel_to_camera_coord(vec2i pixel, bool relative);
screen_tile pixel_to_screentile(vec2i pixel);
