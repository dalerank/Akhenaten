#pragma once

#include "building/building.h"

class building_physician : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_PHYSICIAN, building_physician, building_impl)

    virtual building_physician* dcast_physician() override { return this; }
};
