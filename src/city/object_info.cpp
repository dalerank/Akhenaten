#include "object_info.h"
#include "city/city_figures.h"

figure *object_info::nfigure_t::get() const {
    const int figure_id = ids[selected_index];
    return ::figure_get(figure_id);
}

void object_info::fill_figures_info(tile2i center) {
    nfigure.selected_index = 0;
    nfigure.ids.clear();

    grid_tiles tiles = map_grid_get_tiles(center.shifted(-1, -1), center.shifted(1, 1));

    for (const auto &tile : tiles) {
        int figure_id = map_figure_id_get(tile);
        while (figure_id > 0 && !nfigure.ids.full()) {
            figure *f = ::figure_get(figure_id);
            const bool valid_figure = std::find(forbidden_figure_types.begin(), forbidden_figure_types.end(), f->type) == forbidden_figure_types.end();
            const bool is_alive = f->state != FIGURE_STATE_DEAD || f->action_state != FIGURE_ACTION_149_CORPSE;
            if (is_alive && valid_figure) {
                nfigure.ids.push_back(figure_id);
            }
            figure_id = (figure_id != f->next_figure) ? f->next_figure : 0;
        }

        if (nfigure.ids.full()) {
            break;
        }
    }
}
