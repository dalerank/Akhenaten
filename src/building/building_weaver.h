#pragma once

#include "building/building_industry.h"

class building_weaver : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_WEAVER_WORKSHOP, building_weaver)

    building_weaver(building &b) : building_industry(b) {}

    virtual void on_place_checks() override;
    virtual bool can_play_animation() const override;

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_count() const override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
};