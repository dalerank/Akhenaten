#pragma once

#include "figure/figure.h"

enum shipwreck_limit {
    SHIPWRECK_FRAMES = 36,
    SHIPWRECK_WAIT_SETTLED = 1000,
};

class figure_shipwreck : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SHIPWRECK, figure_shipwreck)
    figure_shipwreck(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override {}
    virtual bool window_info_background(object_info &ctx) override;

    static figure *create(tile2i t);
};
