#pragma once

#include "building/building.h"

class building_bandstand : public building_impl {
public:
    building_bandstand(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int animation_speed(int speed) const override { return 4; }
    virtual int get_fire_risk(int value) const override { return value / 10; }
};