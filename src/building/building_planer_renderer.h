#pragma once

#include "building_type.h"
#include "grid/point.h"
#include "building_fwd.h"

class build_planner;
struct painter;

struct building_planer_renderer {
    static const building_planer_renderer dummy;
    virtual bool ghost_allow_tile(build_planner &p, tile2i tile) const;
    virtual bool can_construction_start(build_planner &p, tile2i start) const { return true; }
    virtual int setup_orientation(int orientation) const { return orientation; }
    virtual void setup_build(build_planner &planer) const {}
    virtual void setup_preview_graphics(build_planner &planer) const;
    virtual int setup_building_variant(e_building_type type, tile2i tile, int variant) const { return variant; }
    virtual int next_building_variant(e_building_type type, tile2i tile, int variant) const { return (variant + 1) % 4; }
    virtual int update_relative_orientation(build_planner &p, tile2i tile, int global_orientation) const { return global_orientation; }
    virtual int update_building_variant(build_planner &p) const;
    virtual int construction_update(build_planner &p, tile2i start, tile2i end) const;
    virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const;
    virtual void ghost_preview(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel) const;
    virtual void ghost_blocked(build_planner &p, painter &ctx, tile2i tile, tile2i end, vec2i pixel, bool fully_blocked) const;
    virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const { return state; }
    virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const { return state; }
    virtual bool is_need_flag(build_planner &p, e_building_need_rules flag) const;

    static void register_model(e_building_type e, const building_planer_renderer &p);
    static const building_planer_renderer &get(e_building_type e);
};