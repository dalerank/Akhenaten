#pragma once

#include "building/building.h"

class building_firehouse : public building_impl {
public:
    building_firehouse(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &c) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_FIRE; }
    virtual int animation_speed(int speed) const override { return 4; }
};