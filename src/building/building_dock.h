#pragma once

#include "building/building.h"
#include "empire/trader_handler.h"

class building_dock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DOCK, building_dock, building_impl)

    struct runtime_data_t {
        short queued_docker_id;
        int dock_tiles[2];
        sbitarray64 trading_goods;
        uint8_t num_ships;
        short docker_ids[3];
        figure_id trade_ship;
        uint8_t docker_anim_frame;
        e_figure_type process_type;
        bool reparing;
        short progress;
        bool has_fish;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_dock *dcast_dock() override { return this; }

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_tick(bool refresh_only) override;
    virtual bool can_play_animation() const override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void update_map_orientation(int orientation) override;
    virtual void spawn_figure() override;
    virtual void update_graphic() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DOCK; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void highlight_waypoints() override;
    virtual void set_water_access_tiles(const water_access_tiles &tiles) override;

    void unaccept_all_goods();
    empire_trader_handle empire_trader() const;
    empire_city_handle trader_city();
    bool is_trade_accepted(e_resource r);
    void toggle_good_accepted(e_resource r);
    int count_idle_dockers() const;
    bool accepts_ship(int ship_id);
    tile2i moor_tile() const;
    tile2i wait_tile() const;
    tile2i reid_tile() const;
};

building_dest map_get_free_destination_dock(int ship_id);
building_dest map_get_queue_destination_dock(int ship_id);
bool map_tile_is_connected_to_open_water(tile2i tile);