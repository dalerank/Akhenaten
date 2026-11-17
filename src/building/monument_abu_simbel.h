#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

class figure;

// Rows of the part_kinds, parts and stages tables in abu_simbel.js.
struct abu_simbel_view_art {
    xstring image;
    uint8_t offset = 0;
    bool two_per_art_stage = false;
};
ANK_CONFIG_STRUCT(abu_simbel_view_art, image, offset, two_per_art_stage)

struct abu_simbel_part_kind {
    int kind = 0;
    xstring name;
    xstring hint;
    uint8_t size = 0;
    bool on_rock = false;
    xstring family;
    uint8_t rotate = 0;
    svector<abu_simbel_view_art, 4> views;
};
ANK_CONFIG_STRUCT(abu_simbel_part_kind, kind, name, hint, size, on_rock, family, rotate, views)

struct abu_simbel_part_cfg {
    xstring id;
    int dx = 0;
    int dy = 0;
    xstring kind;
};
ANK_CONFIG_STRUCT(abu_simbel_part_cfg, id, dx, dy, kind)

struct abu_simbel_scaffold_cfg {
    int scaffold = 0;
    xstring name;
    xstring image;
    vec2i view0;
    vec2i view3;
};
ANK_CONFIG_STRUCT(abu_simbel_scaffold_cfg, scaffold, name, image, view0, view3)

struct abu_simbel_stage_cfg {
    int stage = 0;
    xstring hint;
    xstring scaffold;
    xstring art;
    uint16_t work = 0;
};
ANK_CONFIG_STRUCT(abu_simbel_stage_cfg, stage, hint, scaffold, art, work)

// Sixteen records cut into the cliff, fixed in map space (no rotation). The main record is part 0;
// its phase holds the stage (0..55, then finished) and the work left at the current stage's spot.
class building_abu_simbel : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_ABU_SIMBEL, building_abu_simbel, building_monument)
    virtual building_abu_simbel *dcast_abu_simbel() override { return this; }

    enum {
        PARTS = 16,
        STAGE_COMPLETE = 56,
        PART_KINDS = 12,
        SCAFFOLDS = 12,
    };

    struct runtime_data_t : building_monument::runtime_data_t {
        uint16_t spot_work;
        uint16_t spot_figure;
    } BUILDING_RUNTIME_DATA_T;

    struct static_params : public building_static_params {
        svector<abu_simbel_part_kind, PART_KINDS> part_kinds;
        svector<abu_simbel_scaffold_cfg, SCAFFOLDS> scaffolds;
        svector<abu_simbel_part_cfg, PARTS> parts;
        svector<abu_simbel_stage_cfg, STAGE_COMPLETE> stages;
        vec2i work_tile;
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual uint32_t ghost_ignore_terrain(build_planner &p, tile2i tile) const override;
        virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const override;
        virtual int can_place(build_planner& p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
        virtual void ghost_blocked(build_planner& planer, painter& ctx, tile2i start, tile2i end, vec2i pixel,
          bool fully_blocked) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual xstring demolish_blocked_message() const override;
    virtual bool continues_cliff() const override { return true; }
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool need_stonemason() override;
    virtual bool need_carpenter() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual tile2i access_tile() const override { return access_point(); }
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    // 0..56; 56 = complete.
    int stage() const;
    int progress_percent() const;
    int part_index() const { return runtime_data().variant; }
    const abu_simbel_part_kind* part_kind() const;
    building_abu_simbel* main_abu_simbel();
    const building_abu_simbel* main_abu_simbel() const;

    // Returns true when the figure is done here and should go home.
    bool work_tick(figure& f);
    virtual bool has_free_spot(e_figure_type type) const override;
    bool has_active_worker() const;
    int spot_work_left() const { return main_abu_simbel()->runtime_data().spot_work; }
    void set_stage(int stage);
    int scaffolds_raised() const;
    int scaffold_draw_count() const;

    // OG abu_simbel_can_place: every part tile away from the map edge, rock parts on monument rock.
    static bool site_fits(tile2i origin);

private:
    bool spot_free() const;
    void advance_stage();
    void refresh_part_images();
};
ANK_CONFIG_STRUCT(building_abu_simbel::static_params, part_kinds, scaffolds, parts, stages, work_tile)
ANK_CONFIG_PROPERTY(building_abu_simbel::runtime_data_t, variant)
