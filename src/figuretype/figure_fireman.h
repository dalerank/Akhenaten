#pragma once

#include "figure/figure.h"

class figure_fireman : public figure_impl {
public:
    figure_fireman(figure *f) : figure_impl(f) {}

    virtual void figure_action();
    void extinguish_fire();
    bool fight_fire();
};
