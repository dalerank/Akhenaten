#pragma once

#include "building/building.h"

class building_well : public building_impl {
public:
    building_well(building &b) : building_impl(b) {}
    //virtual void on_create() override;
    virtual void update_month() override;
    virtual bool need_road_access() const { return false; }
    virtual void window_info_background(object_info &ctx) override;
};