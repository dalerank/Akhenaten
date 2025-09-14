#include "object_info.h"
#include "city/city_figures.h"

figure *object_info::nfigure_t::get() const {
    const int figure_id = ids[selected_index];
    return ::figure_get(figure_id);
}
