#pragma once

#include "graphics/color.h"
#include "graphics/image_desc.h"
#include "grid/point.h"
#include "core/vec2i.h"
#include "core/svector.h"

struct painter;

struct blocked_tile {
    tile2i tile;
    bool blocked;
};

void draw_building_ghost(painter &ctx, e_image_id image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);
void draw_building_ghost(painter &ctx, int image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);

using blocked_tile_vec = svector<blocked_tile, 36>;
int is_blocked_for_building(tile2i tile, int size, blocked_tile_vec &blocked_tiles);
int is_blocked_for_farm(tile2i tile, int size, blocked_tile_vec &blocked_tiles);
void draw_partially_blocked(painter &ctx, int fully_blocked, const blocked_tile_vec &blocked_tiles);
void draw_flat_tile(painter &ctx, vec2i pixel, color color_mask);
bool city_building_ghost_mark_deleting(tile2i tile);

extern const vec2i VIEW_OFFSETS[];
