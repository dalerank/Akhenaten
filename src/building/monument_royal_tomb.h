#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

// Valley royal burial tomb: cliff bulk + 1×1 clear-land entrance (Heaven chart).
// Class on BUILDING_*_ROYAL_TOMB (229+). Enums 272–275 unused for place (RT0.1 C).
class building_royal_tomb : public building_monument {
public:
    building_royal_tomb(building &b) : building_monument(b) {}
    virtual building_royal_tomb *dcast_royal_tomb() override { return this; }

    struct base_params {
        vec2i init_tiles = {11, 20}; // Heaven Small cliff bulk; orient swaps
        vec2i entrance_size = {1, 1}; // clear-land tab past far depth edge
        uint8_t art_stages = 9;
        // My Palace: 1–2 masons + 2 artisans typical. Caps until AG7c counts from dump.
        uint8_t max_masons = 1;
        uint8_t max_artisans = 2;
        // Help 478: 400 lamps before work. Later loads burn from stock (≤700), not phase pct.
        // Clay/paint: My Palace 1 guild-load/phase from Stairway on — provisional 100 (=guild trip).
        svector<uint16_t, 16> lamp_loads{400, 0, 0, 0, 0, 0, 0, 0, 0};
        svector<uint16_t, 16> clay_loads{0, 100, 100, 100, 100, 100, 100, 100, 100};
        svector<uint16_t, 16> paint_loads{0, 100, 100, 100, 100, 100, 100, 100, 100};
    };

    struct static_params : public base_params, public building_static_params {
        void rebuild_construction(e_building_type type);
    };

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual uint32_t ghost_ignore_terrain(build_planner &p, tile2i tile) const override;
        virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };

    static constexpr int k_lamp_stock_max = 700;

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void on_destroy() override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool deliver_resource(e_resource resource, int amount) override;
    virtual bool need_stonemason() override;
    virtual bool need_artisan() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int art_stage() const;
    xstring anim_key_for(int stage) const;
    vec2i bulk_size() const;
    vec2i total_size() const;
    vec2i footprint_size() const { return total_size(); }
    const base_params &tomb_params() const;

    int lamp_stock() const { return runtime_data().lamp_stock; }
    int lamp_stock_room() const;
    int accept_lamp_stock(int amount);

    static bool is_bulk_local(int dx, int dy, vec2i bulk);
    static bool is_entrance_local(int dx, int dy, vec2i bulk, vec2i entrance);
    static bool is_padding_local(int dx, int dy, vec2i bulk, vec2i entrance);
    static bool has_unfinished_royal_tomb(e_building_type type);
    static const base_params &params_for(e_building_type type);
};

class building_small_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_SMALL_ROYAL_TOMB, building_small_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_royal_tomb::static_params, init_tiles, entrance_size, art_stages, max_masons, max_artisans, lamp_loads, clay_loads, paint_loads)

class building_medium_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_ROYAL_TOMB, building_medium_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_royal_tomb::static_params, init_tiles, entrance_size, art_stages, max_masons, max_artisans, lamp_loads, clay_loads, paint_loads)

class building_large_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_LARGE_ROYAL_TOMB, building_large_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_royal_tomb::static_params, init_tiles, entrance_size, art_stages, max_masons, max_artisans, lamp_loads, clay_loads, paint_loads)

class building_grand_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_GRAND_ROYAL_TOMB, building_grand_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_grand_royal_tomb::static_params, init_tiles, entrance_size, art_stages, max_masons, max_artisans, lamp_loads, clay_loads, paint_loads)
