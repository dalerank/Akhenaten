#pragma once

#include "building/building_entertainment.h"

class building_juggler_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_JUGGLER_SCHOOL, building_juggler_school, building_entertainment)

    virtual building_juggler_school *dcast_juggler_school() override { return this; }

    struct static_params : public building_model {
        uint8_t spawn_interval;
        virtual void archive_load(archive arch) override;
    } BUILDING_STATIC_DATA(static_params);

    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_JUGGLER_SCHOOL; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};