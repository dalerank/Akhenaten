#pragma once

#include "core/vec2i.h"
#include "grid/point.h"
#include "grid/grid.h"

#define MAX_TILE_CACHES 3000
#define MAX_CACHED_FIGURES_PER_TILE 20

struct painter;

struct tile_figure_draw_cache {
    int grid_offset;
    struct {
        int id;
        vec2i pixel;
    } figures[MAX_CACHED_FIGURES_PER_TILE];
    int num_figures;
};

struct figure_draw_cache_data_t {
    tile_figure_draw_cache tile_caches[MAX_TILE_CACHES];
    int num_cached_tiles;
    int num_cached_figures;
    int caches_fast_index_lookup[GRID_SIZE_TOTAL];
};

figure_draw_cache_data_t &figure_draw_cache();

void reset_tiledraw_caches(figure_draw_cache_data_t &cache);
tile_figure_draw_cache* get_figure_cache_for_tile(figure_draw_cache_data_t &cache, tile2i point);
void cache_figures(vec2i pixel, tile2i point, painter &ctx);
