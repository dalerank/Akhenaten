#pragma once

#include "building/building.h"

class building_police_station : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_POLICE_STATION, building_police_station, building_impl)

    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T

    struct runtime_data_t {
        bool weapon_requested_this_month;
    } BUILDING_RUNTIME_DATA_T;

    virtual void spawn_figure() override;
    virtual void update_month() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool add_resource(e_resource resource, int amount, figure_id fid = 0) override;

    bool request_weapons_if_need();
};

ANK_CONFIG_PROPERTY(building_police_station::runtime_data_t, weapon_requested_this_month)