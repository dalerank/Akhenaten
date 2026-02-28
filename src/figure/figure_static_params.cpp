#include "figure/figure_static_params.h"

static std::array<const figure_static_params *, FIGURE_MAX> figure_impl_params;

void figure_static_params::set(e_figure_type e, const figure_static_params &p) {
    figure_impl_params[e] = &p;
}

const figure_static_params &figure_static_params::get(e_figure_type e) {
    const auto* cfg = figure_impl_params[e];
    return (!cfg ? figure_static_params::dummy : *cfg);
}

figure_static_params &figure_static_params::ref(e_figure_type e) {
    auto *cfg = figure_impl_params[e];
    assert(cfg);
    return *const_cast<figure_static_params*>(cfg);
}

figure_static_params figure_static_params::dummy;
void figure_static_params::initialize() {
    assert(animations.data.size() > 0);

    if (speed_mult == 0) speed_mult = 1;
    if (max_damage == 0) max_damage = 100;
    if (corpse_time_delay == 0) corpse_time_delay = 128;
}
