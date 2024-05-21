#pragma once

#include "building/building.h"

class building_chariots_workshop : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_CHARIOTS_WORKSHOP, building_brick_tower)
    building_chariots_workshop(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    //virtual void window_info_background(object_info &c) override;
    //virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
