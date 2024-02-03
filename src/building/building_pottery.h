#pragma once

#include "building/building.h"

class building_pottery : public building_impl {
public:
    building_pottery(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};