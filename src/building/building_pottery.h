#pragma once

#include "building/building_industry.h"

class building_pottery : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_POTTERY_WORKSHOP, building_pottery, building_industry)

    virtual building_pottery *dcast_pottery() override { return this; }

    virtual void update_animation() override;
};