#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

class figure;

struct caesareum_spot_def {
    uint8_t stage = 0;
    e_figure_type figure = FIGURE_NONE;
    uint16_t work = 0;
};
ANK_CONFIG_STRUCT(caesareum_spot_def, stage, figure, work)

struct caesareum_progress {
    int stage = 0;
    int percent = 0;
    int stonemasons = 0;
    int stonemasons_waiting = 0;
    int laborers = 0;
    int carpenters = 0;
    int material = 0;
};

// OG caesareum: nine 5x5 records chained main -> 8 parts in a 15x15 square around the clicked tile.
// The stage (0..18, then finished) lives in the phase of every record; the main record holds the single
// worker slot (workers[0]) and the sled count, each record keeps the work state of 3 of the 27 spots.
class building_caesareum : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_CAESAREUM, building_caesareum, building_monument)
    virtual building_caesareum *dcast_caesareum() override { return this; }

    static constexpr int PARTS = 9;
    static constexpr int PART_SIZE = 5;
    static constexpr int SITE_SIZE = 15;
    static constexpr int SITE_HALF = 7;
    static constexpr int SPOTS_PER_PART = 3;
    static constexpr int STAGE_GRANITE = 18;
    static constexpr int STAGE_COMPLETE = 19;
    static constexpr int SLEDS_PER_STAGE = 2;
    static constexpr int MATERIAL_LOADS = 38;
    static constexpr int MATERIAL_PER_LOAD = 400;

    struct runtime_data_t : building_monument::runtime_data_t {
        std::array<uint16_t, SPOTS_PER_PART> spot_work;
        std::array<uint16_t, SPOTS_PER_PART> spot_figure;
        uint8_t sleds;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<caesareum_spot_def, 32> spots;
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_place(build_planner &planer, tile2i start, tile2i end, int orientation,
          int variant) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end,
          vec2i pixel) const override;
        virtual void ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel,
          bool fully_blocked) const override;
        virtual bool ghost_allow_tile(build_planner &planer, tile2i tile) const override;
        virtual uint32_t ghost_ignore_terrain(build_planner &planer, tile2i tile) const override;
        virtual int can_place(build_planner &planer, tile2i start, tile2i end, int state) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
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

    // 0..18 while built, 19 when complete.
    int stage() const;
    int part_index() const { return runtime_data().variant; }
    building_caesareum *main_caesareum();
    const building_caesareum *main_caesareum() const;
    building_caesareum *part(int index);
    const building_caesareum *part(int index) const;

    figure_id worker_figure_id() const;
    bool part_has_active_worker() const;
    bool has_free_spot(e_figure_type type) const;
    // OG caesareum_check_work_for_figure with assign: takes the single worker slot.
    bool claim_worker(figure &f);
    // Returns true when the figure is done here and should go home.
    bool work_tick(figure &f);
    // A laborer's sled arrived for the waiting mason; true when it was the last one he needs.
    bool sled_arrived();
    e_resource block_resource() const;
    int get_progress(caesareum_progress *out) const;
    int spot_attached(int spot) const;
    int spot_work_left(int spot) const;
    void set_stage(int stage);

    static int view_part(int part, int view);

private:
    void create_parts(bool undo);
    int find_free_spot(e_figure_type type) const;
    void set_spot(int spot, uint16_t work, uint16_t fid);
    void reset_spots();
    void advance_stage();
    void refresh_part_images();
};
ANK_CONFIG_STRUCT(building_caesareum::static_params, spots)
ANK_CONFIG_PROPERTY(building_caesareum::runtime_data_t, variant)
