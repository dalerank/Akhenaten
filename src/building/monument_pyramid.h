#pragma once

#include "grid/point.h"
#include "core/custom_span.hpp"
#include "core/vec2i.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "building/building.h"

struct painter;

struct stair_t {
    uint8_t phase;
    tile2i part;
    animation_t tex;
    vec2i offset;
};
ANK_CONFIG_STRUCT(stair_t, phase, part, tex, offset)

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
        // OG pyramid block engine style (NONE = remake tile-progress only).
        // Mastaba is a separate engine; all pyramid styles share this one.
        e_pyramid_style pyramide_type = PYRAMID_STYLE_NONE;

        vec2i init_tiles;
        vec2i enter_offset;
        hvector<stair_t, 48> stairs;
    };

    virtual const base_params &pyramid_params() const = 0;
    static const base_params &params_for_type(e_building_type type);

    tile2i footprint_nw() const;
    const base_params &footprint_params() const;

    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override { return footprint_nw().shifted(footprint_params().enter_offset); }
    virtual grid_area get_area() const override;

    // OG pyramid block engine when pyramide_type != NONE.
    virtual void sync_visuals() override;
    virtual bool need_bricklayers() override;
    virtual bool need_stonemason() override;
    virtual int try_assign_bricklayer(figure_id fid) override;
    virtual void place_bricklayer_block(figure_id fid) override;

protected:
    // true ⇒ caller must return (engine owns the day).
    bool run_block_day();
    // Remake layer/part types + map tiles, then MONUMENT_FINISHED.
    virtual void finish_block_construction();
};

class building_stepped_pyramid : public building_pyramid {
public:
    struct layer_area {
        tile2i begin;
        tile2i end;
        vec2i size;
    };

    building_stepped_pyramid(building &b) : building_pyramid(b) {}

    virtual void on_place(int orientation, int variant) override;
    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_config_reload() override;
    virtual void on_place_checks() override;
    virtual void on_destroy() override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void on_phase_changed(int old, int current) override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;


    struct preview_renderer : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        // Use init_tiles for camera→NW (building_size is only the 2×2 part).
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };
    using preview = preview_renderer;

    bool draw_ornaments_and_animations_flat_impl(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_ornaments_and_animations_hight_impl(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_unfinished_height_ornaments(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    bool draw_completed_height_ornaments(painter &ctx, vec2i point, tile2i tile, color mask, const vec2i tiles_size);
    virtual bool use_polish_sprites_for_layer(int layer) const { return false; }
    void draw_ornaments_and_animations_stairs_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size);
    void change_parts_types_in_layer(tile2i begin, const vec2i layer_size, uint8_t layer);

    void sync_footprint_layers(int done_blocks, int total_blocks);
    virtual void sync_visuals() override;
    virtual void finish_block_construction() override;

    void assign_stair();
    layer_area get_layer_area(int layer) const;
    int get_bricks_image(int orientation, tile2i tile, tile2i start, tile2i end, int layer);
    // polished=true uses corner_polish/wall_polish/base_polish when present.
    int get_masonry_image(int orientation, tile2i tile, tile2i start, tile2i end, int layer, bool polished);

    void update_day(const vec2i tiles_size);
    void draw_phase_3_5_tile(painter &ctx, color color_mask, int channel_base_id_1, int channel_base_id_2, const vec2i tiles_size);
    void setup_phase_6_tiles();
    void setup_phase_6_basement();
    virtual bool need_workers() const override;
    span_const<uint16_t> active_workers() const override;

    static void finalize(building *b, const vec2i size_b);
    static int get_image(const building_static_params &, int orientation, tile2i tile, tile2i start, tile2i end);
    static int get_channel_image(int orientation, tile2i tile, tile2i start, tile2i end, int channel_base_id);

    virtual void remove_worker(figure_id fid) override;
    virtual void add_workers(figure_id fid) override;
    virtual void set_tile_progress(tile2i tile, int v) override;
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
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_stepped_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

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
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_stepped_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

class building_medium_stepped_pyramid_corner : public building_medium_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER, building_medium_stepped_pyramid_corner, building_medium_stepped_pyramid)
};

class building_medium_stepped_pyramid_wall : public building_medium_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_STEPPED_PYRAMID_WALL, building_medium_stepped_pyramid_wall, building_medium_stepped_pyramid)
};

// Large stepped pyramid (20×20, id 250). Same shared stepped machinery as small/medium,
// only the footprint (init_tiles) and phase schedule differ. Limestone casing polish is
// true/mudbrick only, not stepped.
class building_large_stepped_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STEPPED_PYRAMID, building_large_stepped_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_stepped_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

class building_large_stepped_pyramid_corner : public building_large_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STEPPED_PYRAMID_CORNER, building_large_stepped_pyramid_corner, building_large_stepped_pyramid)
};

class building_large_stepped_pyramid_wall : public building_large_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_STEPPED_PYRAMID_WALL, building_large_stepped_pyramid_wall, building_large_stepped_pyramid)
};

