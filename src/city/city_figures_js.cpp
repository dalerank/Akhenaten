#include "city/city.h"

#include "js/js_game.h"

std::optional<bvariant> __city_get_figures_property(pcstr property) {
    return archive_helper::get(g_city.figures, property, true);
}
ANK_FUNCTION_1(__city_get_figures_property)

void __city_remove_figures(int ftype) { g_city.figures.remove_figures((e_figure_type)ftype); }
ANK_FUNCTION_1(__city_remove_figures)