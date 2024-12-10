#pragma once

#include "building/building.h"

class building_dock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DOCK, building_dock)

    building_dock(building &b) : building_impl(b) {}
    virtual building_dock *dcast_dock() override { return this; }

    struct static_params : public buildings::model_t<building_dock> {
        virtual void load(archive arch) override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_tick(bool refresh_only) override;
    virtual bool can_play_animation() const override;
    virtual void update_count() const override;
    virtual void update_map_orientation(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DOCK; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void highlight_waypoints() override;

    void unaccept_all_goods();
    int trader_id();
    int trader_city_id();
    bool is_trade_accepted(e_resource r);
    void toggle_good_accepted(e_resource r);
    int count_idle_dockers() const;
    bool accepts_ship(int ship_id);
    tile2i moor_tile() const;
    tile2i wait_tile() const;
    tile2i reid_tile() const;

    static const static_params &current_params() { return (const static_params &)params(TYPE); }
};

struct building_dest {
    int bid;
    tile2i tile;
};

building_dest map_get_free_destination_dock(int ship_id);
building_dest map_get_queue_destination_dock(int ship_id);
bool map_tile_is_connected_to_open_water(tile2i tile);