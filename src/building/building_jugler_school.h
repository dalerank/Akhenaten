#pragma once

#include "building/building_entertainment.h"

class building_juggler_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_JUGGLER_SCHOOL, building_juggler_school, building_entertainment)

    virtual building_juggler_school *dcast_juggler_school() override { return this; }

    struct static_params : public building_static_params {
        uint8_t spawn_delay_100_percent;
        uint8_t spawn_delay_75_percent;
        uint8_t spawn_delay_50_percent;
        uint8_t spawn_delay_25_percent;
        uint8_t spawn_delay_default;  // для 1-24% работников
    } BUILDING_STATIC_DATA_T;

    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_JUGGLER_SCHOOL; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};
ANK_CONFIG_STRUCT(building_juggler_school::static_params, 
    spawn_delay_100_percent, spawn_delay_75_percent, spawn_delay_50_percent, 
    spawn_delay_25_percent, spawn_delay_default)