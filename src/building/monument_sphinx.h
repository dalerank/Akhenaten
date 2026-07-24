#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/vec2i.h"

class building_sphinx : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_SPHINX, building_sphinx, building_monument)
    virtual building_sphinx *dcast_sphinx() override { return this; }

    struct base_params {
        vec2i init_tiles; // full footprint, e.g. {6, 18}
        // Part b/c tile offsets from main for placement rotation 0..3
        svector<vec2i, 4> part_b_offset;
        svector<vec2i, 4> part_c_offset;
    };

    struct static_params : public base_params, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual bool need_stonemason() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int art_stage() const;
    xstring anim_key_for(int stage, int part, int orient_idx) const;
};
ANK_CONFIG_STRUCT(building_sphinx::static_params, init_tiles, part_b_offset, part_c_offset)
