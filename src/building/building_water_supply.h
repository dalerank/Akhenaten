#pragma once

#include "building/building.h"

class building_water_supply : public building_impl {
public:
    building_water_supply(building &b) : building_impl(b) {}
    //virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual void update_month() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_WATER; }
};