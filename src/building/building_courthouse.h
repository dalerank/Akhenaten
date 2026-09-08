#pragma once

#include "building/building.h"

class building_courthouse : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_COURTHOUSE, building_courthouse, building_impl)

    virtual building_courthouse *dcast_courthouse() override { return this; }

    virtual bool is_administration() const override { return true; }
};
