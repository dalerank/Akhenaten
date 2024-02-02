#pragma once

#include "building/building.h"

class building_palace : public building_impl {
public:
    building_palace(building &b) : building_impl(b) {}
    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};