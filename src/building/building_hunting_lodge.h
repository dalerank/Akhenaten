#pragma once

#include "building/building.h"

class building_hunting_lodge : public building_impl {
public:
    building_hunting_lodge(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual void window_info_background(object_info &ctx) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_HUNTER_LOUDGE; }

    int spawn_timer();
    bool can_spawn_ostrich_hunter();
};