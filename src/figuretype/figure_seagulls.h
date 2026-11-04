#pragma once

#include "figure/figure.h"

class figure_seagulls : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SEAGULLS, figure_seagulls)
    figure_seagulls(figure *f) : figure_impl(f) {}
    virtual figure_seagulls *dcast_seagulls() override { return this; }

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override {}
    virtual void main_image_update() override {}
    virtual void cart_image_update() override {}

    static figure *create(tile2i tile);
};
