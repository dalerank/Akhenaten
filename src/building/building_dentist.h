#pragma once

#include "building/building.h"

class building_dentist : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DENTIST, building_dentist, building_impl)

    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T

    struct runtime_data_t : public no_copy_assignment {
        int residents_served_this_month;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_dentist *dcast_dentist() override { return this; }

    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DENTIST; }
    virtual void spawn_figure() override;
    virtual void update_month() override;

    building_id find_noble_house_with_max_bad_teeth();
};

ANK_CONFIG_PROPERTY(building_dentist::runtime_data_t, residents_served_this_month)
