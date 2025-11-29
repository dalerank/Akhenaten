#pragma once

#include "building/building.h"

class building_police_station : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_POLICE_STATION, building_police_station, building_impl)

    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    virtual int animation_speed(int speed) const override { return 3; }
    //virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};