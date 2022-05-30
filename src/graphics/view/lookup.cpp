#include "graphics/elements/menu.h"
#include "core/calc.h"
#include "grid/grid.h"
#include "lookup.h"

static map_point SCREENTILE_TO_MAPPOINT_LOOKUP[4][500][500];
static void fill_in_lookup_table_for_orientation(int city_orientation) {
    int start_x;
    int start_y;
    int column_step_x;
    int column_step_y;
    int row_step_x;
    int row_step_y;
    switch (city_orientation) {
        default:
        case 0:
            start_x = GRID_LENGTH + 2;
            start_y = 3;
            column_step_x = 1;
            column_step_y = 1;
            row_step_x = -1;
            row_step_y = 1;
            break;
        case 1:
            start_x = 5;
            start_y = GRID_LENGTH;
            column_step_x = 1;
            column_step_y = -1;
            row_step_x = 1;
            row_step_y = 1;
            break;
        case 2:
            start_x = GRID_LENGTH + 2;
            start_y = (2 * GRID_LENGTH) - 3;
            column_step_x = -1;
            column_step_y = -1;
            row_step_x = 1;
            row_step_y = -1;
            break;
        case 3:
            start_x = (2 * GRID_LENGTH) - 1;
            start_y = GRID_LENGTH;
            column_step_x = -1;
            column_step_y = 1;
            row_step_x = -1;
            row_step_y = -1;
            break;
    }

//    int columns = point.x();
//    int rows = point.y();
//    return {
//            (start_x + (rows * row_step_x) + (columns * column_step_x)) / 2,
//            (start_y + (rows * row_step_y) + (columns * column_step_y))
//    };

    for (int y = 0; y < GRID_LENGTH; y++) {
        int screen_x = start_x;
        int screen_y = start_y;
        for (int x = 0; x < GRID_LENGTH; x++) {
            int grid_offset = x + GRID_LENGTH * y;

            bool is_inside_area = map_grid_inside_map_area(grid_offset);
            if (is_inside_area) // inside area
                SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen_x / 2][screen_y].set(grid_offset);
            else // outside area
                SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen_x / 2][screen_y].set(-1);
            screen_x += column_step_x;
            screen_y += column_step_y;
        }
        start_x += row_step_x;
        start_y += row_step_y;
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
    int city_orientation = city_view_orientation() / 2;
    return SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x][screen.y];
}
screen_tile mappoint_to_screentile(map_point point) {
    if (!map_grid_inside_map_area(point.grid_offset()))
        return {-1, -1};
    int start_x;
    int start_y;
    int column_step_x;
    int column_step_y;
    int row_step_x;
    int row_step_y;
    switch (city_view_data_unsafe()->orientation) {
        default:
        case 0:
            start_x = GRID_LENGTH + 2;
            start_y = 3;
            column_step_x = 1;
            column_step_y = 1;
            row_step_x = -1;
            row_step_y = 1;
            break;
        case 2:
            start_x = 5;
            start_y = GRID_LENGTH;
            column_step_x = 1;
            column_step_y = -1;
            row_step_x = 1;
            row_step_y = 1;
            break;
        case 4:
            start_x = GRID_LENGTH + 2;
            start_y = (2 * GRID_LENGTH) - 3;
            column_step_x = -1;
            column_step_y = -1;
            row_step_x = 1;
            row_step_y = -1;
            break;
        case 6:
            start_x = (2 * GRID_LENGTH) - 1;
            start_y = GRID_LENGTH;
            column_step_x = -1;
            column_step_y = 1;
            row_step_x = -1;
            row_step_y = -1;
            break;
    }

    int columns = point.x();
    int rows = point.y();
    return {
            (start_x + (rows * row_step_x) + (columns * column_step_x)) / 2,
            (start_y + (rows * row_step_y) + (columns * column_step_y))
    };
}

static pixel_coordinate MAPPOINT_TO_PIXEL_LOOKUP[GRID_SIZE_TOTAL];
void record_mappoint_pixel_coord(map_point point, pixel_coordinate coord) {
    MAPPOINT_TO_PIXEL_LOOKUP[point.grid_offset()] = {coord.x, coord.y};
}
pixel_coordinate mappoint_to_pixel(map_point point) {
    return MAPPOINT_TO_PIXEL_LOOKUP[point.grid_offset()];
}

camera_coordinate pixel_to_camera_coord(pixel_coordinate pixel) {
    // check if within viewport
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};

    // remove viewport offset
    pixel -= city_view_data_unsafe()->viewport.offset;
    //    pixel.y -= TOP_MENU_HEIGHT;

    // adjust by zoom scale
    pixel.x = calc_adjust_with_percentage(pixel.x, zoom_get_percentage());
    pixel.y = calc_adjust_with_percentage(pixel.y, zoom_get_percentage());

    pixel += camera_get_pixel_offset_internal();
    return pixel;
}
screen_tile pixel_to_screentile(pixel_coordinate pixel) {
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};
    camera_coordinate coord = pixel_to_camera_coord(pixel);

    int odd = (coord.x / HALF_TILE_WIDTH_PIXELS +
               coord.y / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_is_odd = (coord.x / HALF_TILE_WIDTH_PIXELS) & 1;
    int y_is_odd = (coord.y / HALF_TILE_HEIGHT_PIXELS) & 1;
    int x_mod = (coord.x % HALF_TILE_WIDTH_PIXELS) / 2;
    int y_mod = coord.y % HALF_TILE_HEIGHT_PIXELS;
    int screen_x_offset = coord.x / TILE_WIDTH_PIXELS;
    int y_view_offset = coord.y / HALF_TILE_HEIGHT_PIXELS;
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
    return city_view_get_camera_screentile() + screen_tile(
         screen_x_offset,
         y_view_offset
    );
}