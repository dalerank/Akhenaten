#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"

// Abu Simbel: linked square parts (mastaba/sphinx style).
// Rot0 / Heaven 9×21 — façade along +Y, entrance toward +X:
//   far  X0: cliffL | statueL | midcut_back | statueR | cliffR
//   mid  X3: cliffL_near | … | midcut_depth | … | cliffR_near
//   near X6: midcut_front (clear land)
class building_abu_simbel : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_ABU_SIMBEL, building_abu_simbel, building_monument)
    virtual building_abu_simbel *dcast_abu_simbel() override { return this; }

    enum part_variant : uint8_t {
        PART_CLIFF_L_FAR = 0,
        PART_CLIFF_L_NEAR = 1,
        PART_STATUE_L = 2,
        PART_MIDCUT_BACK = 3,
        PART_MIDCUT_DEPTH = 4,
        PART_MIDCUT_FRONT = 5,
        PART_STATUE_R = 6,
        PART_CLIFF_R_FAR = 7,
        PART_CLIFF_R_NEAR = 8,
        PART_COUNT = 9,
    };

    struct base_params {
        vec2i init_tiles = {9, 21};
        uint8_t art_stages = 10;
        // AS0.6: no OG counts found (Heaven W=Y; SG3/exe lack load tables). Mason phases = 0.
        svector<uint16_t, 10> timber_loads{400, 400, 400, 200, 200, 0, 0, 0, 0, 0};
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
        void rebuild_construction();
    } BUILDING_STATIC_DATA_T;

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
    virtual xstring demolish_blocked_message() const override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual bool suppress_ornaments_in_flat_view() const override { return true; }
    virtual bool need_stonemason() override;
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
    int art_orient_pair() const;
    void refresh_part_tiles();
    int part_size() const;
    bool part_needs_cliff() const;
    vec2i footprint_size() const;

    static bool has_abu_simbel_on_map();

    bool need_carpenter_phase() const;
    bool has_stonemason_worker() const;
    bool has_carpenter_worker() const;
};
ANK_CONFIG_STRUCT(building_abu_simbel::static_params, init_tiles, art_stages, timber_loads)
