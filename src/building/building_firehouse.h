#pragma once

#include "building/building.h"

class building_firehouse : public building_impl {
public:
    building_firehouse(building &b) : building_impl(b) {}
    void spawn_figure() override;
};