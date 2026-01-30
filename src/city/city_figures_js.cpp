#include "city/city.h"

#include "js/js_game.h"

std::optional<bvariant> __city_get_figures_property(pcstr property) {
    return archive_helper::get(g_city.figures, property, true);
}
ANK_FUNCTION_1(__city_get_figures_property)

void __city_remove_figures(int ftype) { g_city.figures.remove_figures((e_figure_type)ftype); }
ANK_FUNCTION_1(__city_remove_figures)

int __figure_get_type(int fid) { return figure_get(fid)->type; }
ANK_FUNCTION_1(__figure_get_type)

bool __figure_is_valid(int fid) { return figure_get(fid)->is_valid(); }
ANK_FUNCTION_1(__figure_is_valid)

int __figure_get_action_state(int fid) { return figure_get(fid)->action_state; }
ANK_FUNCTION_1(__figure_get_action_state)

int __figure_get_destination_building_id(int fid) { return figure_get(fid)->destination_building_id; }
ANK_FUNCTION_1(__figure_get_destination_building_id)