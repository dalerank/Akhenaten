#pragma once

#include "animal_predator.h"

class figure_lion : public figure_predator {
public:
    FIGURE_METAINFO(FIGURE_LION, figure_lion)
    figure_lion(figure* f) : figure_predator(f) {}

    using static_params = predator_static_params FIGURE_STATIC_DATA_T;
};
