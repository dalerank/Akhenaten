#pragma once

#include "building/building.h"

class building_well : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WELL, building_well)

    building_well(building &b) : building_impl(b) {}
    virtual building_well *dcast_well() override { return this; }

    //virtual void on_create() override;
    virtual void update_month() override;
    virtual bool need_road_access() const override { return false; }
    virtual void on_place_checks() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_WELL; }
    virtual bool can_play_animation() const override;

    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};