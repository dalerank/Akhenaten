#pragma once

#include "building/building_industry.h"

class building_wood_cutter : public building_industry {
public:
    BUILDING_METAINFO(BUILDING_WOOD_CUTTERS, building_wood_cutter, building_industry)

    virtual building_wood_cutter *dcast_wood_cutter() override { return this; }

    struct static_params : public building_static_params {
        uint8_t max_gatherers;
    } BUILDING_STATIC_DATA_T;

    virtual void on_create(int orientation) override;
    virtual bool is_administration() const override { return true; }
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_NONE; }
    virtual bool can_play_animation() const override;

    bool can_spawn_lumberjack(int max_gatherers_per_building, int carry_per_person);
};
ANK_CONFIG_STRUCT(building_wood_cutter::static_params, max_gatherers)