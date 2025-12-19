#pragma once

#include <cstdint>

#include "building/building_type.h"
#include "grid/point.h"

enum e_highligth_mode {
    ehighligth_none,
    ehighligth_blue,
    ehighligth_red,
    ehighligth_green,
    ehighligth_yellow,
};

int map_building_at(int grid_offset);
int map_building_at(tile2i tile);
void map_building_set(int grid_offset, int building_id);

e_building_type map_building_type_at(tile2i tile);
bool map_building_type_is(tile2i tile, e_building_type type);

int map_building_height_at(int grid_offset);
void map_building_height_set(int grid_offset, int8_t height);

int map_building_damage_increase(int grid_offset);
int map_get_building_damage(int grid_offset);
inline int map_get_building_damage(tile2i tile) { return map_get_building_damage(tile.grid_offset()); }
void map_building_damage_clear(int grid_offset);

int map_rubble_building_type(int grid_offset);
inline int map_rubble_building_type(tile2i tile) { return map_rubble_building_type(tile.grid_offset()); }

void map_set_rubble_building_type(int grid_offset, int type);

void map_building_clear(void);

void map_highlight_set(int grid_offset, e_highligth_mode mode);
inline void map_highlight_set(tile2i tile, e_highligth_mode mode) { map_highlight_set(tile.grid_offset(), mode); }
void map_highlight_clear(int grid_offset);
e_highligth_mode map_is_highlighted(int grid_offset);
inline e_highligth_mode map_is_highlighted(tile2i tile) { return map_is_highlighted(tile.grid_offset()); }
void map_clear_highlights();

void map_building_update_all_tiles();

struct adjust_orientation {
    bool match;
    int orientation;
};

adjust_orientation map_adjust_building_determine_orientation(tile2i tile, int size, bool adjust_xy, bool adjacent, e_building_type btype);