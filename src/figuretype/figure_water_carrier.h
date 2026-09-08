#pragma once

#include "figure/figure.h"

enum e_water_carrier_action {
    ACTION_72_WATER_CARRIER_ROAMING = 72,
    ACTION_73_WATER_CARRIER_RETURNING = 73,
    ACTION_150_WATER_CARRIER_ATTACKED = 150,
};

class figure_water_carrier : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_WATER_CARRIER, figure_water_carrier)
    figure_water_carrier(figure *f) : figure_impl(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual int provide_service() override;
    virtual void acquire_attack() override;
};
