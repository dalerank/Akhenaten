#pragma once

#include "core/vec2i.h"
#include "grid/point.h"

#define MAX_TILE_CACHES 3000
#define MAX_CACHED_FIGURES_PER_TILE 20

struct tile_figure_draw_cache {
    int grid_offset;
    struct {
        int id;
        vec2i pixel;
    } figures[MAX_CACHED_FIGURES_PER_TILE];
    int num_figures;
};

void reset_tiledraw_caches();
tile_figure_draw_cache* get_figure_cache_for_tile(map_point point);
void cache_figures(vec2i pixel, map_point point);
