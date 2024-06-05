#pragma once

#include "figuretype/figure_cartpusher.h"

class figure_storageyard_cart : public figure_cartpusher {
public:
    FIGURE_METAINFO(FIGURE_STORAGEYARD_CART, figure_storageyard_cart)
    figure_storageyard_cart(figure *f) : figure_cartpusher(f) {}

    virtual figure_storageyard_cart *dcast_storageyard_cart() override { return this; }

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }
};