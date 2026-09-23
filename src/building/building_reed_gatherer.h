#pragma once

#include "building/building_industry.h"

class building_reed_gatherer : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_REED_GATHERER, building_reed_gatherer, building_industry)
    virtual building_reed_gatherer *dcast_reed_gatherer() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CLAY_PIT; }

    bool can_spawn_gatherer(int max_gatherers_per_building, int carry_per_person);
};
