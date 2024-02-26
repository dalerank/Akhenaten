#pragma once

#include "figuretype/figure_cartpusher.h"

class figure_storageyard_cart : public figure_cartpusher {
public:
    figure_storageyard_cart(figure *f) : figure_cartpusher(f) {}

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }
};