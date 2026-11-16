#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

#include <unordered_map>

class figure;

struct sphinx_spot_def {
    uint8_t stage = 0;
    e_figure_type figure = FIGURE_NONE;
    uint16_t work = 0;
    xstring script;
};
ANK_CONFIG_STRUCT(sphinx_spot_def, stage, figure, work, script)

struct sphinx_worker_image {
    xstring key; // set by the config map reader
    int pack = 0;
    int id = 0;
    uint8_t offset = 0;
    uint8_t frames = 1;
    uint8_t step = 1;
};
ANK_CONFIG_STRUCT(sphinx_worker_image, pack, id, offset, frames, step)

// Choices are {x: sequence, y: 1 = play reversed}.
struct sphinx_anim_sequence {
    vec2i from; // view N
    vec2i to;
    xstring anim;
    int16_t frames = 0;
    svector<vec2i, 4> next; // empty = the following sequence (wraps to 0)
    svector<vec2i, 4> back; // empty = stop
    bool stop = false;
};
ANK_CONFIG_STRUCT(sphinx_anim_sequence, from, to, anim, frames, next, back, stop)

struct sphinx_anim_script {
    xstring key;             // set by the config map reader
    bool unmirrored = false; // OG gives E/W the same x as N/S
    svector<vec2i, 4> entry; // empty = sequence 0
    svector<sphinx_anim_sequence, 24> sequences;
};
ANK_CONFIG_STRUCT(sphinx_anim_script, unmirrored, entry, sequences)

// Three 6x6 records chained main -> b -> c along map +x. The stage lives in the main record's phase
// (1..15, then finished); each record keeps the work state of its own 8 spots.
class building_sphinx : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_SPHINX, building_sphinx, building_monument)
    virtual building_sphinx* dcast_sphinx() override { return this; }

    static constexpr int PARTS = 3;
    static constexpr int PART_SIZE = 6;
    static constexpr int SPOTS_PER_PART = 8;
    static constexpr int STAGE_FIRST = 1;
    static constexpr int STAGE_COMPLETE = 16;
    // Enhanced: artisans paint the carved sphinx before it counts as finished.
    static constexpr int STAGE_PAINTING = 16;

    struct runtime_data_t : building_monument::runtime_data_t {
        std::array<uint16_t, SPOTS_PER_PART> spot_work;
        std::array<uint16_t, SPOTS_PER_PART> spot_figure;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<sphinx_spot_def, 24> spots;
        std::unordered_map<xstring, sphinx_worker_image> worker_images;
        vec2i anim_offset;
        std::unordered_map<xstring, sphinx_anim_script> anim_scripts;
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner& planer) const override;
        virtual void ghost_preview(build_planner& planer, painter& ctx, tile2i start, tile2i end,
          vec2i pixel) const override;
        virtual void ghost_blocked(build_planner& planer, painter& ctx, tile2i start, tile2i end, vec2i pixel,
          bool fully_blocked) const override;
        virtual bool ghost_allow_tile(build_planner& planer, tile2i tile) const override;
        virtual uint32_t ghost_ignore_terrain(build_planner& planer, tile2i tile) const override;
        virtual int can_place(build_planner& planer, tile2i start, tile2i end, int state) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile,
      color color_mask) override;
    virtual bool need_stonemason() override;
    virtual bool need_carpenter() override;
    virtual bool need_artisan() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual const monument& config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer* iob, size_t version) override;

    // 1..16; 16 = all carving done (finished, or awaiting Enhanced painting).
    int stage() const;
    int part_index() const { return runtime_data().variant; }
    building_sphinx* main_sphinx();
    const building_sphinx* main_sphinx() const;
    building_sphinx* part(int index);
    const building_sphinx* part(int index) const;

    // Returns true when the figure is done here and should go home.
    bool work_tick(figure& f);
    bool has_free_spot(e_figure_type type) const;
    int spot_attached(int spot) const;
    int spot_work_left(int spot) const;
    void reset_spots();
    // Spots of earlier stages are done, the rest start over.
    void set_stage(int stage);
    void work_percentages(int& carpenter_pct, int& mason_pct) const;
    bool is_carving_done() const { return stage() >= STAGE_COMPLETE; }

    static int pack_stage(int part_letter, int stage);
    static int view_part_letter(int part, int view);

private:
    int find_free_spot(e_figure_type type) const;
    void set_spot(int spot, uint16_t work, uint16_t fid);
    void scrub_spots();
    void advance_stage();
    void refresh_part_images();
    void animate_spots();
};
ANK_CONFIG_STRUCT(building_sphinx::static_params, spots, worker_images, anim_offset, anim_scripts)
ANK_CONFIG_PROPERTY(building_sphinx::runtime_data_t, variant)
