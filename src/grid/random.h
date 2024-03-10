#pragma once

#include "core/buffer.h"
#include "grid/point.h"

void map_random_clear(void);
void map_random_init(void);
int map_random_get(int grid_offset);
inline int map_random_get(tile2i tile) { return map_random_get(tile.grid_offset()); }

