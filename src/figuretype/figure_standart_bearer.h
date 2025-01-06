#pragma once

#include "figure/figure.h"

class figure_standard_bearer : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_STANDARD_BEARER, figure_standard_bearer)
    figure_standard_bearer(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void figure_draw(painter &ctx, vec2i pixel, int hightlight, vec2i *coord_out) override;
    virtual void before_poof() override;
};