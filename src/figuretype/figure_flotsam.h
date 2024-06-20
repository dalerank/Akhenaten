#pragma once

#include "figure/figure.h"

class figure_flotsam : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FLOTSAM, figure_flotsam)
    figure_flotsam(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
};