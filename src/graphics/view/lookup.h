#pragma once

#include "view.h"

void calculate_screentile_lookup_tables();
tile2i screentile_to_mappoint(vec2i screen);
vec2i mappoint_to_screentile(tile2i point);

void record_mappoint_pixelcoord(tile2i point, vec2i pixel);
vec2i mappoint_to_pixel(tile2i point);

vec2i pixel_to_viewport_coord(vec2i pixel);
vec2i pixel_to_camera_coord(vec2i pixel, bool relative);
vec2i pixel_to_screentile(vec2i pixel);