// Complex = plain 20×20 (same footprint/pipeline as large) + causeway; temples later.
// Reuses LARGE_* part types (334–336) via JS corner/wall/cone/filler params.
// Own wrappers required: BUILDING_STATIC_DATA current_params() is keyed on TYPE.
class building_stepped_pyramid_complex : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_STEPPED_PYRAMID_COMPLEX, building_stepped_pyramid_complex, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_stepped_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

// Grand stepped — same on-land 20×20 as complex; separate TYPE for weight 44 + east-only causeway.
class building_grand_stepped_pyramid_complex : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, building_grand_stepped_pyramid_complex, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_grand_stepped_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

class building_small_bent_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_BENT_PYRAMID, building_small_bent_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_bent_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

class building_small_bent_pyramid_corner : public building_small_bent_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_BENT_PYRAMID_CORNER, building_small_bent_pyramid_corner, building_small_bent_pyramid)
};

class building_small_bent_pyramid_wall : public building_small_bent_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_BENT_PYRAMID_WALL, building_small_bent_pyramid_wall, building_small_bent_pyramid)
};

class building_medium_bent_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_BENT_PYRAMID, building_medium_bent_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_bent_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs);

class building_medium_bent_pyramid_corner : public building_medium_bent_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_BENT_PYRAMID_CORNER, building_medium_bent_pyramid_corner, building_medium_bent_pyramid)
};

class building_medium_bent_pyramid_wall : public building_medium_bent_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_BENT_PYRAMID_WALL, building_medium_bent_pyramid_wall, building_medium_bent_pyramid)
};

// True (smooth) small pyramid — PACK_PYRAMID + limestone casing + polish phases.
class building_small_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_PYRAMID, building_small_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool need_stonemason() override;
    // Top-down casing: phase 24 → layers ≥1; phase ≥25 / finished → all.
    virtual bool use_polish_sprites_for_layer(int layer) const override;
    static constexpr int k_polish_phase_begin = 24;
    // Stepped uses phase 24/30 to raise L3/L4 rings — those numbers are polish for true.
    virtual void on_phase_changed(int old, int current) override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_small_pyramid_corner : public building_small_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_PYRAMID_CORNER, building_small_pyramid_corner, building_small_pyramid)
};

class building_small_pyramid_wall : public building_small_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_PYRAMID_WALL, building_small_pyramid_wall, building_small_pyramid)
};

class building_small_pyramid_cone : public building_small_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_PYRAMID_CONE, building_small_pyramid_cone, building_small_pyramid)
};

// Mudbrick (brick-core) small pyramid — PACK_MUDBRICK_PYRAMID + bricks + limestone casing polish.
class building_small_mudbrick_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MUDBRICK_PYRAMID, building_small_mudbrick_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual bool use_polish_sprites_for_layer(int layer) const override;
    static constexpr int k_polish_phase_begin = 24;
    virtual void on_phase_changed(int old, int current) override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_mudbrick_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_small_mudbrick_pyramid_corner : public building_small_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MUDBRICK_PYRAMID_CORNER, building_small_mudbrick_pyramid_corner, building_small_mudbrick_pyramid)
};

class building_small_mudbrick_pyramid_wall : public building_small_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MUDBRICK_PYRAMID_WALL, building_small_mudbrick_pyramid_wall, building_small_mudbrick_pyramid)
};

class building_small_mudbrick_pyramid_cone : public building_small_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_SMALL_MUDBRICK_PYRAMID_CONE, building_small_mudbrick_pyramid_cone, building_small_mudbrick_pyramid)
};

// Mudbrick (brick-core) medium pyramid — 12×12, bricks + limestone polish after height 31.
class building_medium_mudbrick_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MUDBRICK_PYRAMID, building_medium_mudbrick_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    static constexpr int k_polish_phase_begin = 32;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool use_polish_sprites_for_layer(int layer) const override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_mudbrick_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_medium_mudbrick_pyramid_corner : public building_medium_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MUDBRICK_PYRAMID_CORNER, building_medium_mudbrick_pyramid_corner, building_medium_mudbrick_pyramid)
};

class building_medium_mudbrick_pyramid_wall : public building_medium_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MUDBRICK_PYRAMID_WALL, building_medium_mudbrick_pyramid_wall, building_medium_mudbrick_pyramid)
};

class building_medium_mudbrick_pyramid_cone : public building_medium_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_MUDBRICK_PYRAMID_CONE, building_medium_mudbrick_pyramid_cone, building_medium_mudbrick_pyramid)
};

// Mudbrick (brick-core) large pyramid — 16×16 (≠ true large 20×20), bricks + polish after height 35.
class building_large_mudbrick_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MUDBRICK_PYRAMID, building_large_mudbrick_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    // Height courses end at 35 (same band as true/stepped large); polish count = 16/4 = 4.
    static constexpr int k_polish_phase_begin = 36;
    static constexpr int k_polish_layers = 4;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool use_polish_sprites_for_layer(int layer) const override;
    virtual void on_phase_changed(int old, int current) override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_mudbrick_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_large_mudbrick_pyramid_corner : public building_large_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER, building_large_mudbrick_pyramid_corner, building_large_mudbrick_pyramid)
};

