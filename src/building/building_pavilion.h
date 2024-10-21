#pragma once

#include "building/building_entertainment.h"

class building_pavilion : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_PAVILLION, building_pavilion)
    building_pavilion(building &b) : building_entertainment(b) {}
    
    virtual void on_create(int orientation) override;
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual building_pavilion *dcast_pavilion() override { return this; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_PAVILION; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void window_info_background(object_info &c) override;
    virtual void on_undo() override;

    virtual void update_count() const override;
    virtual void spawn_figure() override;

    static void ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation);
};