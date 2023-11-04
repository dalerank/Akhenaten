#pragma once

#include "grid/point.h"

void map_soldier_strength_clear(void);

void map_soldier_strength_add(int x, int y, int radius, int amount);

int map_soldier_strength_get(int grid_offset);

int map_soldier_strength_get_max(int x, int y, int radius, tile2i &out_x);
