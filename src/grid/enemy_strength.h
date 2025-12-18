#pragma once

#include "grid/point.h"

void map_enemy_strength_clear();
void map_enemy_strength_add(tile2i tile, int radius, int amount);
int map_enemy_strength_get(int grid_offset);
inline int map_enemy_strength_get(tile2i tile) { return map_enemy_strength_get(tile.grid_offset()); }

struct max_enemy_strength_tile {
    int strength;
    tile2i tile;
};
max_enemy_strength_tile map_enemy_strength_get_max(tile2i tile, int radius);

