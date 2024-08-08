#pragma once

#include "building/building.h"

class building_juggler_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_JUGGLER_SCHOOL, building_juggler_school)

    building_juggler_school(building &b) : building_impl(b) {}
    virtual building_juggler_school *dcast_juggler_school() override { return this; }

    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual void spawn_figure() override;
    virtual void update_month() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_JUGGLER_SCHOOL; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};