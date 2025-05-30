#pragma once

#include "building/building_entertainment.h"

class building_senet_house : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_SENET_HOUSE, building_senet_house, building_entertainment)

    virtual void on_place_checks() override;
    virtual void on_destroy() override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_SENET_HOUSE; }
    virtual int animation_speed(int speed) const override { return 3; }
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};


class building_bullfight_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_BULLFIGHT_SCHOOL, building_bullfight_school, building_entertainment)

    //virtual void on_place_checks() override;
    //virtual void on_destroy() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};