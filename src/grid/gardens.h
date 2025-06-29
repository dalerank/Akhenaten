#pragma once

#include "grid/point.h"

void map_tiles_gardens_clear_all();
void map_tiles_gardens_update_all();
void map_tiles_gardens_determine();
int map_tiles_garden_get(tile2i tile, bool with_decay);
void map_tiles_garden_set(tile2i tile, int value);
int map_tiles_garden_decay_get(tile2i tile);
int map_tiles_garden_decay_update(tile2i tile, int delta);
int map_garden_at(int grid_offset);