#pragma once

#include "building/building_entertainment.h"

class building_booth : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_BOOTH, building_booth, building_entertainment)
    virtual building_booth *dcast_booth() override { return this; }

    struct preview : public building_planer_renderer {
        virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const override;
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void on_create(int orientation) override {}
    virtual void update_day() override;
    virtual void update_month() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BOOTH; }
    virtual int get_fire_risk(int value) const override { return value / 10; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BOOTH; }
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual void on_undo() override;
};