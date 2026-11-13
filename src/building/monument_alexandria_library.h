#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"
#include "figure/figure.h"

#include <array>
#include <unordered_map>

// Alexandria's Library (OG): 25 chained parts. Laborers prep every part (stage 1→2),
// then shared main stages 3→21 advance via 27 mason/carpenter work spots with marble/copper sleds.

enum library_stage : int {
    LIBRARY_STAGE_STARTED = 1,
    LIBRARY_STAGE_PREPARED = 2,
    LIBRARY_STAGE_BUILDING = 3,
    LIBRARY_STAGE_COPPER_FIRST = 16,
    LIBRARY_STAGE_COPPER_END = 20,
    LIBRARY_STAGE_COMPLETE = 21,
};

enum library_limits : int {
    LIBRARY_PARTS = 25,
    LIBRARY_WORK_SPOTS = 24, // active spots with work > 0 (stages 3..20)
    LIBRARY_IMAGE_STEPS = 126,
    LIBRARY_LABORER_WORK_TICKS = 100,
    LIBRARY_MATERIAL_LOADS = 36,
    LIBRARY_FRAME_COUNT = 2,
    LIBRARY_MATERIAL_PER_LOAD = 400,
    LIBRARY_WORK_TILE_DX = 3,
    LIBRARY_WORK_TILE_DY = 11,
    LIBRARY_SPOT_DESTINATION_OFFSET = 15,
    LIBRARY_SPOT_WORK_UNSET = 0xffff,
};

enum library_progress_out {
    LIBRARY_PROGRESS_STATUS = 0,
    LIBRARY_PROGRESS_PERCENT = 1,
    LIBRARY_PROGRESS_STONEMASONS = 2,
    LIBRARY_PROGRESS_STONEMASONS_WAITING = 3,
    LIBRARY_PROGRESS_LABORERS = 4,
    LIBRARY_PROGRESS_CARPENTERS = 5,
    LIBRARY_PROGRESS_MATERIAL = 6,
    LIBRARY_PROGRESS_MATERIAL_TOTAL = 7,
    LIBRARY_PROGRESS_SLOTS = 8,
};

struct library_part_desc {
    xstring hint;
    vec2i offset;
    uint8_t size = 1;
    uint8_t kind = 0;
};
ANK_CONFIG_STRUCT(library_part_desc, hint, offset, size, kind)

struct library_spot_def {
    uint8_t stage = 0;
    e_figure_type figure = FIGURE_NONE;
    uint16_t work = 0;
    xstring script;
};
ANK_CONFIG_STRUCT(library_spot_def, stage, figure, work, script)

struct library_image_step {
    uint8_t kind = 0;
    uint8_t until = 0;
    xstring north;
    xstring south;
    uint8_t north_odd = 0;
    uint8_t south_odd = 0;
    xstring north_script;
    xstring south_script;
};
ANK_CONFIG_STRUCT(library_image_step, kind, until, north, south, north_odd, south_odd, north_script, south_script)

struct library_worker_image {
    xstring key;
    int pack = 0;
    int id = 0;
    uint8_t offset = 0;
    uint8_t frames = 1;
    uint8_t step = 1;
};
ANK_CONFIG_STRUCT(library_worker_image, pack, id, offset, frames, step)

struct library_anim_sequence {
    svector<vec2i, 4> from_views;
    svector<vec2i, 4> to_views;
    xstring anim;
    int16_t frames = 0;
    svector<vec2i, 4> next;
    svector<int16_t, 4> add;
};
ANK_CONFIG_STRUCT(library_anim_sequence, from_views, to_views, anim, frames, next, add)

struct library_anim_script {
    xstring key;
    svector<vec2i, 4> entry;
    svector<library_anim_sequence, 40> sequences;
};
ANK_CONFIG_STRUCT(library_anim_script, entry, sequences)

class building_alexandria_library : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_ALEXANDRIA_LIBRARY, building_alexandria_library, building_monument)
    virtual building_alexandria_library *dcast_alexandria_library() override { return this; }

    struct runtime_data_t : building_monument::runtime_data_t {
        uint8_t material_frame = 0;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<library_part_desc, LIBRARY_PARTS> parts;
        svector<library_spot_def, LIBRARY_WORK_SPOTS> spots;
        svector<library_image_step, LIBRARY_IMAGE_STEPS> image_steps;
        std::unordered_map<xstring, library_worker_image> worker_images;
        vec2i anim_offset;
        std::unordered_map<xstring, library_anim_script> anim_scripts;
        xstring leveled;
        xstring unbuilt;
        xstring preview;
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
    virtual void on_place_checks() override;
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
    int part_kind() const;
    int part_stage() const;
    building_alexandria_library *main_library();
    const building_alexandria_library *main_library() const;
    building_alexandria_library *part(int index);
    const building_alexandria_library *part(int index) const;

    bool work_tick(figure &f);
    bool has_free_spot(e_figure_type type) const;
    bool check_work_for_figure(figure_id fid, bool assign);
    static int find_work_for_figure(figure_id fid);

    int spot_attached(int spot) const;
    int spot_work_left(int spot) const;
    int get_progress(int *out /*nullable*/) const;
    void refresh_part_images();
    void reset_spots();
    void on_material_delivered();
    void animate_spots();

    static int parts_count();
    static const library_part_desc &part_desc(int index);
    static bool has_unfinished_alexandria_library();
    static e_resource material_for_stage(int stage);

private:
    int find_free_spot(e_figure_type type) const;
    void set_spot(int spot, uint16_t work, uint16_t fid);
    void scrub_spots();
    void advance_all_parts();
    bool all_parts_prepared() const;
    bool part_has_active_worker() const;
    void clear_worker_figure();
    figure_id worker_figure_id() const;
    void set_worker_figure(figure_id fid);
    void send_to_part(figure &f) const;
    tile2i work_tile() const;
    void update_part_image();
    int resolve_image(bool *is_front) const;
    void finish_all();
    static bool area_for_part_free(tile2i origin, const library_part_desc &desc);
    static vec2i box_extent();
};

ANK_CONFIG_STRUCT(building_alexandria_library::static_params, parts, spots, image_steps, worker_images, anim_offset,
  anim_scripts, leveled, unbuilt, preview)
ANK_CONFIG_PROPERTY(building_alexandria_library::runtime_data_t, variant)
