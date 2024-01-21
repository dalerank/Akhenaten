#pragma once

#include "building/building.h"

class building_booth : public building_impl {
public:
    building_booth(building &b) : building_impl(b) {}
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(vec2i point, tile2i tile, painter &ctx) override;
};
