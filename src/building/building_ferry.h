#pragma once

#include "building/building_roadblock.h"
#include "figure/figure_type.h"

class building_ferry : public building_routeblock {
public:
    BUILDING_METAINFO(BUILDING_FERRY, building_ferry, building_routeblock)

    static constexpr int FERRY_QUEUE_CAPACITY = 32;
    static constexpr int FERRY_PASSENGER_SLOTS = 4;

    struct static_params : public building_static_params {
        uint16_t dock_wait_ticks_min;
        uint16_t dock_wait_ticks_max;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        figure_id queue[FERRY_QUEUE_CAPACITY];
        uint8_t queue_head;
        uint8_t queue_count;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_ferry *dcast_ferry() override { return this; }
    virtual building_routeblock *dcast_routeblock() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_month() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int orientation) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_top_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t verrsion) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;
    virtual void on_destroy() override;

    virtual bool get_permission(e_permission p) override { return false; }

    virtual void spawn_figure() override;

    tile2i dock_tile() const;

    bool queue_is_full() const;
    int queue_size() const;
    bool queue_contains(figure_id fid) const;
    bool queue_push(figure_id fid);
    figure_id queue_pop();
    void queue_release_waiting();

    // OG figure_route_find_ferry_on_path: 1 = partner ahead + staffed, 0 = partner ahead unstaffed, 2 = not on path.
    static int route_find_partner_on_path(const figure &f, building *ferry);
    // Called from movement when a boards_ferry walker is about to enter this landing.
    bool try_enter_ferry(figure &f);
};

// OG figure_is_queued_for_ferry: true unless waiting (7) without a queue slot.
bool figure_is_queued_for_ferry(figure_id fid);
ANK_CONFIG_STRUCT(building_ferry::static_params, dock_wait_ticks_min, dock_wait_ticks_max)
ANK_CONFIG_PROPERTY(building_ferry::runtime_data_t, queue_head, queue_count)
