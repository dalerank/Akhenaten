#include "enemy_strength.h"

#include "figure/figure.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "city/city_figures.h"
#include "figuretype/figure_enemy.h"

grid_xx g_enemy_strength = {0, FS_UINT8};

void map_enemy_strength_clear() {
    map_grid_clear(g_enemy_strength);
}

void map_enemy_strength_add(tile2i tile, int radius, int amount) {
    if (radius == 0) {
        // Add strength only to the specific tile
        int grid_offset = tile.grid_offset();
        int v = map_grid_get(g_enemy_strength, grid_offset);
        map_grid_set(g_enemy_strength, grid_offset, v + amount);
        if (map_has_figure_at(grid_offset)) {
            int fid = map_figure_id_get(grid_offset);
            figure *f = figure_get(fid);
            if (::smart_cast<figure_enemy>(f)) {
                map_grid_set(g_enemy_strength, grid_offset, v + amount + 2);
            }
        }
        return;
    }

    // Add strength in radius (for backward compatibility)
    grid_area area = map_grid_get_area(tile, 1, radius);

    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
        int grid_offset = t.grid_offset();
        int v = map_grid_get(g_enemy_strength, grid_offset);
        map_grid_set(g_enemy_strength, grid_offset, v + amount);
        if (map_has_figure_at(grid_offset)) {
            int fid = map_figure_id_get(grid_offset);
            figure *f = figure_get(fid);
            if (::smart_cast<figure_enemy>(f)) {
                map_grid_set(g_enemy_strength, grid_offset, v + amount + 2);
            }
        }
    });
}

int map_enemy_strength_get(int grid_offset) {
    return map_grid_get(g_enemy_strength, grid_offset);
}

max_enemy_strength_tile map_enemy_strength_get_max(tile2i tile, int radius) {
    grid_area area = map_grid_get_area(tile, 1, radius);

    int max_value = 0;
    tile2i max_tile(0, 0);
    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        if (map_routing_distance(grid_offset) > 0 && map_grid_get(g_enemy_strength, grid_offset) > max_value) {
            max_value = map_grid_get(g_enemy_strength, grid_offset);
            max_tile = tile;
        }
    });

    if (max_value > 0) {
        return { max_value, max_tile };
    }

    return { 0, tile2i::invalid };
}

