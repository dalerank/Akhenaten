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