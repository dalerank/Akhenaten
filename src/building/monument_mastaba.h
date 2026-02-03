#pragma once

#include "grid/point.h"
#include "core/custom_span.hpp"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "building/building.h"

struct painter;

struct mastaba_part {
    e_building_type type;
    tile2i offset;
    building *b;
    bool base;
};
ANK_CONFIG_STRUCT(mastaba_part,
    type, offset, base)

class building_mastaba : public building_monument {
public:
    building_mastaba(building &b) : building_monument(b) {}
    virtual building_mastaba *dcast_mastaba() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool get_route_citizen_land_type(int grid_offset, int &land_result) const override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
    };

    struct base_params {
        hvector<mastaba_part, 10> config_north;
        hvector<mastaba_part, 10> config_east;
        hvector<mastaba_part, 10> config_south;
        hvector<mastaba_part, 10> config_west;
        vec2i init_tiles;
    };
    
    bool draw_ornaments_and_animations_flat_impl(building &base, painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_ornaments_and_animations_hight_impl(building &base, painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);

    void update_day(const vec2i tiles_size);
    virtual bool need_workers() const override;

    static void update_images(building *b, int curr_phase, const vec2i size_b);
    static void finalize(building *b, const vec2i size_b);
    static int get_image(int orientation, tile2i tile, tile2i start, tile2i end);

    virtual void remove_worker(figure_id fid) override;
    virtual void add_workers(figure_id fid) override;
};

class building_small_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA, building_small_mastaba, building_mastaba)
    virtual building_small_mastaba *dcast_small_mastaba() override { return this; }

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;

    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    
};
ANK_CONFIG_STRUCT(building_small_mastaba::static_params, 
    init_tiles, config_north, config_east, config_south, config_west);

class building_small_mastaba_part_side : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_SIDE, building_small_mastaba_part_side, building_small_mastaba)
};

class building_small_mastaba_part_wall : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_WALL, building_small_mastaba_part_wall, building_small_mastaba)
};

class building_small_mastaba_part_entrance : public building_small_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA_ENTRANCE, building_small_mastaba_part_entrance, building_small_mastaba)
};

class building_medium_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MASTABA, building_medium_mastaba, building_mastaba)

    virtual building_medium_mastaba *dcast_medium_mastaba() override { return nullptr; }

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;

    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
        
};
ANK_CONFIG_STRUCT(building_medium_mastaba::static_params,
    init_tiles, config_north, config_east, config_south, config_west);

class building_medium_mastaba_part_side : public building_medium_mastaba {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MASTABA_SIDE, building_medium_mastaba_part_side, building_medium_mastaba)
};

class building_medium_mastaba_part_wall : public building_medium_mastaba {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MASTABA_WALL, building_medium_mastaba_part_wall, building_medium_mastaba)
};

class building_medium_mastaba_part_entrance : public building_medium_mastaba {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MASTABA_ENTRANCE, building_medium_mastaba_part_entrance, building_medium_mastaba)
};

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
tile2i building_small_mastaba_bricks_waiting_tile(building *b);
int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer);