#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/tokenum.h"
#include "core/vec2i.h"
#include "figure/figure.h"

#include <array>
#include <unordered_map>

// sun temple: 100 chained parts from the part-desc table. TEMPLE (main, size 5)
// advances through 13 carpenter/stonemason work spots; other kinds are leveled
// and built by laborers (and sandstone sleds for masons).

enum e_sun_temple_part_kind : uint8_t {
    SUN_TEMPLE_PART_TEMPLE = 0,
    SUN_TEMPLE_PART_FORECOURT = 1,
    SUN_TEMPLE_PART_ENCLOSURE_CORNER_SW = 2,
    SUN_TEMPLE_PART_ENCLOSURE_CORNER_SE = 3,
    SUN_TEMPLE_PART_ENCLOSURE_CORNER_NE = 4,
    SUN_TEMPLE_PART_ENCLOSURE_CORNER_NW = 5,
    SUN_TEMPLE_PART_ENCLOSURE_SIDE = 6,
    SUN_TEMPLE_PART_ENCLOSURE_EDGE = 7,
    SUN_TEMPLE_PART_COURTYARD = 8,
    SUN_TEMPLE_PART_PATH = 9,
    SUN_TEMPLE_PART_COURTYARD_PILLAR = 10,
    SUN_TEMPLE_PART_COURTYARD_COLUMN = 11,
    SUN_TEMPLE_PART_HALL = 12,
    SUN_TEMPLE_PART_KIND_MAX
};
using e_sun_temple_part_kind_tokens_t = token_holder<e_sun_temple_part_kind, SUN_TEMPLE_PART_TEMPLE, SUN_TEMPLE_PART_KIND_MAX>;

struct sun_temple_part_desc {
    xstring name;
    vec2i offset;
    uint8_t size = 1;
    e_sun_temple_part_kind kind = SUN_TEMPLE_PART_TEMPLE;
};
ANK_CONFIG_STRUCT(sun_temple_part_desc, name, offset, size, kind)

struct sun_temple_spot_def {
    uint8_t stage = 0;
    e_figure_type figure = FIGURE_NONE;
    uint16_t work = 0;
    xstring script;
};
ANK_CONFIG_STRUCT(sun_temple_spot_def, stage, figure, work, script)

struct sun_temple_worker_image {
    xstring key;
    int pack = 0;
    int id = 0;
    uint8_t offset = 0;
    uint8_t frames = 1;
    uint8_t step = 1;
};
ANK_CONFIG_STRUCT(sun_temple_worker_image, pack, id, offset, frames, step)

struct sun_temple_anim_sequence {
    vec2i from;
    vec2i to;
    xstring anim;
    int16_t frames = 0;
    svector<vec2i, 4> next; // 4 view slots [N,E,S,W]; x=-1 = none
    svector<vec2i, 4> back;
    bool stop = false;
};
ANK_CONFIG_STRUCT(sun_temple_anim_sequence, from, to, anim, frames, next, back, stop)

struct sun_temple_anim_script {
    xstring key;
    bool unmirrored = false;
    svector<vec2i, 4> entry;
    svector<sun_temple_anim_sequence, 40> sequences;
};
ANK_CONFIG_STRUCT(sun_temple_anim_script, unmirrored, entry, sequences)

enum sun_temple_work_flag : uint8_t {
    SUN_TEMPLE_TEMPLE_DONE = 1,
    SUN_TEMPLE_COURTYARD_STARTED = 2,
    SUN_TEMPLE_FORECOURT_DONE = 4,
    SUN_TEMPLE_ENCLOSURE_DONE = 8,
    SUN_TEMPLE_COURTYARD_DONE = 16,
    SUN_TEMPLE_HALL_DONE = 32,
};

enum sun_temple_stage : uint8_t {
    SUN_TEMPLE_PART_STARTED = 1,
    SUN_TEMPLE_PART_DONE = 2,
    SUN_TEMPLE_LAST_PART_DONE = 4,
    SUN_TEMPLE_STAGE_COMPLETE = 13,
    SUN_TEMPLE_LABORER_WORK_TICKS = 50,
};

enum sun_temple_limits : int {
    SUN_TEMPLE_PARTS_MAX = 100,
    SUN_TEMPLE_WORK_SPOTS = 13,
    SUN_TEMPLE_SPOT_WORK_UNSET = 0xffff,
};

