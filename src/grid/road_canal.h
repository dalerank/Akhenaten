#pragma once

#include "grid/point.h"

bool map_can_place_road_under_canal(tile2i grid_offset);

bool map_can_place_canal_on_road(tile2i grid_offset);

int map_get_canal_with_road_image(int grid_offset);
