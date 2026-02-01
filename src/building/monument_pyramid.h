#pragma once

#include "grid/point.h"
#include "core/custom_span.hpp"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "building/building.h"

struct painter;

class building_pyramid : public building_monument {
public:
    building_pyramid(building &b) : building_monument(b) {}
    virtual building_pyramid *dcast_pyramid() override { return this; }

    virtual bool get_route_citizen_land_type(int grid_offset, int &land_result) const override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;

    struct base_params {
        e_building_type corner_type;
        e_building_type wall_type;
        e_building_type cone_type;
        e_building_type filler_type;

        vec2i init_tiles;
    };

    static void update_images(building *b, int curr_phase, const vec2i size_b);
};

class building_stepped_pyramid : public building_pyramid {
public:
    building_stepped_pyramid(building &b) : building_pyramid(b) {}

    virtual void on_place(int orientation, int variant) override;
    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_place_checks() override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    bool draw_ornaments_and_animations_flat_impl(building &base, painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_ornaments_and_animations_hight_impl(building &base, painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);

    void update_day(const vec2i tiles_size);
    virtual bool need_workers() const override;
    span_const<uint16_t> active_workers() const;

    static void finalize(building *b, const vec2i size_b);
    static int get_image(int orientation, tile2i tile, tile2i start, tile2i end);

    virtual void remove_worker(figure_id fid) override;
    virtual void add_workers(figure_id fid) override;
};

class building_small_stepped_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STEPPED_PYRAMID, building_small_stepped_pyramid, building_stepped_pyramid)
    virtual building_small_stepped_pyramid *dcast_small_stepped_pyramid() override { return this; }

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;

    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
};
ANK_CONFIG_STRUCT(building_small_stepped_pyramid::static_params, 
    init_tiles, corner_type, wall_type, cone_type, filler_type);

class building_small_stepped_pyramid_corner : public building_small_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STEPPED_PYRAMID_CORNER, building_small_stepped_pyramid_corner, building_small_stepped_pyramid)
};

class building_small_stepped_pyramid_wall : public building_small_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_STEPPED_PYRAMID_WALL, building_small_stepped_pyramid_wall, building_small_stepped_pyramid)
};

class building_medium_stepped_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STEPPED_PYRAMID, building_medium_stepped_pyramid, building_stepped_pyramid)
    virtual building_medium_stepped_pyramid *dcast_medium_stepped_pyramid() override { return this; }

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;

    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
};
ANK_CONFIG_STRUCT(building_medium_stepped_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type);

class building_medium_stepped_pyramid_corner : public building_medium_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER, building_medium_stepped_pyramid_corner, building_medium_stepped_pyramid)
};

class building_medium_stepped_pyramid_wall : public building_medium_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STEPPED_PYRAMID_WALL, building_medium_stepped_pyramid_wall, building_medium_stepped_pyramid)
};

void map_pyramid_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
