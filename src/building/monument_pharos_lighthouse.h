#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

class figure;

struct pharos_lighthouse_stage_def {
    uint8_t stage = 0;
    xstring hint;
    uint16_t stonemason = 0;
    uint16_t carpenter = 0;
    uint16_t text = 0;
};
ANK_CONFIG_STRUCT(pharos_lighthouse_stage_def, stage, hint, stonemason, carpenter, text)

class building_pharos_lighthouse : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_PHAROS_LIGHTHOUSE, building_pharos_lighthouse, building_monument)
    virtual building_pharos_lighthouse *dcast_pharos_lighthouse() override { return this; }

    enum {
        TOWER_SIZE = 6,
        STAGE_COMPLETE = 9,
        SLEDS_PER_BLOCK = 3,
        MATERIAL_PER_LOAD = 400,
        SPOT_MASON = 0,
        SPOT_CARPENTER = 1,
    };

    struct runtime_data_t : building_monument::runtime_data_t {
        std::array<uint16_t, 2> spot_work;
        uint16_t worker_fid;
        uint8_t sleds;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<pharos_lighthouse_stage_def, STAGE_COMPLETE> stages;
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct progress_info {
        int stage = 0;
        int percent = 0;
        int stonemasons = 0;
        int stonemasons_waiting = 0;
        int carpenters = 0;
        int material = 0;
        int material_total = 0;
    };

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner& planer) const override;
        virtual uint32_t ghost_ignore_terrain(build_planner &p, tile2i tile) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void collect_site(build_planner& p, tile2i end) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int construction_place(build_planner& p, tile2i tile, tile2i end, int orientation,
          int variant) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
        virtual void ghost_blocked(build_planner& planer, painter& ctx, tile2i start, tile2i end, vec2i pixel,
          bool fully_blocked) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual xstring demolish_blocked_message() const override;
    virtual void set_phase(int phase) override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_animation() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile,
      color color_mask) override;
    virtual bool need_stonemason() override;
    virtual bool need_carpenter() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    building_pharos_lighthouse* main_lighthouse();
    const building_pharos_lighthouse* main_lighthouse() const;
    bool is_land_part() const { return !is_main(); }

    int stage() const;
    void set_stage(int stage);
    int spot_work_left(e_figure_type type) const;
    bool has_free_spot(e_figure_type type) const;
    figure_id worker_figure_id() const;
    bool part_has_active_worker() const;
    figure_id mason_waiting_for_block() const;
    bool sled_arrived(figure& mason);
    bool work_tick(figure& f);
    int get_progress(progress_info* out) const;
    static const base_params& lighthouse_params();

    static tile2i land_part_tile(tile2i tower);
    static bool site_tile_free(tile2i tile, bool tower);
    static bool site_fits(tile2i tower);
    static bool has_unfinished_pharos_lighthouse();

private:
    int spot_index(e_figure_type type) const;
    void reset_spots();
    void advance_stage();
    void refresh_tower_tiles();
};
ANK_CONFIG_STRUCT(building_pharos_lighthouse::static_params, stages)
ANK_CONFIG_PROPERTY(building_pharos_lighthouse::runtime_data_t, variant)
