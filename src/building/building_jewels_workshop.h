#pragma once

#include "building/building_industry.h"

class building_jewels_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_JEWELS_WORKSHOP, building_jewels_workshop, building_industry)

    virtual void update_animation() override;
};
