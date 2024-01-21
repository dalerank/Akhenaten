#pragma once

#include "grid/point.h"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "building/building.h"

struct painter;

class building_small_mastaba : public building_impl {
public:
    building_small_mastaba(building & b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void update_day() override;
    virtual void window_info_background(object_info &ctx) override;
};

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
void draw_small_mastaba_anim_flat(painter &ctx, vec2i pixel, building *b, int color_mask);
void draw_small_mastaba_anim(painter &ctx, vec2i pixel, building *b, int color_mask);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
void building_small_mastabe_update_images(building *b, int curr_phase);
int building_small_mastabe_get_image(int orientation, tile2i tile, tile2i start, tile2i end);
tile2i building_small_mastaba_bricks_waiting_tile(building *b);
tile2i building_small_mastaba_tile4work(building *b);
int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer);