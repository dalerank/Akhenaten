#include "lookup.h"
#include "core/calc.h"
#include "graphics/elements/menu.h"
#include "graphics/image.h"
#include "grid/grid.h"
#include "core/profiler.h"

constexpr int map_lookup_size = 500;
static tile2i SCREENTILE_TO_MAPPOINT_LOOKUP[4][map_lookup_size][map_lookup_size];
constexpr int max_grid_offset = 4 * 500 * 500;
static void screentile_calc_params_by_orientation(int city_orientation, vec2i* start, vec2i* column_step, vec2i* row_step) {
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
    vec2i start;
    vec2i column_step;
    vec2i row_step;
    screentile_calc_params_by_orientation(city_orientation, &start, &column_step, &row_step);

    for (int y = 0; y < GRID_LENGTH; y++) {
        screen_tile screen = start;
        for (int x = 0; x < GRID_LENGTH; x++) {
            int grid_offset = x + GRID_LENGTH * y;

            bool is_inside_area = map_grid_inside_map_area(grid_offset) || 1;
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
    constexpr int orientations = 4;
    for (int o = 0; o < orientations; ++o) {
        for (int y = 0; y < (2 * GRID_LENGTH) + 1; y++) {
            for (int x = 0; x < GRID_LENGTH + 3; x++) {
                SCREENTILE_TO_MAPPOINT_LOOKUP[o][x][y].set(-1);
            }
        }
    }
    // fill in tables
    for (int orientation = 0; orientation < orientations; ++orientation) {
        fill_in_lookup_table_for_orientation(orientation);
    }
}

tile2i screen_to_tile(vec2i screen) {
    if (screen.x == -1 || screen.y == -1) {
        return tile2i(-1);
    }

    int city_orientation = city_view_orientation() / 2;
    return SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x][screen.y];
}

vec2i tile_to_screen(tile2i point) {
    if (!map_grid_inside_map_area(point.grid_offset())) {
        return { -1, -1 };
    }

    vec2i start;
    vec2i column_step;
    vec2i row_step;
    int city_orientation = city_view_orientation() / 2;
    screentile_calc_params_by_orientation(city_orientation, &start, &column_step, &row_step);

    int columns = point.x();
    int rows = point.y();

    vec2i screen = { -1, -1 };
    tile2i *ptr = nullptr;
    switch (city_orientation) {
    case 0:
    case 2:
        screen.x = (start.x + (rows * row_step.x) + (columns * column_step.x)) / 2;
        ptr = SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][screen.x];
        for (int i = 0; i < map_lookup_size; ++i, ++ptr) {
            if (ptr->grid_offset() == point.grid_offset()) {
                screen.y = i;
                break;
            }
        }
        break;

    case 1:
    case 3:
        screen.y = (start.y + (rows * row_step.y) + (columns * column_step.y));
        for (int i = 0; i < map_lookup_size; ++i) {
            ptr = &SCREENTILE_TO_MAPPOINT_LOOKUP[city_orientation][i][screen.y];
            if (ptr->grid_offset() == point.grid_offset()) {
                screen.x = i;
                break;
            }
        }
        break;
    }

    return screen;
}

static vec2i MAPPOINT_TO_PIXEL_LOOKUP[GRID_SIZE_TOTAL];
void clear_mappoint_pixelcoord() {
    OZZY_PROFILER_FUNCTION();
    memset(MAPPOINT_TO_PIXEL_LOOKUP, 0, sizeof(MAPPOINT_TO_PIXEL_LOOKUP));
}

void record_mappoint_pixelcoord(tile2i point, vec2i pixel) {
    MAPPOINT_TO_PIXEL_LOOKUP[point.grid_offset()] = {pixel.x, pixel.y};
}

vec2i lookup_tile_to_pixel(tile2i point) {
    int grid_offset = point.grid_offset();
    assert(grid_offset < max_grid_offset);
    return MAPPOINT_TO_PIXEL_LOOKUP[grid_offset];
}

vec2i pixel_to_viewport(vec2i pixel) {
    return pixel - g_city_view.viewport.offset;
}

vec2i pixel_to_camera_coord(vec2i pixel, bool relative) {
    // check if within viewport
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};

    // remove viewport offset
    pixel = pixel_to_viewport(pixel);

    // adjust by zoom scale
    pixel.x = calc_adjust_with_percentage<int>(pixel.x, g_zoom.get_percentage());
    pixel.y = calc_adjust_with_percentage<int>(pixel.y, g_zoom.get_percentage());

    pixel += relative ? vec2i{0, 0} : g_city_view.camera.position;
    return pixel;
}

vec2i pixel_to_screentile(vec2i pixel) {
    if (!pixel_is_inside_viewport(pixel))
        return {-1, -1};

    // get the absolute camera pixel coords
    vec2i coord = pixel_to_camera_coord(pixel, false);

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

    return vec2i(screen_x_offset, screen_y_offset);
}