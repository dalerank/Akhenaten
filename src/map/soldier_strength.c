#include "soldier_strength.h"

#include "figure/figure.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/routing.h"

static grid_xx strength = {0, {FS_UINT8, FS_UINT8}};

void map_soldier_strength_clear(void)
{
    map_grid_clear(&strength);
}
void map_soldier_strength_add(int x, int y, int radius, int amount)
{
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, 1, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            int grid_offset = map_grid_offset(xx, yy);
            int v = map_grid_get(&strength, grid_offset);
            map_grid_set(&strength, grid_offset, v + amount);
            if (map_has_figure_at(grid_offset)) {
                if (figure_is_legion(figure_get(map_figure_at(grid_offset)))) {
                    map_grid_set(&strength, grid_offset, v + amount + 2);
                }
            }
        }
    }
}

int map_soldier_strength_get(int grid_offset)
{
    return map_grid_get(&strength, grid_offset);
}
int map_soldier_strength_get_max(int x, int y, int radius, int *out_x, int *out_y)
{
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, 1, radius, &x_min, &y_min, &x_max, &y_max);

    int max_value = 0;
    int max_tile_x = 0, max_tile_y = 0;
    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            int grid_offset = map_grid_offset(xx, yy);
            if (map_routing_distance(grid_offset) > 0 && map_grid_get(&strength, grid_offset) > max_value) {
                max_value = map_grid_get(&strength, grid_offset);
                max_tile_x = xx;
                max_tile_y = yy;
            }
        }
    }
    if (max_value > 0) {
        *out_x = max_tile_x;
        *out_y = max_tile_y;
        return 1;
    }
    return 0;
}
