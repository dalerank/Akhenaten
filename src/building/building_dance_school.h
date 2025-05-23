#pragma once

#include "building/building_entertainment.h"
#include "window/window_building_info.h"

class building_dancer_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_DANCE_SCHOOL, building_dancer_school, building_entertainment)

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENTERTAINMENT; }
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DANCE_SCHOOL; }
};
