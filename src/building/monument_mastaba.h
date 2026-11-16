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

// Matches construction.phases ids in mastaba.js (0..8). Values are stored in monument runtime.
enum e_mastaba_phase : int8_t {
    MASTABA_PHASE_SITE = 0,        // sticks + grounded fade
    MASTABA_PHASE_FOUNDATION = 1,  // grounded + structure fade
    MASTABA_PHASE_BRICKS = 2,      // brick layers / height ornaments
    MASTABA_PHASE_COMPLETE = 8,    // schedule done → finalize to MONUMENT_FINISHED
};

class building_mastaba : public building_monument {
public:
    building_mastaba(building &b) : building_monument(b) {}
    virtual building_mastaba *dcast_mastaba() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void update_day() override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool get_route_citizen_land_type(int grid_offset, int &land_result) const override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;

    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual grid_area get_area() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;

    struct base_params {
        // Large mastaba = 4×9 parts (36); keep headroom above medium's 21.
        hvector<mastaba_part, 40> config_north;
        hvector<mastaba_part, 40> config_east;
        hvector<mastaba_part, 40> config_south;
        hvector<mastaba_part, 40> config_west;
        vec2i init_tiles;
        // Construction phases live here (parts resolve to main type via get_params).
        monument construction;
        // block-engine geometry for this mastaba size.
        uint8_t part_count = 0;
        uint8_t brick_layers = 0;
        uint8_t entry_part = 0;
        // mastaba_entry.entry_points for this size.
        hvector<pyramid_entry_point, 16> entry_points;
        // mastaba_part_pair_table for this size.
        hvector<pyramid_paired_parts, 20> part_pairs;

        void finalize_construction(e_building_type btype);
    };

    virtual const monument &config() const override;

    virtual int needs_resource(e_resource resource) const override;
    virtual int needs_resource(e_resource resource, int phase) const override;
    virtual bool need_workers() const override;
    virtual bool need_bricklayers() override;
    virtual int needs_bricklayers(int ph_id) const override;
    virtual int try_assign_bricklayer(figure_id fid) override;
    virtual void place_bricklayer_block(figure_id fid) override;

    static bool clay_delivery_enabled();
    bool clay_stock_ready() const;
    // Clay of this phase still to haul after what is on site and the loads under way.
    int clay_to_haul(int loads_under_way, int load) const;

    static void update_images(building *b, int curr_phase, const vec2i size_b);
    virtual void sync_visuals() override;
    static void finalize(building *b, const vec2i size_b);
    static int get_image(int orientation, tile2i tile, tile2i start, tile2i end);
    static const base_params &get_params(e_building_type type);

    virtual void remove_worker(figure_id fid) override;
    virtual void add_workers(figure_id fid) override;

protected:
    bool draw_ornaments_and_animations_flat_impl(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_ornaments_and_animations_hight_impl(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    void update_construction_day(const vec2i tiles_size);
    void complete_construction(const vec2i tiles_size);

    void draw_flat_phase_site(painter &ctx, color color_mask, const vec2i tiles_size, int image_grounded, int image_stick);
    void draw_flat_phase_foundation(painter &ctx, color color_mask, const vec2i tiles_size, int image_grounded);
    void draw_flat_phase_bricks(painter &ctx, color color_mask, const vec2i tiles_size);

    using height_tiles = svector<tile2i, 21>;
    void draw_height_phase_bricks(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw);
    void draw_height_phase_layers(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw);
    void draw_height_phase_complete(painter &ctx, color color_mask, const vec2i tiles_size, const vec2i city_offset, const height_tiles &tiles2draw);
    void draw_height_side_figures(painter &ctx);
};

class building_small_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MASTABA, building_small_mastaba, building_mastaba)
    virtual building_small_mastaba *dcast_small_mastaba() override { return this; }

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_small_mastaba::static_params,
    init_tiles, config_north, config_east, config_south, config_west, construction,
    part_count, brick_layers, entry_part, entry_points, part_pairs);

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
    virtual building_medium_mastaba *dcast_medium_mastaba() override { return this; }

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_medium_mastaba::static_params,
    init_tiles, config_north, config_east, config_south, config_west, construction,
    part_count, brick_layers, entry_part, entry_points, part_pairs);

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

class building_large_mastaba : public building_mastaba {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MASTABA, building_large_mastaba, building_mastaba)
    virtual building_large_mastaba *dcast_large_mastaba() override { return this; }

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
};
ANK_CONFIG_STRUCT(building_large_mastaba::static_params,
    init_tiles, config_north, config_east, config_south, config_west, construction,
    part_count, brick_layers, entry_part, entry_points, part_pairs);

class building_large_mastaba_part_side : public building_large_mastaba {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MASTABA_SIDE, building_large_mastaba_part_side, building_large_mastaba)
};

class building_large_mastaba_part_wall : public building_large_mastaba {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MASTABA_WALL, building_large_mastaba_part_wall, building_large_mastaba)
};

class building_large_mastaba_part_entrance : public building_large_mastaba {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MASTABA_ENTRANCE, building_large_mastaba_part_entrance, building_large_mastaba)
};

void map_mastaba_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
tile2i building_small_mastaba_bricks_waiting_tile(building *b);
int building_small_mastabe_get_bricks_image(int orientation, e_building_type type, tile2i tile, tile2i start, tile2i end, int layer);
