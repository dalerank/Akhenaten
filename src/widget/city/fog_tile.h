#pragma once

#include "city/city_fog_of_war.h"
#include "graphics/painter.h"
#include "grid/point.h"

struct fog_tile_scope {
    painter& ctx;
    const uint32_t saved_tint;
    e_fog_shade shade;

    fog_tile_scope(painter& c, tile2i tile) : ctx(c), saved_tint(c.tile_tint) {
        const auto& fog = city_fog_of_war();
        shade = fog.shade(tile);
        if (shade == fog_fogged) {
            ctx.tile_tint = fog.config.fogged_mask;
        } else if (shade == fog_visible) {
            const int edge = fog.edge(tile);
            if (edge > 0) {
                ctx.tile_tint = color_lerp(COLOR_MASK_NONE, fog.config.edge_mask, edge, fog.config.soft_edge_tiles);
            }
        }
    }
    ~fog_tile_scope() { ctx.tile_tint = saved_tint; }

    fog_tile_scope(const fog_tile_scope&) = delete;
    fog_tile_scope& operator=(const fog_tile_scope&) = delete;

    bool unexplored() const { return shade == fog_unexplored; }
    bool fogged() const { return shade == fog_fogged; }
};
