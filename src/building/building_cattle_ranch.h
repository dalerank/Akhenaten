#pragma once

#include "building/building_industry.h"

class building_cattle_ranch : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_CATTLE_RANCH, building_cattle_ranch, building_industry)

    virtual bool can_play_animation() const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_COWFARM; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};