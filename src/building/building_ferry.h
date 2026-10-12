#pragma once

#include "building/building_roadblock.h"

class building_ferry : public building_routeblock {
public:
    BUILDING_METAINFO(BUILDING_FERRY, building_ferry, building_routeblock)

    enum e_crossing_phase : uint8_t {
        phase_wait_home = 0,
        phase_crossing = 1,
        phase_wait_away = 2,
        phase_returning = 3,
    };

    struct static_params : public building_static_params {
        uint16_t dock_wait_ticks_min;
        uint16_t dock_wait_ticks_max;
    } BUILDING_STATIC_DATA_T;

    struct runtime_data_t {
        e_crossing_phase phase;
        int16_t wait_remaining;
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

    virtual bool get_permission(e_permission p) override { return false; }

    virtual void spawn_figure() override;

    tile2i dock_tile() const;

private:
    void update_crossing();
    void roll_dock_wait();
    bool is_pair_leader(building *partner) const;
};
ANK_CONFIG_STRUCT(building_ferry::static_params, dock_wait_ticks_min, dock_wait_ticks_max)
ANK_CONFIG_PROPERTY(building_ferry::runtime_data_t, phase, wait_remaining)
