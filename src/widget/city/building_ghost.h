#pragma once

#include "graphics/color.h"
#include "graphics/image_desc.h"
#include "grid/point.h"
#include "core/vec2i.h"

#include <vector>

struct painter;

struct blocked_tile {
    tile2i tile;
    bool blocked;
};

void draw_building_ghost(painter &ctx, e_image_id image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);
void draw_building_ghost(painter &ctx, int image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);
int is_blocked_for_building(tile2i tile, int size, std::vector<blocked_tile> &blocked_tiles);
void draw_flat_tile(painter &ctx, int x, int y, color color_mask);
bool city_building_ghost_mark_deleting(tile2i tile);

extern const vec2i VIEW_OFFSETS[];
