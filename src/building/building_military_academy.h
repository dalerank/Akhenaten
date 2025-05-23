#pragma once

#include "building/building.h"

class building_military_academy : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MILITARY_ACADEMY, building_military_academy, building_impl)

    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};