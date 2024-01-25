#pragma once

#include "building/building.h"

class building_shrine : public building_impl {
public:
    building_shrine(building &b) : building_impl(b) {}

    virtual void window_info_background(object_info &ctx) override;
};