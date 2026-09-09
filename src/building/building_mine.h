#pragma once

#include "building/building_industry.h"

class building_mine : public building_industry {
public:
    building_mine(building &b) : building_industry(b) {}
    virtual building_mine *dcast_mine() override { return this; }
};
