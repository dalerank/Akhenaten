#pragma once

#include "building/building.h"

class building_firehouse : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FIREHOUSE, building_firehouse, building_impl)
    virtual building_firehouse *dcast_firehouse() override { return this; }

    struct runtime_data_t : public no_copy_assignment {
        int buildings_served_this_month;
        int buildings_served_this_year;
        int total_buildings_served;
        int months_active;
    } BUILDING_RUNTIME_DATA_T;
};
ANK_CONFIG_PROPERTY(building_firehouse::runtime_data_t,
    buildings_served_this_month,
    buildings_served_this_year,
    total_buildings_served,
    months_active)
