#pragma once

#include "building/building.h"

class building_wood_cutter : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WOOD_CUTTERS, building_wood_cutter)

    building_wood_cutter(building &b) : building_impl(b) {}
    virtual building_wood_cutter *dcast_wood_cutter() override { return this; }

    virtual void on_create(int orientation) override;
    virtual bool is_administration() const override { return true; }
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_count() const override;
};