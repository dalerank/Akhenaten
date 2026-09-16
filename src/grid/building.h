#pragma once

#include <cstdint>

#include "building/building_type.h"
#include "core/tokenum.h"
#include "grid/point.h"

enum e_highlight_mode : uint8_t {
    HIGHLIGHT_NONE = 0,
    HIGHLIGHT_BLUE = 1,
    HIGHLIGHT_RED = 2,
    HIGHLIGHT_GREEN = 3,
    HIGHLIGHT_YELLOW = 4,

    HIGHLIGHT_MAX
};
using e_highlight_mode_tokens_t = token_holder<e_highlight_mode, HIGHLIGHT_NONE, HIGHLIGHT_MAX>;
extern const e_highlight_mode_tokens_t e_highlight_mode_tokens;

int map_building_at(int grid_offset);
int map_building_at(tile2i tile);
void map_building_set(int grid_offset, int building_id);

e_building_type map_building_type_at(tile2i tile);
bool map_building_type_is(tile2i tile, e_building_type type);

int map_building_height_at(int grid_offset);
void map_building_height_set(int grid_offset, int8_t height);

int map_get_building_damage(int grid_offset);
inline int map_get_building_damage(tile2i tile) { return map_get_building_damage(tile.grid_offset()); }
void map_building_damage_clear(int grid_offset);

int map_rubble_building_type(int grid_offset);
inline int map_rubble_building_type(tile2i tile) { return map_rubble_building_type(tile.grid_offset()); }

void map_set_rubble_building_type(int grid_offset, int type);

void map_building_clear(void);

void map_highlight_set(int grid_offset, e_highlight_mode mode);
inline void map_highlight_set(tile2i tile, e_highlight_mode mode) { map_highlight_set(tile.grid_offset(), mode); }
void map_highlight_clear(int grid_offset);
e_highlight_mode map_is_highlighted(int grid_offset);
inline e_highlight_mode map_is_highlighted(tile2i tile) { return map_is_highlighted(tile.grid_offset()); }
void map_clear_highlights();

void map_building_update_all_tiles();

struct adjust_orientation {
    bool match;
    int orientation;
};

adjust_orientation map_adjust_building_determine_orientation(tile2i tile, int size, bool adjust_xy, bool adjacent, e_building_type btype);