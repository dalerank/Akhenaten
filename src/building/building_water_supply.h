#pragma once

#include "building/building.h"

class building_water_supply : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WATER_SUPPLY, building_water_supply, building_impl)

    virtual building_water_supply *dcast_water_supply() override { return this; }
};
