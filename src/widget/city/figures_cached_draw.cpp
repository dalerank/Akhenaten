#include "figures_cached_draw.h"
#include "figure/figure.h"
#include "grid/figure.h"
#include "grid/property.h"

figure_draw_cache_data_t g_figure_draw_cache;

figure_draw_cache_data_t &figure_draw_cache() {
    return g_figure_draw_cache;
}

void reset_tiledraw_caches(figure_draw_cache_data_t &figure_cache) {
    figure_cache.num_cached_tiles = 0;
    figure_cache.num_cached_figures = 0;
    memset((void*)&figure_cache.caches_fast_index_lookup, -1, GRID_SIZE_TOTAL * sizeof(int));
    for (int p = 0; p < MAX_TILE_CACHES; ++p) {
        figure_cache.tile_caches[p].num_figures = 0;
        figure_cache.tile_caches[p].grid_offset = -1;
    }
}

tile_figure_draw_cache* get_figure_cache_for_tile(figure_draw_cache_data_t &figure_cache, tile2i point) {
    int fast_index = figure_cache.caches_fast_index_lookup[point.grid_offset()];
    if (fast_index == -1)
        return nullptr; // no cache in memory for the chosen tile.

    return &figure_cache.tile_caches[fast_index];
}

static map_point tile_get_northtile(map_point point) {
    int size = map_property_multi_tile_size(point.grid_offset());
    for (int i = 0; i < size && map_property_multi_tile_x(point.grid_offset()); i++)
        point.shift(-1, 0);
    for (int i = 0; i < size && map_property_multi_tile_y(point.grid_offset()); i++)
        point.shift(0, -1);
    return point;
}

static map_point tile_get_drawtile(map_point point) {
    point = tile_get_northtile(point);
    int size = map_property_multi_tile_size(point.grid_offset());
    if (size > 1) {
        size -= 1;
        switch (city_view_orientation()) {
        case 0:
            point.shift(0, size);
            break;
            //            case 2:
            //                // no change needed
            //                break;
        case 4:
            point.shift(size, 0);
            break;
        case 6:
            point.shift(size, size);
            break;
        }
    }
    return point;
}

static void record_figure_over_tile(figure_draw_cache_data_t &figure_cache, figure* f, vec2i pixel, map_point point) {
    //    point = tile_get_drawtile(point);
    int grid_offset = point.grid_offset();
    int figure_id = f->id;
    tile_figure_draw_cache* cache = get_figure_cache_for_tile(figure_draw_cache(), point);
    if (cache != nullptr) { // found an existing cache!
        if (cache->num_figures >= MAX_CACHED_FIGURES_PER_TILE)
            return; // cache is FULL!
        // add figure to the existing point's cache.
        int i = cache->num_figures++;
        cache->figures[i].id = figure_id;
        cache->figures[i].pixel = pixel;
        figure_cache.num_cached_figures++;
        return;
    }
    // no cache found -- make a new one.
    if (figure_cache.num_cached_tiles >= MAX_TILE_CACHES) {
        return; // can not cache any more tiles.
    }
    int p = figure_cache.num_cached_tiles++;
    figure_cache.caches_fast_index_lookup[grid_offset] = p;
    cache = &figure_cache.tile_caches[p];
    cache->grid_offset = grid_offset;

    // add figure to cache (figure id + the original rendering coords)
    int i = cache->num_figures++;
    cache->figures[i].id = figure_id;
    cache->figures[i].pixel = pixel;
    figure_cache.num_cached_figures++;
}
static void cache_figure(figure_draw_cache_data_t &figure_cache, figure* f, vec2i pixel) {
    map_point point = f->tile;
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(0, -1));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(1, -1));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(1, 0));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(1, 1));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(0, 1));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(-1, 1));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(-1, 0));
    record_figure_over_tile(figure_cache, f, pixel, point.shifted(-1, -1));
    //    bool entering_tile = (f->progress_on_tile < 8);
    //    switch (f->direction) {
    //        // Y-axis aligned
    //        case 0:
    //        case 4:
    //            if ((f->direction == 0) == entering_tile)
    //                record_figure_over_tile(f, pixel, point.shifted(0, 1));
    //            else
    //                record_figure_over_tile(f, pixel, point.shifted(0, -1));
    //            break;
    //            // horizontal movement
    //        case 1:
    //            if (entering_tile) {
    //                record_figure_over_tile(f, pixel, point.shifted(-1, 0));
    //                record_figure_over_tile(f, pixel, point.shifted(0, 1));
    //            }
    //        case 5:
    //            if (entering_tile) {
    //                record_figure_over_tile(f, pixel, point.shifted(0, -1));
    //                record_figure_over_tile(f, pixel, point.shifted(1, 0));
    //            }
    //            break;
    //            // X-axis aligned
    //        case 2:
    //        case 6:
    //            if ((f->direction == 2) == entering_tile)
    //                record_figure_over_tile(f, pixel, point.shifted(-1, 0));
    //            else
    //                record_figure_over_tile(f, pixel, point.shifted(1, 0));
    //            break;
    //            // vertical movement
    //        case 3:
    //            if (entering_tile) {
    //                record_figure_over_tile(f, pixel, point.shifted(-1, 0));
    //                record_figure_over_tile(f, pixel, point.shifted(0, -1));
    //            }
    //            break;
    //        case 7:
    //            if (entering_tile) {
    //                record_figure_over_tile(f, pixel, point.shifted(1, 0));
    //                record_figure_over_tile(f, pixel, point.shifted(0, 1));
    //            }
    //            break;
    //    }
    //    record_figure_over_tile(f, pixel, f->previous_tile);
}

void cache_figures(vec2i pixel, tile2i point, view_context &ctx) {
    int figure_id = map_figure_id_get(point.grid_offset());

    while (figure_id) {
        figure* f = figure_get(figure_id);
        if (!f->is_ghost || f->height_adjusted_ticks) {
            cache_figure(*ctx.figure_cache, f, pixel);
        } if (figure_id != f->next_figure) {
            figure_id = f->next_figure;
        } else {
            figure_id = 0;
        }
    }
}