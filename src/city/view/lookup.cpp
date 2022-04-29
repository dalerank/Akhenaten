#include <core/config.h>
#include <graphics/menu.h>
#include <core/calc.h>
#include "lookup.h"

static map_point screen_to_map_point_lookup[500][500];
static pixel_coordinate mappoint_to_pixel_coord_lookup[500][500];

void cache_pixel_coord(map_point tile, pixel_coordinate coord) {
    mappoint_to_pixel_coord_lookup[tile.x()][tile.y()] = {coord.x, coord.y};
}

static void reset_lookup(void) {
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++)
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++)
            screen_to_map_point_lookup[x][y].set(-1);
}
void calculate_lookup() {
    reset_lookup();
    int screen_y_start;
    int screen_y_skip;
    int screen_y_step;
    int screen_x_start;
    int screen_x_skip;
    int screen_x_step;
    switch (city_view_data_unsafe()->orientation) {
        default:
        case 0:
            screen_x_start = MAP_TILE_UPPER_LIMIT_X() - 1;
            screen_x_skip = -1;
            screen_x_step = 1;
            screen_y_start = 1;
            screen_y_skip = 1;
            screen_y_step = 1;
            break;
        case 2:
            screen_x_start = 3;
            screen_x_skip = 1;
            screen_x_step = 1;
            screen_y_start = MAP_TILE_UPPER_LIMIT_X() - 3;
            screen_y_skip = 1;
            screen_y_step = -1;
            break;
        case 4:
            screen_x_start = MAP_TILE_UPPER_LIMIT_X() - 1;
            screen_x_skip = 1;
            screen_x_step = -1;
            screen_y_start = MAP_TILE_UPPER_LIMIT_Y() - 2;
            screen_y_skip = -1;
            screen_y_step = -1;
            break;
        case 6:
            screen_x_start = MAP_TILE_UPPER_LIMIT_Y();
            screen_x_skip = -1;
            screen_x_step = -1;
            screen_y_start = MAP_TILE_UPPER_LIMIT_X() - 3;
            screen_y_skip = -1;
            screen_y_step = 1;
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
        int screen_x = screen_x_start;
        int screen_y = screen_y_start;
        for (int x = 0; x < grid_s; x++) {
            int grid_offset = x + grid_s * y;

            bool is_inside_area = map_tile_inside_map_area(x, y);
            if (is_inside_area) // inside area
                screen_to_map_point_lookup[screen_x / 2][screen_y].set(grid_offset);
            else // outside area
                screen_to_map_point_lookup[screen_x / 2][screen_y].set(-1);
            screen_x += screen_x_step;
            screen_y += screen_y_step;
        }
        screen_x_start += screen_x_skip;
        screen_y_start += screen_y_skip;
    }
}

pixel_coordinate city_view_grid_offset_to_pixel(int grid_offset) {
    return mappoint_to_pixel_coord_lookup[map_grid_offset_to_x(grid_offset)][map_grid_offset_to_y(grid_offset)];
}
pixel_coordinate city_view_grid_offset_to_pixel(int tile_x, int tile_y) {
//    calculate_lookup();
    return mappoint_to_pixel_coord_lookup[tile_x][tile_y];
}

int screentile_to_pixel(int screen_x, int screen_y) {
    return screen_to_map_point_lookup[screen_x][screen_y].grid_offset();
}
int pixel_to_screentile(int x, int y, screen_tile *screen) {
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
    int screen_x_offset = (x - data.viewport.x) / TILE_WIDTH_PIXELS;
    int y_view_offset = (y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS;
    if (odd) {
        if (x_mod + y_mod >= HALF_TILE_HEIGHT_PIXELS - 1) {
            y_view_offset++;
            if (x_is_odd && !y_is_odd)
                screen_x_offset++;
        }
    } else {
        if (y_mod > x_mod)
            y_view_offset++;
        else if (x_is_odd && y_is_odd)
            screen_x_offset++;
    }
    screen->x = data.camera.tile_internal.x + screen_x_offset;
    screen->y = data.camera.tile_internal.y + y_view_offset;
    return 1;
}

screen_tile mappoint_to_viewtile(map_point point) {
    calculate_lookup();
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++) {
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++) {
            if (screentile_to_pixel(x, y) == point.grid_offset())
                return {x, y};
        }
    }
}
int viewtile_to_mappoint(const screen_tile *tile) {
    int grid_offset = screentile_to_pixel(tile->x, tile->y);
    if (grid_offset < 0)
        screen_to_map_point_lookup[tile->x][tile->y].set(0);

    return grid_offset < 0 ? 0 : grid_offset;
}