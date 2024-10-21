#pragma once

#include "building/building_entertainment.h"
#include "window/window_building_info.h"

class building_bandstand : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_BANDSTAND, building_bandstand)
    building_bandstand(building &b) : building_entertainment(b) {}
    virtual building_bandstand *dcast_bandstand() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_day() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual void spawn_figure() override;
    virtual int animation_speed(int speed) const override { return 4; }
    virtual int get_fire_risk(int value) const override { return value / 10; }
    virtual void update_count() const;
    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BANDSTAND; }
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void on_undo() override;

    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    void draw_shows_musicians(painter &ctx, vec2i pixel, int direction, color color_mask);
    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};