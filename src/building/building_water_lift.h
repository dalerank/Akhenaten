#pragma once

#include "building/building.h"

class building_water_lift : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_WATER_LIFT, building_water_lift)

    building_water_lift(building &b) : building_impl(b) {}

    virtual void window_info_background(object_info &c) override;
    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual int animation_speed(int speed) const;
    virtual void spawn_figure() override;
    virtual void update_count() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_POLICE; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void update_map_orientation(int orientation) override;
};