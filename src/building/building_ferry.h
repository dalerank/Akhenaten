#pragma once

#include "building/building_roadblock.h"
#include "window/window_building_info.h"

class building_ferry : public building_routeblock {
public:
    BUILDING_METAINFO(BUILDING_FERRY, building_ferry)
    building_ferry(building &b) : building_routeblock(b) {}

    virtual building_ferry *dcast_ferry() override { return this; }
    virtual building_routeblock *dcast_routeblock() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int orientation) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_top_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t verrsion) override;

    virtual bool get_permission(e_permission p) override { return false; }
};

struct info_window_ferry : public building_info_window_t<info_window_ferry> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
};