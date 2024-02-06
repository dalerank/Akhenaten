#pragma once

#include "graphics/color.h"
#include "graphics/image_desc.h"
#include "grid/point.h"
#include "core/vec2i.h"

struct painter;

void draw_building_ghost(painter &ctx, e_image_id image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);
void draw_building_ghost(painter &ctx, int image_id, vec2i tile, color color_mask = COLOR_MASK_GREEN);
int is_blocked_for_building(int grid_offset, int num_tiles, int *blocked_tiles);
void draw_partially_blocked(painter &ctx, vec2i tile, int fully_blocked, int num_tiles, int *blocked_tiles);
bool city_building_ghost_mark_deleting(tile2i tile);
