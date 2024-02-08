#pragma once

#include "building/building.h"

class building_architect_post : public building_impl {
public:
    building_architect_post(building &b) : building_impl(b) {}
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_DAMAGE; }
    virtual void window_info_background(object_info &c) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_ENGINEERS_POST; }
};