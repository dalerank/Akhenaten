#pragma once

#include "building/building_fwd.h"
#include "building/building_type.h"
#include "grid/point.h"

class build_planner;

struct placement_rules {
    virtual ~placement_rules() = default;
    virtual bool ghost_allow_tile(build_planner& p, tile2i tile) const = 0;
    virtual uint32_t ghost_ignore_terrain(build_planner& p, tile2i tile) const = 0;
    virtual bool can_construction_start(build_planner& p, tile2i start) const = 0;
    virtual int setup_orientation(int orientation) const = 0;
    virtual void setup_build(build_planner& planer) const = 0;
    virtual void setup_preview_graphics(build_planner& planer) const = 0;
    virtual int setup_building_variant(e_building_type type, tile2i tile, int variant) const = 0;
    virtual int next_building_variant(e_building_type type, tile2i tile, int variant) const = 0;
    virtual int update_relative_orientation(build_planner& p, tile2i tile, int global_orientation) const = 0;
    virtual int update_building_variant(build_planner& p) const = 0;
    virtual int construction_update(build_planner& p, tile2i start, tile2i end) const = 0;
    virtual int construction_place(build_planner& p, tile2i tile, tile2i end, int orientation, int variant) const = 0;
    virtual int can_place(build_planner& p, tile2i tile, tile2i end, int state) const = 0;
    virtual int finalize_check(build_planner& p, tile2i tile, tile2i end, int state) const = 0;
    virtual bool is_need_flag(build_planner& p, e_building_need_rules flag) const = 0;
    virtual void collect_site(build_planner& p, tile2i end) const = 0;
    virtual int finalize_cost(build_planner& p, int cost) const = 0;
};
