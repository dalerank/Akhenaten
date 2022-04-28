#include <core/config.h>
#include <graphics/menu.h>
#include <core/calc.h>
#include "lookup.h"

static map_point view_tile_to_map_point_lookup[500][500];
static pixel_coordinate tile_xy_to_pixel_coord_lookup[500][500];

void cache_pixel_coord(int tile_x, int tile_y, pixel_coordinate coord) {
    tile_xy_to_pixel_coord_lookup[tile_x][tile_y] = pixel_coordinate {
            coord.x,
            coord.y
    };
}

static void reset_lookup(void) {
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++)
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++)
            view_tile_to_map_point_lookup[x][y].set(-1);
}
void calculate_lookup() {
    reset_lookup();
    int y_view_start;
    int y_view_skip;
    int y_view_step;
    int x_view_start;
    int x_view_skip;
    int x_view_step;
    switch (city_view_data_unsafe()->orientation) {
        default:
        case 0:
            x_view_start = MAP_TILE_UPPER_LIMIT_X() - 1;
            x_view_skip = -1;
            x_view_step = 1;
            y_view_start = 1;
            y_view_skip = 1;
            y_view_step = 1;
            break;
        case 2:
            x_view_start = 3;
            x_view_skip = 1;
            x_view_step = 1;
            y_view_start = MAP_TILE_UPPER_LIMIT_X() - 3;
            y_view_skip = 1;
            y_view_step = -1;
            break;
        case 4:
            x_view_start = MAP_TILE_UPPER_LIMIT_X() - 1;
            x_view_skip = 1;
            x_view_step = -1;
            y_view_start = MAP_TILE_UPPER_LIMIT_Y() - 2;
            y_view_skip = -1;
            y_view_step = -1;
            break;
        case 6:
            x_view_start = MAP_TILE_UPPER_LIMIT_Y();
            x_view_skip = -1;
            x_view_step = -1;
            y_view_start = MAP_TILE_UPPER_LIMIT_X() - 3;
            y_view_skip = -1;
            y_view_step = 1;
            break;
    }

    int min_x = SCROLLABLE_X_MIN_TILE();
    int max_x = SCROLLABLE_X_MAX_TILE();

    int min_y = SCROLLABLE_Y_MIN_TILE();
    int max_y = SCROLLABLE_Y_MAX_TILE();

    int grid_s;
    switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH:
            grid_s = GRID_LENGTH;
            break;
    }
    for (int y = 0; y < grid_s; y++) {
        int x_view = x_view_start;
        int y_view = y_view_start;
        for (int x = 0; x < grid_s; x++) {
            int grid_offset = x + grid_s * y;

            bool is_inside_area = map_tile_inside_map_area(x, y);
            if (is_inside_area) // inside area
                view_tile_to_map_point_lookup[x_view / 2][y_view].set(grid_offset);
            else // outside area
                view_tile_to_map_point_lookup[x_view / 2][y_view].set(-1);
            x_view += x_view_step;
            y_view += y_view_step;
        }
        x_view_start += x_view_skip;
        y_view_start += y_view_skip;
    }
}

pixel_coordinate city_view_grid_offset_to_pixel(int grid_offset) {
    return tile_xy_to_pixel_coord_lookup[map_grid_offset_to_x(grid_offset)][map_grid_offset_to_y(grid_offset)];
}
pixel_coordinate city_view_grid_offset_to_pixel(int tile_x, int tile_y) {
//    calculate_lookup();
    return tile_xy_to_pixel_coord_lookup[tile_x][tile_y];
}

int city_view_to_grid_offset(int x_view, int y_view) {
    return view_tile_to_map_point_lookup[x_view][y_view].grid_offset();
}
void city_view_grid_offset_to_xy_view(int grid_offset, int *x_view, int *y_view) {
    calculate_lookup();
    *x_view = *y_view = 0;
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++) {
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++) {
            if (city_view_to_grid_offset(x, y) == grid_offset) {
                *x_view = x;
                *y_view = y;
                return;
            }
        }
    }
}
int city_view_pixels_to_view_tile(int x, int y, view_tile *tile) {
    if (config_get(CONFIG_UI_ZOOM))
        y -= TOP_MENU_HEIGHT[GAME_ENV];

    auto data = *city_view_data_unsafe();

    // adjust by zoom scale
    x = calc_adjust_with_percentage(x, data.scale);
    y = calc_adjust_with_percentage(y, data.scale);

    // check if within viewport
    if (x < data.viewport.x ||
        x >= data.viewport.x + data.viewport.width_pixels ||
        y < data.viewport.y ||
        y >= data.viewport.y + data.viewport.height_pixels) {
        return 0;
    }

    x += data.camera.pixel_offset_internal.x;
    y += data.camera.pixel_offset_internal.y;
    int odd = ((x - data.viewport.x) / HALF_TILE_WIDTH_PIXELS +
               (y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_is_odd = ((x - data.viewport.x) / HALF_TILE_WIDTH_PIXELS) & 1;
    int y_is_odd = ((y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_mod = ((x - data.viewport.x) % HALF_TILE_WIDTH_PIXELS) / 2;
    int y_mod = (y - data.viewport.y) % HALF_TILE_HEIGHT_PIXELS;
    int x_view_offset = (x - data.viewport.x) / TILE_WIDTH_PIXELS;
    int y_view_offset = (y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS;
    if (odd) {
        if (x_mod + y_mod >= HALF_TILE_HEIGHT_PIXELS - 1) {
            y_view_offset++;
            if (x_is_odd && !y_is_odd)
                x_view_offset++;
        }
    } else {
        if (y_mod > x_mod)
            y_view_offset++;
        else if (x_is_odd && y_is_odd)
            x_view_offset++;
    }
    tile->x = data.camera.tile_internal.x + x_view_offset;
    tile->y = data.camera.tile_internal.y + y_view_offset;
    return 1;
}
int city_view_tile_to_grid_offset(const view_tile *tile) {
    int grid_offset = city_view_to_grid_offset(tile->x, tile->y);
    if (grid_offset < 0)
        view_tile_to_map_point_lookup[tile->x][tile->y].set(0);

    return grid_offset < 0 ? 0 : grid_offset;
}