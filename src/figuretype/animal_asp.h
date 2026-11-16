#pragma once

#include "animal_predator.h"

class figure_asp : public figure_predator {
public:
    FIGURE_METAINFO(FIGURE_ASP, figure_asp)
    figure_asp(figure* f) : figure_predator(f) {}

    using static_params = predator_static_params FIGURE_STATIC_DATA_T;
};
