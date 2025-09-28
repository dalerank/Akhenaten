#pragma once

#include "figure/figure_type.h"

struct figure_properties {
    int defense_value;
    int missile_defense_value;
    int missile_attack_value;
    int missile_delay;
};

const figure_properties& figure_properties_for_type(e_figure_type type);