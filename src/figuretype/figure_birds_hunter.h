#pragma once

#include "figuretype/figure_hunter.h"

class figure_birds_hunter : public figure_hunter {
public:
    FIGURE_METAINFO(FIGURE_BIRDS_HUNTER, figure_birds_hunter)
    figure_birds_hunter(figure *f) : figure_hunter(f) {}

    struct static_params : public figure_hunter::static_params {
    } FIGURE_STATIC_DATA_T;

    virtual e_figure_type prey_type() const override { return FIGURE_BIRDS; }
    virtual e_figure_type missile_type() const override { return FIGURE_HUNTER_ARROW; }
};

ANK_CONFIG_STRUCT(figure_birds_hunter::static_params,
    max_hunting_distance, attack_distance, shoot_tick, shoot_timeout, animal_attack_value)
