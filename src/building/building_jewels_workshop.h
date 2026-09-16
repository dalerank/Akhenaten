#pragma once

#include "building/building_industry.h"

class building_jewels_workshop : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_JEWELS_WORKSHOP, building_jewels_workshop, building_industry)

    struct static_params : public building_static_params {
        uint8_t material_reduction_per_nearby_workshop;
    } BUILDING_STATIC_DATA_T;

    virtual void update_animation() override;
    virtual void start_production() override;

private:
    int count_nearby_workshops() const;
};
ANK_CONFIG_STRUCT(building_jewels_workshop::static_params, material_reduction_per_nearby_workshop)