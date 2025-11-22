#include "figure.h"

#include "core/custom_span.hpp"
#include "grid/grid.h"
#include "io/io_buffer.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "graphics/view/view.h"
#include "city/city_figures.h"

#include <assert.h>

static grid_xx grid_figures = {0, FS_UINT16};

svector<figure_draw, 5000> g_figures_y_sort;

bool map_has_figure_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(grid_figures, grid_offset) > 0;
}

int map_figure_id_get(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(grid_figures, grid_offset) : 0;
}

void map_figure_sort_by_y() {
    g_figures_y_sort.clear();
    for (figure *f : map_figures()) {
        if (f->state == FIGURE_STATE_NONE) {
            continue;
        }

        if (f->tile.x() >= GRID_LENGTH || f->tile.y() > GRID_LENGTH) {
            f->tile = {-1, -1};
            f->main_cached_pos = {-1, -1};
            f->cart_cached_pos = {-1, -1};
            f->poof();
            continue;
        }

        const vec2i draw_pos = f->main_sprite_pixel();
        if (draw_pos.x == 0 && draw_pos.y == 0) { // tile outside viewport
            continue;
        }

        f->main_cached_pos = draw_pos;

        f->main_cached_pos = f->adjust_pixel_offset(f->main_cached_pos);
        f->is_main_drawn = false;
        f->is_cart_drawn = false;
        g_figures_y_sort.push_back({ f, f->main_cached_pos, false });

        if (f->has_cart()) {
            f->cart_cached_pos = f->cart_sprite_pixel();
            const image_t *img = image_get(f->cart_image_id);
            int cart_y = img ? img->animation.sprite_offset.y : 0;
            vec2i cart_bound_pos = f->cart_cached_pos;
            switch (f->direction) {
            case DIR_6_TOP_LEFT:
                cart_bound_pos += vec2i(0, -cart_y / 2);
                break;
            }
            g_figures_y_sort.push_back({ f, cart_bound_pos, true });
        }
    }

    std::sort(g_figures_y_sort.begin(), g_figures_y_sort.end(), [] (auto &lhs, auto &rhs) {
        return lhs.fpos.y < rhs.fpos.y;
    });
}

custom_span<figure_draw> map_figures_in_row(tile2i tile) {
    vec2i pixel_begin = lookup_tile_to_pixel(tile);
    vec2i pixel_end = pixel_begin + vec2i(0, TILE_HEIGHT_PIXELS);

    vec2i pixel_begin_scr = pixel_to_viewport(pixel_begin);
    vec2i pixel_end_scr = pixel_to_viewport(pixel_end);

    if (pixel_end_scr.x < 0 || pixel_end_scr.y < 0 
        || pixel_begin_scr.x > g_city_view.viewport.size_pixels.x
        || pixel_begin_scr.y > g_city_view.viewport.size_pixels.y) {
        return {};
    }

    auto begin = std::lower_bound(g_figures_y_sort.begin(), g_figures_y_sort.end(), pixel_begin.y, [](const auto &f, int y) {
        return f.fpos.y < y;
    });

    if (begin == g_figures_y_sort.end()) {
        return {};
    }

    auto end = std::lower_bound(g_figures_y_sort.begin(), g_figures_y_sort.end(), pixel_end.y, [](const auto &f, int y) {
        return f.fpos.y < y;
    });

    if (end == g_figures_y_sort.end()) {
        custom_span<figure_draw>(begin, g_figures_y_sort.end());
    }

    return custom_span<figure_draw>(begin, end);
}

void map_figure_set(int grid_offset, int id) {
    map_grid_set(grid_figures, grid_offset, id);
}

figure *map_figure_get(int grid_offset) {
    int id = map_figure_id_get(grid_offset);
    return figure_get(id);
}

bool map_has_figure_but(tile2i tile, int id) {
    if (map_figure_id_get(tile.grid_offset()) > 0) {
        int figure_id = map_figure_id_get(tile.grid_offset());
        while (figure_id) {
            if (figure_id != id) {
                return true;
            }

            figure* f = figure_get(figure_id);
            if (figure_id != f->next_figure) {
                figure_id = f->next_figure;
            } else {
                figure_id = 0;
            }
        }
    }

    return false;
}

int map_figure_foreach_until(int grid_offset, int test) {
    if (map_figure_id_get(grid_offset) > 0) {
        int figure_id = map_figure_id_get(grid_offset);
        if (figure_id >= MAX_FIGURES) {
            return 0;
        }

        int last_figure_id = figure_id;
        while (figure_id) {
            figure* f = figure_get(figure_id);
            if (figure_id >= MAX_FIGURES) {
                return 0;
            }

            if (!f->type) {
                return 0;
            }

            bool result;
            switch (test) {
            case TEST_SEARCH_DEAD: result = f->is_dead(); break;
            case TEST_SEARCH_ENEMY: result = f->is_enemy(); break;
            case TEST_SEARCH_HERD: result = f->is_herd(); break;
            case TEST_SEARCH_FORMATION: result = f->is_soldier(); break;
            case TEST_SEARCH_CRIMINAL: result = f->is_criminal(); break;
            case TEST_SEARCH_CITIZEN: result = f->is_citizen(); break;
            case TEST_SEARCH_NON_CITIZEN: result = f->is_non_citizen(); break;
            case TEST_SEARCH_FIGHTING_FRIENDLY: result = f->is_fighting_friendly(); break;
            case TEST_SEARCH_FIGHTING_ENEMY: result = f->is_fighting_enemy(); break;
            case TEST_SEARCH_HAS_COLOR: result = !!f->get_figure_color(); break;
            default:
                result = false;
            }

            if (result) {
                return figure_id;
            }

            last_figure_id = figure_id;
            if (figure_id != f->next_figure) {
                figure_id = f->next_figure;
            } else {
                figure_id = 0;
            }
        }
    }

    return 0;
}

void map_figure_clear(void) {
    map_grid_clear(grid_figures);
}

io_buffer* iob_figure_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &grid_figures);
});
