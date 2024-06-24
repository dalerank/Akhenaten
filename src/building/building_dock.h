#pragma once

#include "building/building.h"

void building_river_update_open_water_access();

class building_dock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DOCK, building_dock)

    building_dock(building &b) : building_impl(b) {}
    virtual building_dock *dcast_dock() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual bool can_play_animation() const override;
    virtual void update_count() const;
    virtual void update_map_orientation(int orientation) override;
    virtual void spawn_figure() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DOCK; }
    virtual void window_info_background(object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    int trader_id();
    bool is_good_accepted(int index);
    void toggle_good_accepted(int index);
    int count_idle_dockers() const;
    void draw_dock_orders(object_info *c);
    void draw_dock(object_info *c);
    void draw_dock_orders_foreground(object_info *c);
    //void draw_dock_foreground(object_info *c);
};

struct building_dest {
    int bid;
    tile2i tile;
};

building_dest map_get_free_destination_dock(int ship_id);
building_dest map_get_queue_destination_dock(int ship_id);
bool map_tile_is_connected_to_open_water(tile2i tile);