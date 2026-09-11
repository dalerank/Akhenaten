#pragma once

#include "building/building.h"

class building_physician : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_PHYSICIAN, building_physician, building_impl)

    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T

    struct runtime_data_t : public no_copy_assignment {
        int residents_served_this_month;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_physician* dcast_physician() override { return this; }

    virtual void update_month() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_PHYSICIAN; }
};

ANK_CONFIG_PROPERTY(building_physician::runtime_data_t, residents_served_this_month)
