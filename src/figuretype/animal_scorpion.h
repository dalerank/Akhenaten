#pragma once

#include "animal_predator.h"

class figure_scorpion : public figure_predator {
public:
    FIGURE_METAINFO(FIGURE_SCORPION, figure_scorpion)
    figure_scorpion(figure* f) : figure_predator(f) {}

    using static_params = predator_static_params FIGURE_STATIC_DATA_T;
};
