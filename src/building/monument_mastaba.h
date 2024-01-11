#pragma once

#include "grid/point.h"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"

struct painter;
class building;

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
void draw_small_mastaba_anim_flat(painter &ctx, vec2i pixel, building *b, int color_mask);
void draw_small_mastaba_anim(painter &ctx, vec2i pixel, building *b, int color_mask);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
void building_small_mastabe_update_images(building *b, int curr_phase);
void building_small_mastabe_update_day(building *b);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
tile2i building_small_mastaba_bricks_waiting_tile(building *b);
tile2i building_small_mastaba_tile4work(building *b);
int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer);