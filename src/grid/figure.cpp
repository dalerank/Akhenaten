#include "figure.h"
#include "grid/figure_chunks.h"

#include "core/custom_span.hpp"
#include "grid/grid.h"
#include "io/io_buffer.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "city/city_figures.h"
#include "core/profiler.h"

#include <array>
#include <assert.h>


svector<figure_draw, 5000> g_figures_y_sort;
static uint32_t g_figures_y_sort_generation = 0;
static std::array<figure_draw_state, MAX_FIGURES> g_figure_draw_states;

figure_draw_state& map_figure_draw_state(int figure_id) {
    static figure_draw_state invalid;
    if (figure_id < 0 || figure_id >= MAX_FIGURES) {
        invalid.main_drawn.store(true, std::memory_order_relaxed);
        return invalid;
    }
    return g_figure_draw_states[figure_id];
}

void map_figure_draw_state_reset(int figure_id) {
    figure_draw_state& st = map_figure_draw_state(figure_id);
    st.main_pos = {-1, -1};
    st.cart_pos = {-1, -1};
}

void map_figure_draw_state_clear(int figure_id) {
    figure_draw_state& st = map_figure_draw_state(figure_id);
    st.main_pos = {};
    st.sort_pixel = {};
    st.cart_pos = {};
    st.main_drawn.store(false, std::memory_order_relaxed);
}

void map_figure_draw_states_clear_all() {
    for (int id = 0; id < MAX_FIGURES; ++id) {
        map_figure_draw_state_clear(id);
    }
}

bool map_has_figure_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(figure_grid_chunk::grid, grid_offset) > 0;
}

int map_figure_id_get(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(figure_grid_chunk::grid, grid_offset) : 0;
}

void map_figure_sort_by_y(const viewport_t& view) {
    OZZY_PROFILER_FUNCTION();
    g_figures_y_sort.clear();
    ++g_figures_y_sort_generation;
    for (figure *f : map_figures()) {
        if (f->state == FIGURE_STATE_NONE) {
            continue;
        }

        // Removed by city_figures_t::update; the sort must not touch simulation state.
        if (f->tile.x() >= GRID_LENGTH || f->tile.y() > GRID_LENGTH) {
            continue;
        }

        const vec2i draw_pos = f->main_sprite_pixel(view);
        if (draw_pos.x == 0 && draw_pos.y == 0) { // tile outside viewport
            continue;
        }

        figure_draw_state& st = map_figure_draw_state(f->id);
        st.main_pos = f->adjust_pixel_offset(draw_pos);
        st.sort_pixel = st.main_pos - f->crowd_pixel_offset() - vec2i(29, 15 + 8);
        st.main_drawn.store(false, std::memory_order_relaxed);
        g_figures_y_sort.push_back({f, st.main_pos, false});

        if (f->has_cart()) {
            st.cart_pos = f->cart_sprite_pixel();
            const image_t *img = image_get(f->cart_image_id);
            int cart_y = img ? img->animation.sprite_offset.y : 0;
            vec2i cart_bound_pos = st.cart_pos;
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

xspan<figure_draw> map_figures_in_row(const viewport_t& view, tile2i tile) {
    vec2i pixel_begin = view.lookup_tile_to_pixel(tile);
    vec2i pixel_end = pixel_begin + vec2i(0, TILE_HEIGHT_PIXELS);

    vec2i pixel_begin_scr = view.pixel_to_viewport(pixel_begin);
    vec2i pixel_end_scr = view.pixel_to_viewport(pixel_end);

    const float scale = g_zoom.get_scale();
    if (pixel_end_scr.x < 0 || pixel_end_scr.y < 0 || pixel_begin_scr.x * scale > view.size_pixels.x
        || pixel_begin_scr.y * scale > view.size_pixels.y) {
        return {};
    }

    // Every tile of a screen row asks for the same y band: search it once per row and worker.
    struct row_band {
        uint32_t generation = 0;
        int y = 0;
        figure_draw* begin = nullptr;
        figure_draw* end = nullptr;
    };
    thread_local row_band band;
    if (band.generation != g_figures_y_sort_generation || band.y != pixel_begin.y || !band.begin) {
        const auto by_y = [](const auto& f, int y) { return f.fpos.y < y; };
        band.begin = std::lower_bound(g_figures_y_sort.begin(), g_figures_y_sort.end(), pixel_begin.y, by_y);
        band.end = std::lower_bound(band.begin, g_figures_y_sort.end(), pixel_end.y, by_y);
        band.generation = g_figures_y_sort_generation;
        band.y = pixel_begin.y;
    }

    return xspan<figure_draw>(band.begin, band.end);
}

void map_figure_set(int grid_offset, int id) {
    map_grid_set(figure_grid_chunk::grid, grid_offset, id);
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
    map_grid_clear(figure_grid_chunk::grid);
}
