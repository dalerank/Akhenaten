#include "object_info.h"
#include "city/city_figures.h"

#include "graphics/view/lookup.h"
#include "dev/debug.h"

declare_console_var_int(fill_figure_radius, 30);

const terrain_info_type_tokens_t terrain_info_type_tokens;

figure *object_info::nfigure_t::get() const {
    const figure_id fid = ids[selected_index];
    return ::figure_get(fid);
}

void object_info::fill_figures_info(tile2i center) {
    nfigure.selected_index = 0;
    nfigure.ids.clear();
    vec2i center_pos = lookup_tile_to_pixel(center) + vec2i{ HALF_TILE_WIDTH_PIXELS, HALF_TILE_HEIGHT_PIXELS };

    grid_tiles tiles = map_grid_get_tiles(center.shifted(-1, -1), center.shifted(1, 1));
    svector<figure*, 32> possible_figures;
    for (const auto &tile : tiles) {
        int figure_id = map_figure_id_get(tile);
        while (figure_id > 0 && !possible_figures.full()) {
            figure *f = ::figure_get(figure_id);
            const bool valid_figure = std::find(forbidden_figure_types.begin(), forbidden_figure_types.end(), f->type) == forbidden_figure_types.end();
            const bool is_alive = f->state != FIGURE_STATE_DEAD && f->action_state != FIGURE_ACTION_149_CORPSE;
            const bool in_radius = center_pos.dist(f->main_cached_pos) < fill_figure_radius();
            if (is_alive && valid_figure && in_radius) {
                possible_figures.push_back(f);
            }
            figure_id = (figure_id != f->next_figure) ? f->next_figure : 0;
        }

        if (possible_figures.full()) {
            break;
        }
    }

    std::sort(possible_figures.begin(), possible_figures.end(), [&] (const figure *lhs, const figure *rhs) {
        float lhsa_sq = center_pos.dist_sq(lhs->main_cached_pos);
        float rhsa_sq = center_pos.dist_sq(rhs->main_cached_pos);
        return lhsa_sq < rhsa_sq;
    });

    for (int i = 0, size = std::min<int>(nfigure.ids.capacity(), possible_figures.size()); i < size;  ++i) {
        nfigure.ids.push_back(possible_figures[i]->id);
    }
}
