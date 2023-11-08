#include "figure.h"

#include "grid/grid.h"
#include "io/io_buffer.h"

#include <assert.h>

static grid_xx grid_figures = {0, {FS_UINT16, FS_UINT16}};

bool map_has_figure_at(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(&grid_figures, grid_offset) > 0;
}

int map_figure_id_get(int grid_offset) {
    return map_grid_is_valid_offset(grid_offset) ? map_grid_get(&grid_figures, grid_offset) : 0;
}

void map_figure_set(int grid_offset, int id) {
    map_grid_set(&grid_figures, grid_offset, id);
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
        while (figure_id) {
            figure* f = figure_get(figure_id);

            bool result;
            switch (test) {
            case TEST_SEARCH_DEAD: result = f->is_dead(); break;
            case TEST_SEARCH_ENEMY: result = f->is_enemy(); break;
            case TEST_SEARCH_HERD: result = f->is_herd(); break;
            case TEST_SEARCH_FORMATION: result = f->is_formation(); break;
            case TEST_SEARCH_ATTACKING_NATIVE: result = f->is_attacking_native(); break;
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
    map_grid_clear(&grid_figures);
}

io_buffer* iob_figure_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &grid_figures);
});
