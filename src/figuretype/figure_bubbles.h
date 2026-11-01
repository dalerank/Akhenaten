#pragma once

#include "figure/figure.h"

// OG FIG_BUBBLES (28): short-lived sinking/water VFX — one frame per tick, gone after 22.
class figure_bubbles : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BUBBLES, figure_bubbles)
    figure_bubbles(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void cart_image_update() override {}
    virtual void update_animation() override;
    virtual void main_image_update() override {}

    static figure *create(tile2i tile);
};
