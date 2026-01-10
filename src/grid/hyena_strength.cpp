#include "hyena_strength.h"

#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_type.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "city/city_figures.h"
#include "figuretype/figure_hyena.h"

grid_xx g_hyena_strength = {0, FS_UINT8};

void map_hyena_strength_clear() {
    map_grid_clear(g_hyena_strength);
}

void map_hyena_strength_add(tile2i tile, int radius, int amount) {
    if (radius == 0) {
        // Add strength only to the specific tile
        int grid_offset = tile.grid_offset();
        int v = map_grid_get(g_hyena_strength, grid_offset);
        map_grid_set(g_hyena_strength, grid_offset, v + amount);
        if (map_has_figure_at(grid_offset)) {
            int fid = map_figure_id_get(grid_offset);
            figure *f = figure_get(fid);
            if (::smart_cast<figure_hyena>(f)) {
                map_grid_set(g_hyena_strength, grid_offset, v + amount + 2);
            }
        }
        return;
    }

    // Add strength in radius (for backward compatibility)
    grid_area area = map_grid_get_area(tile, 1, radius);

    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
        int grid_offset = t.grid_offset();
        int v = map_grid_get(g_hyena_strength, grid_offset);
        map_grid_set(g_hyena_strength, grid_offset, v + amount);
        if (map_has_figure_at(grid_offset)) {
            int fid = map_figure_id_get(grid_offset);
            figure *f = figure_get(fid);
            if (::smart_cast<figure_hyena>(f)) {
                map_grid_set(g_hyena_strength, grid_offset, v + amount + 2);
            }
        }
    });
}

int map_hyena_strength_get(int grid_offset) {
    return map_grid_get(g_hyena_strength, grid_offset);
}

max_hyena_strength_tile map_hyena_strength_get_max(tile2i tile, int radius) {
    grid_area area = map_grid_get_area(tile, 1, radius);

    int max_value = 0;
    tile2i max_tile(0, 0);
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        if (map_routing_distance(grid_offset) > 0 && map_grid_get(g_hyena_strength, grid_offset) > max_value) {
            max_value = map_grid_get(g_hyena_strength, grid_offset);
            max_tile = tile;
        }
    });

    if (max_value > 0) {
        return { max_value, max_tile };
    }

    return { 0, tile2i::invalid };
}

void map_hyena_strength_update() {
    map_hyena_strength_clear();
    
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && m->is_herd && m->max_figures > 0 && m->figure_type == FIGURE_HYENA) {
            int figures_num = 0;
            for (int fig = 0; fig < formation::max_figures_count; fig++) {
                if (m->figures[fig] > 0) {
                    figure *f = figure_get(m->figures[fig]);
                    figures_num++;
                    uint8_t radiuses[] = { 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2 };
                    if (f && f->state == FIGURE_STATE_ALIVE && f->type == FIGURE_HYENA) {
                        map_hyena_strength_add(f->tile, radiuses[figures_num], 1);
                    }
                }
            }
        }
    }
}
