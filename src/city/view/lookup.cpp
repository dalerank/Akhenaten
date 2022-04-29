#include <core/config.h>
#include <graphics/menu.h>
#include <core/calc.h>
#include "lookup.h"

// TODO: get rid of these!!!
static map_point SCREENTILE_TO_MAPPOINT_LOOKUP[500][500];

map_point screentile_to_mappoint(screen_tile screen) {
    return SCREENTILE_TO_MAPPOINT_LOOKUP[screen.x][screen.y];
//    if (grid_offset < 0)
//        SCREENTILE_TO_MAPPOINT_LOOKUP[screen.x][screen.y].set(0);
//
//    return grid_offset < 0 ? 0 : grid_offset;
}
screen_tile mappoint_to_screentile(map_point point) {
    calculate_lookup();
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++) {
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++) {
            if (screentile_to_mappoint({x, y}) == point)
                return {x, y};
        }
    }
}

///

static pixel_coordinate MAPPOINT_TO_PIXELCOORD_LOOKUP[GRID_SIZE_TOTAL];

pixel_coordinate mappoint_to_pixel(map_point point) {
//    calculate_lookup();
    return MAPPOINT_TO_PIXELCOORD_LOOKUP[point.grid_offset()];
}
void record_pixel_coord(map_point point, pixel_coordinate coord) {
    MAPPOINT_TO_PIXELCOORD_LOOKUP[point.grid_offset()] = {coord.x, coord.y};
}

///

screen_tile pixel_to_screentile(pixel_coordinate pixel) {
    if (config_get(CONFIG_UI_ZOOM))
        pixel.y -= TOP_MENU_HEIGHT[GAME_ENV];

    auto data = *city_view_data_unsafe();

    // adjust by zoom scale
    pixel.x = calc_adjust_with_percentage(pixel.x, data.scale);
    pixel.y = calc_adjust_with_percentage(pixel.y, data.scale);

    // check if within viewport
    if (pixel.x < data.viewport.x ||
        pixel.x >= data.viewport.x + data.viewport.width_pixels ||
        pixel.y < data.viewport.y ||
        pixel.y >= data.viewport.y + data.viewport.height_pixels) {
        return {-1, -1};
    }

    pixel.x += data.camera.pixel_offset_internal.x;
    pixel.y += data.camera.pixel_offset_internal.y;
    int odd = ((pixel.x - data.viewport.x) / HALF_TILE_WIDTH_PIXELS +
               (pixel.y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_is_odd = ((pixel.x - data.viewport.x) / HALF_TILE_WIDTH_PIXELS) & 1;
    int y_is_odd = ((pixel.y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_mod = ((pixel.x - data.viewport.x) % HALF_TILE_WIDTH_PIXELS) / 2;
    int y_mod = (pixel.y - data.viewport.y) % HALF_TILE_HEIGHT_PIXELS;
    int screen_x_offset = (pixel.x - data.viewport.x) / TILE_WIDTH_PIXELS;
    int y_view_offset = (pixel.y - data.viewport.y) / HALF_TILE_HEIGHT_PIXELS;
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
    screen_tile screen;
    screen.x = data.camera.tile_internal.x + screen_x_offset;
    screen.y = data.camera.tile_internal.y + y_view_offset;
    return screen;
}

static void reset_lookup(void) {
    for (int y = 0; y < MAP_TILE_UPPER_LIMIT_Y(); y++)
        for (int x = 0; x < MAP_TILE_UPPER_LIMIT_X(); x++)
            SCREENTILE_TO_MAPPOINT_LOOKUP[x][y].set(-1);
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
                SCREENTILE_TO_MAPPOINT_LOOKUP[screen_x / 2][screen_y].set(grid_offset);
            else // outside area
                SCREENTILE_TO_MAPPOINT_LOOKUP[screen_x / 2][screen_y].set(-1);
            screen_x += screen_x_step;
            screen_y += screen_y_step;
        }
        screen_x_start += screen_x_skip;
        screen_y_start += screen_y_skip;
    }
}