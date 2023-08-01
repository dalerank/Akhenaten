#include "lookup.h"
#include "core/calc.h"
#include "graphics/elements/menu.h"
#include "graphics/image.h"
#include "grid/grid.h"

static map_point SCREENTILE_TO_MAPPOINT_LOOKUP[4][500][500];
static void screentile_calc_params_by_orientation(int city_orientation, pixel_coordinate* start,
                                                  pixel_coordinate* column_step, pixel_coordinate* row_step) {
    switch (city_orientation) {
    default:
    case 0:
        *start = {GRID_LENGTH + 2, 1};
        *column_step = {1, 1};
        *row_step = {-1, 1};
        break;
    case 1:
        *start = {3, GRID_LENGTH};
        *column_step = {1, -1};
        *row_step = {1, 1};
        break;
    case 2:
        *start = {GRID_LENGTH + 2, (2 * GRID_LENGTH) - 1};
        *column_step = {-1, -1};
        *row_step = {1, -1};
        break;
    case 3:
        *start = {(2 * GRID_LENGTH) + 1, GRID_LENGTH};
        *column_step = {-1, 1};
        *row_step = {-1, -1};
        break;
    }
}
static void fill_in_lookup_table_for_orientation(int city_orientation) {
    pixel_coordinate start;
    pixel_coordinate column_step;
    pixel_coordinate row_step;
    screentile_calc_params_by_orientation(city_orientation, &start, &column_step, &row_step);

    for (int y = 0; y < GRID_LENGTH; y++) {
        screen_tile screen = start;
        for (int x = 0; x < GRID_LENGTH; x++) {
            int grid_offset = x + GRID_LENGTH * y;

            bool is_inside_area = map_grid_inside_map_area(grid_offset);
            if (is_inside_area) // inside area
                SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x / 2][screen.y].set(grid_offset);
            else // outside area
                SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x / 2][screen.y].set(-1);
            screen += column_step;
        }
        start += row_step;
    }
}
void calculate_screentile_lookup_tables() {
    // reset lookup tables
    for (int o = 0; o < 4; ++o)
        for (int y = 0; y < (2 * GRID_LENGTH) + 1; y++)
            for (int x = 0; x < GRID_LENGTH + 3; x++)
                SCREENTILE_TO_MAPPOINT_LOOKUP[o][x][y].set(-1);
    // fill in tables
    for (int orientation = 0; orientation < 4; ++orientation)
        fill_in_lookup_table_for_orientation(orientation);
}
map_point screentile_to_mappoint(screen_tile screen) {
    if (screen.x == -1 || screen.y == -1)
        return map_point(-1);
    int city_orientation = city_view_orientation() / 2;
    return SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x][screen.y];
}
screen_tile mappoint_to_screentile(map_point point) {
    if (!map_grid_inside_map_area(point.grid_offset()))
        return {-1, -1};

    pixel_coordinate start;
    pixel_coordinate column_step;
    pixel_coordinate row_step;
    screentile_calc_params_by_orientation(city_view_orientation() / 2, &start, &column_step, &row_step);

    int columns = point.x();
    int rows = point.y();

    return {(start.x + (rows * row_step.x) + (columns * column_step.x)) / 2,
            (start.y + (rows * row_step.y) + (columns * column_step.y))};
}

static pixel_coordinate MAPPOINT_TO_PIXEL_LOOKUP[GRID_SIZE_TOTAL];
void record_mappoint_pixelcoord(map_point point, pixel_coordinate pixel) {
    MAPPOINT_TO_PIXEL_LOOKUP[point.grid_offset()] = {pixel.x, pixel.y};
}
pixel_coordinate mappoint_to_pixel(map_point point) {
    return MAPPOINT_TO_PIXEL_LOOKUP[point.grid_offset()];
}

pixel_coordinate pixel_to_viewport_coord(pixel_coordinate pixel) {
    return pixel - city_view_data_unsafe().viewport.offset;
}
camera_coordinate pixel_to_camera_coord(pixel_coordinate pixel, bool relative) {
    // check if within viewport
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};

    // remove viewport offset
    pixel = pixel_to_viewport_coord(pixel);

    // adjust by zoom scale
    pixel.x = calc_adjust_with_percentage(pixel.x, zoom_get_percentage());
    pixel.y = calc_adjust_with_percentage(pixel.y, zoom_get_percentage());

    if (!relative)
        pixel += city_view_data_unsafe().camera.position;
    return pixel;
}
screen_tile pixel_to_screentile(pixel_coordinate pixel) {
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};

    // get the absolute camera pixel coords
    camera_coordinate coord = pixel_to_camera_coord(pixel, false);

    // black magic
    int odd = (coord.x / HALF_TILE_WIDTH_PIXELS + coord.y / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_is_odd = (coord.x / HALF_TILE_WIDTH_PIXELS) & 1;
    int y_is_odd = (coord.y / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_mod = (coord.x % HALF_TILE_WIDTH_PIXELS) / 2;
    int y_mod = coord.y % HALF_TILE_HEIGHT_PIXELS;
    int screen_x_offset = coord.x / TILE_WIDTH_PIXELS;
    int screen_y_offset = coord.y / HALF_TILE_HEIGHT_PIXELS;
    if (odd) {
        if (x_mod + y_mod >= HALF_TILE_HEIGHT_PIXELS - 1) {
            screen_y_offset++;
            if (x_is_odd && !y_is_odd)
                screen_x_offset++;
        }
    } else {
        if (y_mod > x_mod)
            screen_y_offset++;
        else if (x_is_odd && y_is_odd)
            screen_x_offset++;
    }
    return screen_tile(screen_x_offset, screen_y_offset);
}