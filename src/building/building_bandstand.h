#pragma once

#include "building/building.h"

class building_bandstand : public building_impl {
public:
    building_bandstand(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void spawn_figure() override;
    virtual void window_info_background(object_info &c) override;
};