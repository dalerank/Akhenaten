#pragma once

#include "figure/figure.h"

class figure_delivery_boy : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_DELIVERY_BOY, figure_delivery_boy)
    figure_delivery_boy(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
};
