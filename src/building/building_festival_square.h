#pragma once

#include "building/building.h"

class building_festival_square : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FESTIVAL_SQUARE, building_festival_square)

    building_festival_square(building &b) : building_impl(b) {}

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_day() override;
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual void on_undo() override;
    virtual void on_post_load() override;

    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};