#include "lookup.h"
#include "view.h"
#include "core/calc.h"
#include "graphics/elements/menu.h"
#include "graphics/image.h"
#include "grid/grid.h"
#include "core/profiler.h"

tile2i& screentile_lookup_t::at(int orientation, int x, int y) {
    return tables[index(orientation, x, y)];
}

tile2i screentile_lookup_t::at(int orientation, int x, int y) const {
    return tables[index(orientation, x, y)];
}

void screentile_lookup_t::ensure_tables() {
    if (!tables.empty()) {
        return;
    }

    tables.assign(table_size, tile2i(-1));
}

screentile_lookup_t::orientation_params_t screentile_lookup_t::calc_params_by_orientation(int city_orientation) {
    switch (city_orientation) {
    default:
    case 0:
        return {{GRID_LENGTH + 2, 1}, {1, 1}, {-1, 1}};
    case 1:
        return {{3, GRID_LENGTH}, {1, -1}, {1, 1}};
    case 2:
        return {{GRID_LENGTH + 2, (2 * GRID_LENGTH) - 1}, {-1, -1}, {1, -1}};
    case 3:
        return {{(2 * GRID_LENGTH) + 1, GRID_LENGTH}, {-1, 1}, {-1, -1}};
    }
}

void screentile_lookup_t::fill_in_for_orientation(int city_orientation) {
    const auto params = calc_params_by_orientation(city_orientation);
    vec2i start = params.start;

    for (int y = 0; y < GRID_LENGTH; y++) {
        screen_tile screen = start;
        for (int x = 0; x < GRID_LENGTH; x++) {
            int grid_offset = x + GRID_LENGTH * y;

            bool is_inside_area = map_grid_inside_map_area(grid_offset) || 1;
            auto &cell = at(city_orientation, screen.x / 2, screen.y);

            if (is_inside_area) // inside area
                cell.set(grid_offset);
            else // outside area
                cell.set(-1);

            screen += params.column_step;
        }
        start += params.row_step;
    }
}

void screentile_lookup_t::calculate() {
    ensure_tables();

    for (int o = 0; o < orientations; ++o) {
        for (int y = 0; y < (2 * GRID_LENGTH) + 1; y++) {
            for (int x = 0; x < GRID_LENGTH + 3; x++) {
                at(o, x, y).set(-1);
            }
        }
    }

    for (int orientation = 0; orientation < orientations; ++orientation) {
        fill_in_for_orientation(orientation);
    }
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
    assert(grid_offset < screentile_lookup_t::max_grid_offset);
    return MAPPOINT_TO_PIXEL_LOOKUP[grid_offset];
}

vec2i pixel_to_viewport(vec2i pixel) {
    return pixel - g_camera.offset;
}

vec2i pixel_to_camera_coord(vec2i pixel, bool relative) {
    // check if within viewport
    if (!g_camera.contains_pixel(pixel))
        return {-1, -1};

    // remove viewport offset
    pixel = pixel_to_viewport(pixel);

    // adjust by zoom scale
    pixel.x = calc_adjust_with_percentage<int>(pixel.x, g_zoom.get_percentage());
    pixel.y = calc_adjust_with_percentage<int>(pixel.y, g_zoom.get_percentage());

    pixel += relative ? vec2i{0, 0} : g_camera.camera_position;
    return pixel;
}

vec2i pixel_to_screentile(vec2i pixel) {
    if (!g_camera.contains_pixel(pixel))
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