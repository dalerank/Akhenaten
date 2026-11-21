#pragma once

#include "core/vec2i.h"
#include "grid/point.h"

class build_planner;
struct painter;

struct ghost_painter {
    virtual ~ghost_painter() = default;
    virtual void ghost_preview(build_planner& p, painter& ctx, tile2i tile, tile2i end, vec2i pixel) const = 0;
    virtual void ghost_blocked(build_planner& p, painter& ctx, tile2i tile, tile2i end, vec2i pixel,
      bool fully_blocked) const
      = 0;
};
