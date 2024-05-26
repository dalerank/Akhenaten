#pragma once

#include "building/building.h"

class building_booth : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_BOOTH, building_booth)

    building_booth(building &b) : building_impl(b) {}
    virtual building_booth *dcast_booth() override { return this; }

    virtual void on_create(int orientation) override {}
    virtual void update_day() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual int get_fire_risk(int value) const override { return value / 10; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BOOTH; }
    virtual void update_count() const;
    virtual bool draw_isometric_flat_building(tile2i point, painter &ctx) override;

    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};
