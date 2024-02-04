#pragma once

#include "building/building.h"

class building_statue : public building_impl {
public:
    building_statue(building &b) : building_impl(b) {}
    virtual void on_create() override;
    virtual bool is_workshop() const override { return true; }
    virtual void window_info_background(object_info &c) override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_STATUE; }
};

int building_statue_random_variant(int type, int variant);
int building_statue_next_variant(int type, int variant);

int building_statue_get_image(int type, int orientation, int variant);
int building_statue_get_image_from_value(int type, int combined, int variant, int map_orientation);