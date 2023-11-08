#pragma once

#include "core/buffer.h"
#include "figure/figure.h"

enum {
    TEST_SEARCH_DEAD,
    TEST_SEARCH_ENEMY,
    TEST_SEARCH_HERD,
    TEST_SEARCH_FORMATION,
    TEST_SEARCH_ATTACKING_NATIVE,
    TEST_SEARCH_CITIZEN,
    TEST_SEARCH_NON_CITIZEN,
    TEST_SEARCH_FIGHTING_FRIENDLY,
    TEST_SEARCH_FIGHTING_ENEMY,
    TEST_SEARCH_HAS_COLOR,
};

/**
 * Returns the first figure at the given offset
 * @param grid_offset Map offset
 * @return Figure ID of first figure at offset
 */
int map_figure_id_get(int grid_offset);
inline int map_figure_id_get(tile2i tile) { return map_figure_id_get(tile.grid_offset());  }

figure *map_figure_get(int grid_offset);

void map_figure_set(int grid_offset, int id);
inline void map_figure_set(tile2i tile, int id) { map_figure_set(tile.grid_offset(), id); }
/**
 * Returns whether there is a figure at the given offset
 * @param grid_offset Map offset
 * @return True if there is a figure, otherwise false
 */
bool map_has_figure_at(int grid_offset);
bool map_has_figure_but(tile2i tile, int id);
inline bool map_has_figure_at(tile2i tile) { return map_has_figure_at(tile.grid_offset());  }

// void map_figure_add();
//
// void map_figure_update();

// void map_figure *f->map_figure_remove();

int map_figure_foreach_until(int grid_offset, int test);

/**
 * Clears the map
 */
void map_figure_clear(void);
