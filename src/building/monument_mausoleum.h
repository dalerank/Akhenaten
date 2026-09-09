#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

// Mausoleum: 8×22 clear land; 240 sandstone to place; WC clear → story1 → timber ramp → story2.
// Visual skins 0/1/2 in runtime_data().variant (enum MAUSOLEUM_0/1/2); menu type = BUILDING_MAUSOLEUM.
class building_mausoleum : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_MAUSOLEUM, building_mausoleum, building_monument)
    virtual building_mausoleum *dcast_mausoleum() override { return this; }

    struct base_params {
        svector<monument_phase_resource, 4> placement_resources;
        uint8_t art_stages = 3;
        svector<uint16_t, 8> timber_loads;
        svector<uint16_t, 8> sandstone_loads;
        vec2i init_tiles = {8, 22};
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
        void rebuild_construction();
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual void on_destroy() override;
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
    xstring anim_key_for(int stage, int orient_idx) const;
    vec2i footprint_size() const;
    int placement_amount(e_resource r) const;
    static int yards_available(e_resource r);
    static bool has_unfinished_mausoleum();
};
ANK_CONFIG_STRUCT(building_mausoleum::static_params,
    placement_resources, art_stages, timber_loads, sandstone_loads, init_tiles)
