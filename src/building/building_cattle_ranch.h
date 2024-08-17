#pragma once

#include "building/building.h"

class building_cattle_ranch : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_CATTLE_RANCH, building_cattle_ranch)

    building_cattle_ranch(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual bool is_workshop() const override { return true; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_COWFARM; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};