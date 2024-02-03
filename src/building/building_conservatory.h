#pragma once

#include "building/building.h"

class building_conservatory : public building_impl {
public:
    building_conservatory(building &b) : building_impl(b) {}
    //virtual void on_create() override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_CONSERVATORY; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};