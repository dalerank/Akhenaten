#pragma once

#include "figure/figure.h"

class figure_animal : public figure_impl {
public:
    figure_animal(figure *f) : figure_impl(f) {}
    virtual figure_animal *dcast_animal() override { return this; }

    virtual void herd_moved();
    virtual void moveto(tile2i tile);
};

bool figure_herd_roost(figure *f, int step, int bias, int max_dist, int terrain_mask);