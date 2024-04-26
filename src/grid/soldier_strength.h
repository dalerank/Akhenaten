#pragma once

#include "grid/point.h"

void map_soldier_strength_clear(void);
void map_soldier_strength_add(tile2i tile, int radius, int amount);
int map_soldier_strength_get(int grid_offset);
int map_soldier_strength_get_max(tile2i tile, int radius, tile2i &out_x);