enum sun_temple_progress_out {
    SUN_TEMPLE_PROGRESS_STATUS = 0,
    SUN_TEMPLE_PROGRESS_AT_STAGE_0 = 1,
    SUN_TEMPLE_PROGRESS_TEMPLE_LEFT = 2,
    SUN_TEMPLE_PROGRESS_FORECOURT_LEFT = 3,
    SUN_TEMPLE_PROGRESS_ENCLOSURE_LEFT = 4,
    SUN_TEMPLE_PROGRESS_COURTYARD_LEFT = 5,
    SUN_TEMPLE_PROGRESS_HALL_LEFT = 6,
    SUN_TEMPLE_PROGRESS_STONEMASONS = 7,
    SUN_TEMPLE_PROGRESS_STONEMASONS_WAITING = 8,
    SUN_TEMPLE_PROGRESS_LABORERS = 9,
    SUN_TEMPLE_PROGRESS_CARPENTERS = 10,
    SUN_TEMPLE_PROGRESS_MATERIAL = 11,
    SUN_TEMPLE_PROGRESS_PERCENT = 12,
    SUN_TEMPLE_PROGRESS_MATERIAL_TOTAL = 13,
    SUN_TEMPLE_PROGRESS_SLOTS = 14,
};

class building_sun_temple : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_SUN_TEMPLE, building_sun_temple, building_monument)
    virtual building_sun_temple *dcast_sun_temple() override { return this; }

    struct runtime_data_t : building_monument::runtime_data_t {
        // Work spots: sun_temple_spots helper (runtime_data too small); flags here.
        uint8_t work_flags = 0;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<monument_phase_resource, 4> placement_resources;
        svector<sun_temple_spot_def, SUN_TEMPLE_WORK_SPOTS> spots;
        svector<sun_temple_part_desc, SUN_TEMPLE_PARTS_MAX> parts;
        // Main body: key prefixes (sa/sb/sc) + stage thresholds between packs (OG: 9, 13).
        svector<xstring, 4> temple_images;
        svector<uint8_t, 4> temple_image_stages;
        // EXTRA pack keys in OG MAUSOLEUM_GROUND offset order (0..12).
        svector<xstring, 16> extra_images;
        xstring leveled; // stage-1 leveled ground
        xstring unbuilt; // plaza outline before leveling (OG walkway)
        std::unordered_map<xstring, sun_temple_worker_image> worker_images;
        vec2i anim_offset;
        std::unordered_map<xstring, sun_temple_anim_script> anim_scripts;
        uint16_t work_units = 213;
        uint16_t material_total = 38000;
        uint16_t material_per_load = 100;
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
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

    int part_index() const { return runtime_data().variant; }
    e_sun_temple_part_kind part_kind() const;
    int part_stage() const;
    uint8_t work_flags() const;
    building_sun_temple *main_sun_temple();
    const building_sun_temple *main_sun_temple() const;
    building_sun_temple *part(int index);
    const building_sun_temple *part(int index) const;

    // Returns true when the figure is done here and should leave.
    bool work_tick(figure &f);
    bool has_free_spot(e_figure_type type) const;
    bool check_work_for_figure(figure_id fid, bool assign);
    static int find_work_for_figure(figure_id fid);

    int spot_attached(int spot) const;
    int spot_work_left(int spot) const;

    int get_progress(int *out /*nullable, SUN_TEMPLE_PROGRESS_SLOTS*/) const;
    void refresh_part_images();
    void reset_spots();

    int placement_amount(e_resource r) const;
    static int yards_available(e_resource r);
    static bool has_completed_sun_temple();
    static int parts_count();
    static const sun_temple_part_desc &part_desc(int index);

private:
    int find_free_spot(e_figure_type type) const;
    void set_spot(int spot, uint16_t work, uint16_t fid);
    void scrub_spots();
    void advance_main_stage();
    void apply_part_flags_after_work();
    bool part_has_active_worker() const;
    void clear_worker_figure();
    figure_id worker_figure_id() const;
    void set_worker_figure(figure_id fid);
    void send_to_part(figure &f) const;
    int assign_laborer(figure_id fid, bool assign);
    int assign_material(figure_id fid, bool assign, e_terrain_usage terrain);
    void update_part_image();
    void animate_spots();
    static bool area_for_part_free(tile2i origin, const sun_temple_part_desc &desc);

    static int map_view();
    static int art_orient_idx();
    static int camera_view();
    static int temple_image_band(const base_params &params, int stage);
    static int extra_img(const static_params &params, int offset);
    static int img_or_fallback(const static_params &params, xstring key);
    static int finished_extra_offset(e_sun_temple_part_kind kind, int view);
};

ANK_CONFIG_STRUCT(building_sun_temple::static_params, placement_resources, spots, parts, temple_images,
  temple_image_stages, extra_images, leveled, unbuilt, worker_images, anim_offset, anim_scripts, work_units,
  material_total, material_per_load)
ANK_CONFIG_PROPERTY(building_sun_temple::runtime_data_t, variant)
