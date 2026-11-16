#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "building/monument_royal_tomb_data.h"
#include "core/vec2i.h"

#include <array>

class figure;

enum e_royal_tomb_stage : uint8_t {
    ROYAL_TOMB_STAGE_CLOSED = 0,
    ROYAL_TOMB_STAGE_STONEMASONS = 1,
    ROYAL_TOMB_STAGE_ARTISANS_LAST = 3,
    ROYAL_TOMB_STAGE_OPENS_NEIGHBOURS = 3,
    ROYAL_TOMB_STAGE_DONE = 4,
};

// Cleopatra royal tombs, ported from OG: a chain of one record per part (chambers first, then the
// closed rock, the cliff edge and the entrance). Chambers open one after another: stonemasons cut
// stage 1, tomb artisans do stages 2 and 3, and every worker sent costs the tomb 100 lamps that
// laborers sled in 400 at a time. The layout is fixed on the map; only the art turns with the view.
class building_royal_tomb : public building_monument {
public:
    using inherited = building_monument;

    building_royal_tomb(building &b) : building_monument(b) {}
    virtual building_royal_tomb *dcast_royal_tomb() override { return this; }

    static constexpr int STAGE_WORK_SLOTS = 3;
    static constexpr int LAMPS_PER_WORKER = 100;
    static constexpr int LAMP_REFILL_BELOW = 400;
    static constexpr int LAMP_STOCK_FULL = 400;
    static constexpr int MAP_EDGE_MARGIN = 3;

    struct runtime_data_t : building_monument::runtime_data_t {
        uint16_t part;
        uint8_t stage;
        uint8_t can_take_workers;
        std::array<uint16_t, STAGE_WORK_SLOTS> remaining_work;
        uint16_t worker_figure_id;
        uint8_t closed_variant;
        // Main part only: OG completed (all done and the mission goals reached: the tomb is sealed).
        uint8_t sealed;
        uint8_t completion_shown;
        // Not saved: set by a pre-v201 load, rebuilt in on_post_load.
        uint8_t legacy_layout;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        int art_pack = 0;
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

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void set_phase(int phase) override;
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

    const royal_tomb_layout& layout() const { return layout_of(type()); }
    const royal_tomb_part_init& part_init() const;
    int part_index() const { return runtime_data().part; }
    int stage() const { return runtime_data().stage; }
    bool is_chamber() const { return part_index() < layout().chambers; }
    building_royal_tomb* main_tomb();
    const building_royal_tomb* main_tomb() const;
    building_royal_tomb* part(int index);

    int lamp_stock() const { return main_tomb()->runtime_data().lamp_stock; }
    void add_lamp_stock(int amount);
    bool is_sealed() const { return main_tomb()->runtime_data().sealed != 0; }
    // OG royal_tomb_is_idle: no lamps on site and no chamber worker — the chambers go dark.
    bool is_idle() const;
    // A laborer may fetch lamps for this tomb (main only; the caller checks for a yard and a hauler).
    bool wants_lamps() const;

    bool part_has_active_worker() const;
    // OG royal_tomb_check_work_for_figure without the laborer branch.
    bool check_work_for_figure(e_figure_type type, figure_id fid, bool assign, building_royal_tomb* main = nullptr);
    // Returns true when the figure is done here and should go home.
    bool work_tick(figure& f);

    int progress_percent() const;
    struct progress_report {
        int percent = 0;
        int stonemasons = 0;
        int laborers = 0;
        int artisans = 0;
        int stock = 0;
    };
    progress_report get_progress() const;
    bool has_chamber_at(int first_stage, int last_stage) const;

    // Mark every chamber done and seal the tomb (a tomb carried over from an earlier mission).
    void set_completed();
    void seal_if_goals_reached();
    void refresh_part_images();

    static const royal_tomb_layout& layout_of(e_building_type type);
    static int size_index(e_building_type type);
    static bool is_royal_tomb_type(e_building_type type);
    static bool can_place_at(e_building_type type, tile2i origin);
    static bool part_tile_allowed(const royal_tomb_layout& l, int part, tile2i t);
    static bool has_unfinished_royal_tomb(e_building_type type);
    // Stonemasons / tomb artisans: the first royal tomb part that takes this figure (0 = none).
    static building_royal_tomb* find_work(e_figure_type type, figure_id fid, bool assign, int only_stage = -1);
    static bool goals_reached();
    static void seal_all_finished();

private:
    void init_part(int index);
    void place_parts();
    void update_part_image();
    int part_image(bool& per_tile) const;
    void advance_stage();
    int spot_table() const;
    tile2i entrance_access_tile() const;
    void convert_legacy_layout();
};
ANK_CONFIG_PROPERTY(building_royal_tomb::runtime_data_t, variant)

class building_small_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_SMALL_ROYAL_TOMB, building_small_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_royal_tomb::static_params, art_pack)

class building_medium_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_MEDIUM_ROYAL_TOMB, building_medium_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_medium_royal_tomb::static_params, art_pack)

class building_large_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_LARGE_ROYAL_TOMB, building_large_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_royal_tomb::static_params, art_pack)

class building_grand_royal_tomb : public building_royal_tomb {
public:
    BUILDING_METAINFO(BUILDING_GRAND_ROYAL_TOMB, building_grand_royal_tomb, building_royal_tomb)
    struct static_params : public building_royal_tomb::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_grand_royal_tomb::static_params, art_pack)
