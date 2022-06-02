#include "figures_cached_draw.h"
#include "figure/figure.h"
#include "grid/figure.h"

struct {
    tile_figure_draw_cache tile_caches[MAX_TILE_CACHES];
    int num_cached_tiles;
    int num_cached_figures;
    int caches_fast_index_lookup[GRID_SIZE_TOTAL];
} FIGURE_DRAW_CACHE;
void reset_tiledraw_caches() {
    FIGURE_DRAW_CACHE.num_cached_tiles = 0;
    FIGURE_DRAW_CACHE.num_cached_figures = 0;
    memset((void*)&FIGURE_DRAW_CACHE.caches_fast_index_lookup, 0, GRID_SIZE_TOTAL * sizeof(int));
    for (int p = 0; p < MAX_TILE_CACHES; ++p) {
        FIGURE_DRAW_CACHE.tile_caches[p].num_figures = 0;
        FIGURE_DRAW_CACHE.tile_caches[p].grid_offset = -1;
    }
}
tile_figure_draw_cache *get_figure_cache_for_tile(map_point point) {
    int fast_index = FIGURE_DRAW_CACHE.caches_fast_index_lookup[point.grid_offset()];
    if (fast_index == 0)
        return nullptr; // no cache in memory for the chosen tile.
    return &FIGURE_DRAW_CACHE.tile_caches[fast_index];
}
#define TILE_WIDTH_PIXELS 60
#define TILE_HEIGHT_PIXELS 30
static void record_figure_over_tile(figure *f, pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int figure_id = f->id;
    tile_figure_draw_cache *cache = get_figure_cache_for_tile(point);
    if (cache != 0) { // found an existing cache!
        if (cache->num_figures >= MAX_CACHED_FIGURES_PER_TILE)
            return; // cache is FULL!
        // add figure to the existing point's cache.
        int i = cache->num_figures++;
        cache->figures[i].id = figure_id;
        cache->figures[i].pixel = pixel;
        FIGURE_DRAW_CACHE.num_cached_figures++;
        return;
    }
    // no cache found -- make a new one.
    if (FIGURE_DRAW_CACHE.num_cached_tiles >= MAX_TILE_CACHES)
        return; // can not cache any more tiles.
    int p = FIGURE_DRAW_CACHE.num_cached_tiles++;
    FIGURE_DRAW_CACHE.caches_fast_index_lookup[grid_offset] = p;
    cache = &FIGURE_DRAW_CACHE.tile_caches[p];
    cache->grid_offset = grid_offset;

    // add figure to cache (figure id + the original rendering coords)
    int i = cache->num_figures++;
    cache->figures[i].id = figure_id;
    cache->figures[i].pixel = pixel;
    FIGURE_DRAW_CACHE.num_cached_figures++;
}
static void cache_figure(figure *f, pixel_coordinate pixel) {
    map_point point = f->tile;
    switch (f->direction) {
        case 0:
        case 4:
            // Y-axis aligned
            record_figure_over_tile(f, pixel, f->tile.shifted(0, 1));
            record_figure_over_tile(f, pixel, f->tile.shifted(0, -1));
            break;
        case 1:
        case 5:
            // horizontal movement
            record_figure_over_tile(f, pixel, f->tile.shifted(-1, 1));
            record_figure_over_tile(f, pixel, f->tile.shifted(1, -1));
            break;
        case 2:
        case 6:
            // X-axis aligned
            record_figure_over_tile(f, pixel, f->tile.shifted(1, 0));
            record_figure_over_tile(f, pixel, f->tile.shifted(-1, 0));
            break;
        case 3:
        case 7:
            record_figure_over_tile(f, pixel, f->tile.shifted(1, 1));
            record_figure_over_tile(f, pixel, f->tile.shifted(-1, -1));
            // vertical movement
            break;
    }
    record_figure_over_tile(f, pixel, f->previous_tile);
}
void cache_figures(pixel_coordinate pixel, map_point point) {
    int figure_id = map_figure_at(point.grid_offset());
    while (figure_id) {
        figure *f = figure_get(figure_id);
        if (!f->is_ghost || f->height_adjusted_ticks)
            cache_figure(f, pixel);
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}