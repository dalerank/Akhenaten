#pragma once

#include "grid/point.h"

int map_bridge_building_length(void);

void map_bridge_reset_building_length(void);

int map_bridge_calculate_length_direction(int x, int y, int* length, int* direction);

int map_bridge_get_sprite_id(int index, int length, int direction, bool is_ship_bridge);
int map_bridge_add(int x, int y, bool is_ship_bridge);

void map_bridge_remove(int grid_offset, int mark_deleted);

void map_bridge_update_after_rotate(int counter_clockwise);

int map_bridge_count_figures(int grid_offset);

int map_is_bridge(int grid_offset);
inline int map_is_bridge(tile2i tile) { return map_is_bridge(tile.grid_offset()); }

int map_bridge_height(int grid_offset);