class building_large_mudbrick_pyramid_wall : public building_large_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MUDBRICK_PYRAMID_WALL, building_large_mudbrick_pyramid_wall, building_large_mudbrick_pyramid)
};

class building_large_mudbrick_pyramid_cone : public building_large_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_MUDBRICK_PYRAMID_CONE, building_large_mudbrick_pyramid_cone, building_large_mudbrick_pyramid)
};

// Mudbrick complex — on-land 20×20 + causeway (temples/entrance annex later).
// Reuses LARGE_MUDBRICK part types (353–355). Schedule = true-large band with bricks.
class building_mudbrick_pyramid_complex : public building_large_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MUDBRICK_PYRAMID_COMPLEX, building_mudbrick_pyramid_complex, building_large_mudbrick_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    // 20×20 → 5 polish layers (large mudbrick plain is 16×16 / 4).
    static constexpr int k_polish_layers = 5;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool use_polish_sprites_for_layer(int layer) const override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_mudbrick_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

// Grand mudbrick — same on-land 20×20 until annex; separate TYPE for weight 44.
class building_grand_mudbrick_pyramid_complex : public building_large_mudbrick_pyramid {
public:
    BUILDING_METAINFO(BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, building_grand_mudbrick_pyramid_complex, building_large_mudbrick_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    static constexpr int k_polish_layers = 5;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool use_polish_sprites_for_layer(int layer) const override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_grand_mudbrick_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_medium_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_PYRAMID, building_medium_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    // First polish phase index (height courses end at 31; polish count = 12/4).
    static constexpr int k_polish_phase_begin = 32;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool need_stonemason() override;
    virtual bool use_polish_sprites_for_layer(int layer) const override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_medium_pyramid_corner : public building_medium_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_PYRAMID_CORNER, building_medium_pyramid_corner, building_medium_pyramid)
};

class building_medium_pyramid_wall : public building_medium_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_PYRAMID_WALL, building_medium_pyramid_wall, building_medium_pyramid)
};

class building_medium_pyramid_cone : public building_medium_pyramid {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_PYRAMID_CONE, building_medium_pyramid_cone, building_medium_pyramid)
};

// True (smooth) large pyramid — 20×20, limestone + polish after height 35.
class building_large_pyramid : public building_stepped_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_PYRAMID, building_large_pyramid, building_stepped_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    // First polish phase (height courses end at 35; polish count = 20/4 = 5).
    static constexpr int k_polish_phase_begin = 36;
    static constexpr int k_polish_layers = 5;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }
    virtual bool need_stonemason() override;
    virtual bool use_polish_sprites_for_layer(int layer) const override;
    virtual void on_phase_changed(int old, int current) override;

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_pyramid::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

class building_large_pyramid_corner : public building_large_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_PYRAMID_CORNER, building_large_pyramid_corner, building_large_pyramid)
};

class building_large_pyramid_wall : public building_large_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_PYRAMID_WALL, building_large_pyramid_wall, building_large_pyramid)
};

class building_large_pyramid_cone : public building_large_pyramid {
public:
    BUILDING_METAINFO(BUILDING_LARGE_PYRAMID_CONE, building_large_pyramid_cone, building_large_pyramid)
};

class building_pyramid_complex : public building_large_pyramid {
public:
    BUILDING_METAINFO(BUILDING_PYRAMID_COMPLEX, building_pyramid_complex, building_large_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

// Grand = same on-land footprint until causeway; separate TYPE for monument weight 44.
class building_grand_pyramid_complex : public building_large_pyramid {
public:
    BUILDING_METAINFO(BUILDING_GRAND_PYRAMID_COMPLEX, building_grand_pyramid_complex, building_large_pyramid)

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual int building_image_get() const override;
    virtual const base_params &pyramid_params() const override { return current_params(); }

    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_grand_pyramid_complex::static_params,
    init_tiles, corner_type, wall_type, cone_type, filler_type, enter_offset, stairs, pyramide_type);

// OG complex annex (size_variant 3/4): mortuary temple → causeway → valley temple.
// Placeholder art until pak sprites are wired; placement is along the causeway strip.
class building_mortuary_temple : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_MORTUARY_TEMPLE, building_mortuary_temple, building_impl)
    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T
    virtual void on_place_update_tiles(int orientation, int variant) override;
};

class building_pyramid_causeway : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_CAUSEWAY, building_pyramid_causeway, building_impl)
    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T
    virtual void on_place_update_tiles(int orientation, int variant) override;
};

class building_valley_temple : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_VALLEY_TEMPLE, building_valley_temple, building_impl)
    using static_params = building_impl::static_params;
    BUILDING_STATIC_DATA_T
    virtual void on_place_update_tiles(int orientation, int variant) override;
};

bool building_type_is_pyramid_complex_annex(e_building_type t);

void map_pyramid_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain);
