#pragma once

#include "building/building_type.h"
#include "grid/point.h"

int map_building_at(int grid_offset);
int map_building_at(tile2i tile);

void map_building_set(int grid_offset, int building_id);

int map_building_damage_increase(int grid_offset);

void map_building_damage_clear(int grid_offset);

int map_rubble_building_type(int grid_offset);

void map_set_rubble_building_type(int grid_offset, int type);

void map_building_clear(void);

void map_highlight_set(int grid_offset, int mode);
void map_highlight_clear(int grid_offset);
int map_is_highlighted(int grid_offset);
void map_clear_highlights(void);

int map_building_is_reservoir(int x, int y);
void map_building_update_all_tiles();