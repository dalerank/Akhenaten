#pragma once

#include "grid/point.h"

void map_tree_clear();
void map_tree_push_back(int grid_offset);
void map_tree_foreach_tile(void (*callback)(int grid_offset));
void map_tree_update_image(int grid_offset);
void map_tree_growth_update();
void map_tree_update_image_3x3(int grid_offset);
void map_tree_update_all_tiles();
void map_tree_update_region_tiles(int x_min, int y_min, int x_max, int y_max);
void map_tree_update_region_tiles(tile2i min, tile2i max);