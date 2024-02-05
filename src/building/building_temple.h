#pragma once

#include "building/building.h"

class building_temple : public building_impl {
public:
    building_temple(building &b) : building_impl(b) {}
    //virtual void on_create() override;
    virtual e_overlay get_overlay() const override;
    virtual e_sound_channel_city sound_channel() const override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
};