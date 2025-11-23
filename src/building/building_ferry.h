#pragma once

#include "building/building_roadblock.h"
#include "window/window_building_info.h"

class building_ferry : public building_routeblock {
public:
    BUILDING_METAINFO(BUILDING_FERRY, building_ferry, building_routeblock)

    struct preview : building_planer_renderer {
        virtual int construction_update(build_planner &planer, tile2i start, tile2i end) const override;
    };

    struct runtime_data_t {
        int dock_tiles[2];
    } BUILDING_RUNTIME_DATA(runtime_data_t);

    virtual building_ferry *dcast_ferry() override { return this; }
    virtual building_routeblock *dcast_routeblock() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void update_month() override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_map_orientation(int orientation) override;
    virtual bool force_draw_height_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual bool force_draw_top_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t verrsion) override;
    virtual void set_water_access_tiles(const water_access_tiles &tiles) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;

    virtual bool get_permission(e_permission p) override { return false; }
    
    virtual void spawn_figure() override;
};

struct info_window_ferry : public building_info_window_t<info_window_ferry> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
};