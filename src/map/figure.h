#ifndef MAP_FIGURE_H
#define MAP_FIGURE_H

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
int map_figure_at(int grid_offset);

/**
 * Returns whether there is a figure at the given offset
 * @param grid_offset Map offset
 * @return True if there is a figure, otherwise false
 */
int map_has_figure_at(int grid_offset);

//void map_figure_add();
//
//void map_figure_update();

//void map_figure *f->map_figure_remove();

bool map_figure_foreach_until(int grid_offset, int test);

/**
 * Clears the map
 */
void map_figure_clear(void);

void map_figure_save_state(buffer *buf);

void map_figure_load_state(buffer *buf);

#endif // MAP_FIGURE_H
