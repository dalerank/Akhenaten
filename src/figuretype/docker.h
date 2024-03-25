#pragma once

#include "figure/figure.h"

class figure_docker : public figure_impl {
public:
    figure_docker(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual void on_destroy() override;
};