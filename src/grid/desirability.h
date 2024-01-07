#pragma once

#include "core/buffer.h"
#include "grid/point.h"

void map_desirability_clear(void);
void map_desirability_update(void);

int map_desirability_get(int grid_offset);
int map_desirability_get_max(tile2i tile, int size);

int map_desirabilty_avg(tile2i tile, int size);
