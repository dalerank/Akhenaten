#ifndef OZYMANDIAS_FIGURES_CACHED_DRAW_H
#define OZYMANDIAS_FIGURES_CACHED_DRAW_H

#include "core/struct_types.h"
#include "grid/point.h"

#define MAX_TILE_CACHES 3000
#define MAX_CACHED_FIGURES_PER_TILE 20

typedef struct {
    int grid_offset;
    struct {
        int id;
        pixel_coordinate pixel;
    } figures[MAX_CACHED_FIGURES_PER_TILE];
    int num_figures;
} tile_figure_draw_cache;

void reset_tiledraw_caches();
tile_figure_draw_cache *get_figure_cache_for_tile(map_point point);
void cache_figures(pixel_coordinate pixel, map_point point);

#endif //OZYMANDIAS_FIGURES_CACHED_DRAW_H
