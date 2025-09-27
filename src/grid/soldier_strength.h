#pragma once

#include "grid/point.h"

void map_soldier_strength_clear();
void map_soldier_strength_add(tile2i tile, int radius, int amount);
int map_soldier_strength_get(int grid_offset);

struct max_strength_tile {
    int strength;
    tile2i tile;
};
max_strength_tile map_soldier_strength_get_max(tile2i tile, int radius);
