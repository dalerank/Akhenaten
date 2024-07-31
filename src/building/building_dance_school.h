#pragma once

#include "building/building.h"


class building_dancer_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DANCE_SCHOOL, building_dancer_school)

    building_dancer_school(building &b) : building_impl(b) {}

    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void window_info_background(object_info &c) override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_DANCE_SCHOOL; }
};

void building_entertainment_school_draw_info(object_info &c);
