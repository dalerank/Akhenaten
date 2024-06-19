#pragma once

#include "figure/figure.h"

class figure_shipwreck : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SHIPWRECK, figure_shipwreck)
    figure_shipwreck(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool window_info_background(object_info &ctx) override;

    static figure *create(tile2i t);
};