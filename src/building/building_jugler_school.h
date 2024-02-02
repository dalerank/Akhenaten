#pragma once

#include "building/building.h"

class building_juggler_school : public building_impl {
public:
    building_juggler_school(building &b) : building_impl(b) {}
    virtual void window_info_background(object_info &c) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual void spawn_figure() override;
    virtual void update_month() override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_JUGGLER_SCHOOL; }
};