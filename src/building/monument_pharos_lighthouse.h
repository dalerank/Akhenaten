#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

// Pharos Lighthouse: 6×6 rocky ground; WC clear → marble tiers + timber scaffold → finish.
// METAINFO on BUILDING_PHAROS_LIGHTHOUSE (228); _0 (267) is dead enum slot.
class building_pharos_lighthouse : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_PHAROS_LIGHTHOUSE, building_pharos_lighthouse, building_monument)
    virtual building_pharos_lighthouse *dcast_pharos_lighthouse() override { return this; }

    struct base_params {
        vec2i init_tiles = {6, 6};
        uint8_t art_stages = 9;
        // Heaven marble ~108; timber provisional (PL0.2).
        svector<uint16_t, 8> timber_loads{100, 200, 200};
        svector<uint16_t, 8> marble_loads{22, 22, 22, 21, 21};
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
        void rebuild_construction();
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        // Rock is TERRAIN_NOT_CLEAR — ignore so tiles_blocked_total stays 0 on valid pads.
        virtual uint32_t ghost_ignore_terrain(build_planner &p, tile2i tile) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual xstring demolish_blocked_message() const override;
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

    int art_stage() const;
    xstring anim_key_for(int stage) const;
    vec2i footprint_size() const;
    static bool has_unfinished_pharos_lighthouse();
};
ANK_CONFIG_STRUCT(building_pharos_lighthouse::static_params,
    init_tiles, art_stages, timber_loads, marble_loads)
