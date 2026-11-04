#pragma once

#include "figuretype/figure_hunter.h"

class figure_ostrich_hunter : public figure_hunter {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH_HUNTER, figure_ostrich_hunter)
    figure_ostrich_hunter(figure *f) : figure_hunter(f) {}

    struct static_params : public figure_hunter::static_params {
    } FIGURE_STATIC_DATA_T;

    virtual e_figure_type prey_type() const override { return FIGURE_OSTRICH; }
    virtual e_figure_type missile_type() const override { return FIGURE_HUNTER_ARROW; }
};

ANK_CONFIG_STRUCT(figure_ostrich_hunter::static_params,
    max_hunting_distance, attack_distance, shoot_tick, shoot_timeout, animal_attack_value)
