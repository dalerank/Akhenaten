#include "figure.h"

#include "map/grid.h"

static grid_xx figures = {0, {FS_UINT16, FS_UINT16}};

int map_has_figure_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(&figures, grid_offset) > 0;
}
int map_figure_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(&figures, grid_offset) : 0;
}

#include <assert.h>

bool map_figure_foreach_until(int grid_offset, int test) {
    if (map_grid_get(&figures, grid_offset) > 0) {
        int figure_id = map_grid_get(&figures, grid_offset);
        while (figure_id) {
            figure *f = figure_get(figure_id);

            bool result;
            switch (test) {
                case TEST_SEARCH_DEAD:
                    result = f->is_dead(); break;
                case TEST_SEARCH_ENEMY:
                    result = f->is_enemy(); break;
                case TEST_SEARCH_HERD:
                    result = f->is_herd(); break;
                case TEST_SEARCH_FORMATION:
                    result = f->is_formation(); break;
                case TEST_SEARCH_ATTACKING_NATIVE:
                    result = f->is_attacking_native(); break;
                case TEST_SEARCH_CITIZEN:
                    result = f->is_citizen(); break;
                case TEST_SEARCH_NON_CITIZEN:
                    result = f->is_non_citizen(); break;
                case TEST_SEARCH_FIGHTING_FRIENDLY:
                    result = f->is_fighting_friendly(); break;
                case TEST_SEARCH_FIGHTING_ENEMY:
                    result = f->is_fighting_enemy(); break;
                case TEST_SEARCH_HAS_COLOR:
                    result = f->has_figure_color(); break;
                default:
                    result = false;
            }
            if (result)
                return result;

            if (figure_id != f->next_figure)
                figure_id = f->next_figure;
            else
                figure_id = 0;
        }
    }
    return 0;
}
void figure::map_figure_add() {
    if (!map_grid_is_valid_offset(grid_offset))
        return;

    // check for figures on new tile, update "next_figure" pointers accordingly
    next_figure = 0;
    int on_tile = map_grid_get(&figures, grid_offset);
    if (on_tile) {
        figure *checking = figure_get(on_tile); // get first figure (head) on the new tile, if any is present
//        assert(checking->id != f->id); // hmmmm that'd be wrong
        if (checking->id == id)
            int a = 2;

        // traverse through chain
        while (checking->next_figure) {
            if (checking->next_figure == id) // this figure is already in the chain on this tile!!
                return;
            checking = figure_get(checking->next_figure); // else, traverse chain of figures as normal...
        }

        // last figure in the chain!
        checking->next_figure = id;
    } else
        map_grid_set(&figures, grid_offset, id);
}
void figure::map_figure_update() { // useless - but used temporarily for checking if figures are correct!
    if (!map_grid_is_valid_offset(grid_offset))
        return;

    // traverse through chain of figures on this tile
    int on_tile = map_grid_get(&figures, grid_offset);
    figure *checking = figure_get(on_tile);
    while (checking->id) {
        assert(checking->grid_offset == grid_offset);
        checking = figure_get(checking->next_figure);
    }
}
void figure::map_figure_remove() {
    if (!map_grid_is_valid_offset(grid_offset) || !map_grid_get(&figures, grid_offset)) {
        next_figure = 0;
        return;
    }

    // check for figures on new tile, update "next_figure" pointers accordingly
    int on_tile = map_grid_get(&figures, grid_offset);
    if (on_tile == id) // figure is the first (head) on its tile!
        map_grid_set(&figures, grid_offset, next_figure); // remove from chain, set the head as the next one in chain (0 is fine)
    else {
        figure *checking = figure_get(on_tile); // traverse through the chain to find this figure...
        while (checking->id && checking->next_figure != id)
            checking = figure_get(checking->next_figure);
        checking->next_figure = next_figure; // remove from chain, set previous figure to point "next" to the next one in chain (0 is fine)
    }
    next_figure = 0;
}
void map_figure_clear(void) {
    map_grid_clear(&figures);
}

void map_figure_save_state(buffer *buf) {
    map_grid_save_state(&figures, buf);
}
void map_figure_load_state(buffer *buf) {
    map_grid_load_state(&figures, buf);
}
