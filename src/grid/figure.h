#pragma once

#include "core/buffer.h"
#include "core/custom_span.hpp"
#include "figure/figure.h"

#include <atomic>

enum {
    TEST_SEARCH_DEAD,
    TEST_SEARCH_ENEMY,
    TEST_SEARCH_HERD,
    TEST_SEARCH_FORMATION,
    TEST_SEARCH_CRIMINAL,
    TEST_SEARCH_CITIZEN,
    TEST_SEARCH_NON_CITIZEN,
    TEST_SEARCH_FIGHTING_FRIENDLY,
    TEST_SEARCH_FIGHTING_ENEMY,
    TEST_SEARCH_HAS_COLOR,
};

struct figure_draw {
    figure *f;
    vec2i fpos;
    bool draw_cart = false;
};

struct figure_draw_state {
    vec2i main_pos;
    vec2i sort_pixel;
    vec2i cart_pos;
    std::atomic<bool> main_drawn{false};
};

figure_draw_state& map_figure_draw_state(int figure_id);
void map_figure_draw_state_reset(int figure_id);
void map_figure_draw_state_clear(int figure_id);
void map_figure_draw_states_clear_all();

int map_figure_id_get(int grid_offset);
inline int map_figure_id_get(tile2i tile) { return map_figure_id_get(tile.grid_offset());  }

figure *map_figure_get(int grid_offset);
inline figure *map_figure_get(tile2i tile) { return map_figure_get(tile.grid_offset()); }

void map_figure_set(int grid_offset, int id);
inline void map_figure_set(tile2i tile, int id) { map_figure_set(tile.grid_offset(), id); }

bool map_has_figure_at(int grid_offset);
bool map_has_figure_but(tile2i tile, int id);
inline bool map_has_figure_at(tile2i tile) { return map_has_figure_at(tile.grid_offset());  }

int map_figure_foreach_until(int grid_offset, int test);
inline int map_figure_foreach_until(tile2i tile, int test) { return map_figure_foreach_until(tile.grid_offset(), test); }

void map_figure_clear();
void map_figure_sort_by_y();

xspan<figure_draw> map_figures_in_row(tile2i tile);
