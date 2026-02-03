#pragma once

#include "building/building_entertainment.h"
#include "window/window_building_info.h"

class building_bandstand : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_BANDSTAND, building_bandstand, building_entertainment)
    virtual building_bandstand *dcast_bandstand() override { return this; }

    enum {
        musician_anim = 0,
        juggler_anim = 1,
    };

    struct preview : public building_planer_renderer {
        virtual bool ghost_allow_tile(build_planner & p, tile2i tile) const override;
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    virtual void on_create(int orientation) override;
    virtual void update_day() override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual void spawn_figure() override;
    virtual int get_fire_risk(int value) const override { return value / 10; }
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_BANDSTAND; }
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void on_undo() override;
    virtual bool get_route_citizen_land_type(int grid_offset, int &land_result) const override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;
     
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    void draw_shows_musicians(painter &ctx, vec2i pixel, tile2i tile, int direction, color color_mask);
    void draw_shows_juggler(painter &ctx, vec2i pixel, tile2i tile, int direction, color color_mask);

    void map_add_bandstand_tiles();
};