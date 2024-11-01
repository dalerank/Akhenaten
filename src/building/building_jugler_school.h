#pragma once

#include "building/building_entertainment.h"

class building_juggler_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_JUGGLER_SCHOOL, building_juggler_school)

    building_juggler_school(building &b) : building_entertainment(b) {}
    virtual building_juggler_school *dcast_juggler_school() override { return this; }

    struct static_params : public buildings::model_t<building_juggler_school> {
        uint8_t spawn_interval;
        virtual void load(archive arch) override;
    };

    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_JUGGLER_SCHOOL; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};