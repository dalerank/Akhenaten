#pragma once

#include "building/building.h"

class building_mansion : public building_impl {
public:
    building_mansion(building &b) : building_impl(b) {}
    virtual void window_info_background(object_info &ctx) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_MANSION; }
};