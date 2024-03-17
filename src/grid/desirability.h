#pragma once

#include "grid/point.h"

void map_desirability_clear();
void map_desirability_update();

int map_desirability_get(int grid_offset);
inline int map_desirability_get(tile2i tile) { return map_desirability_get(tile.grid_offset()); }
int map_desirability_get_max(tile2i tile, int size);

int map_desirabilty_avg(tile2i tile, int size);
