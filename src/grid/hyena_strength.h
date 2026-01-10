#pragma once

#include "grid/point.h"

void map_hyena_strength_clear();
void map_hyena_strength_add(tile2i tile, int radius, int amount);
void map_hyena_strength_update();
int map_hyena_strength_get(int grid_offset);
inline int map_hyena_strength_get(tile2i tile) { return map_hyena_strength_get(tile.grid_offset()); }

struct max_hyena_strength_tile {
    int strength;
    tile2i tile;
};
max_hyena_strength_tile map_hyena_strength_get_max(tile2i tile, int radius);
