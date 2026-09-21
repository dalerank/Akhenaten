#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"
#include "core/xstring.h"

struct obelisk_stage {
    xstring name;
    uint16_t timber = 0;
    svector<vec2i, 8> ladders;
    vec2i carpenter_point{};
    vec2i stonemasons_point{};
    bool carpenter_need = false;
    bool stonemasons_need = false;
};
ANK_CONFIG_STRUCT(obelisk_stage, timber, ladders, carpenter_point, stonemasons_point, carpenter_need, stonemasons_need)

// Shared base for small (3×3) and large (5×5) granite obelisks — single building, no parts.
class building_obelisk : public building_monument {
public:
    building_obelisk(building &b) : building_monument(b) {}
    virtual building_obelisk *dcast_obelisk() override { return this; }

    struct base_params {
        svector<monument_phase_resource, 4> placement_resources;
        uint8_t art_stages = 4;
        svector<obelisk_stage, 16> stages;
    };

    struct static_params : public base_params, public building_static_params {
        void load_stages(archive arch);
        void rebuild_construction(e_building_type type);
    };

    struct preview : building_planer_renderer {
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual bool need_stonemason() override;
    virtual bool need_carpenter() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual bool accepts_yard_delivery(e_resource resource) const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int art_stage() const; // 1-based stage index → anim letter a..
    xstring anim_key_for(int stage) const;
    int placement_amount(e_resource r) const;
    bool place_scaffold();
    const obelisk_stage *stage_at(int phase) const;
    const obelisk_stage *current_stage() const;
    vec2i carpenter_work_pixel() const;
    vec2i stonemasons_work_pixel() const;
    static int yards_available(e_resource r);
    static bool has_unfinished_obelisk();

private:
    void scrub_dead_workers();
    bool has_live_worker(e_figure_type type) const;
};

class building_small_obelisk : public building_obelisk {
public:
    BUILDING_METAINFO(BUILDING_SMALL_OBELISK, building_small_obelisk, building_obelisk)
    struct static_params : public building_obelisk::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_small_obelisk::static_params, placement_resources, art_stages)

class building_large_obelisk : public building_obelisk {
public:
    BUILDING_METAINFO(BUILDING_LARGE_OBELISK, building_large_obelisk, building_obelisk)
    struct static_params : public building_obelisk::static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;
    virtual const monument &config() const override;
};
ANK_CONFIG_STRUCT(building_large_obelisk::static_params, placement_resources, art_stages)
