#pragma once

#include "figuretype/figure_cartpusher.h"

enum e_warehouse_cart_action {
    ACTION_9_WAREHOUSE_CART_DELIVERING_GOODS = 9,
};

class figure_storageyard_cart : public figure_cartpusher {
public:
    FIGURE_METAINFO(FIGURE_STORAGEYARD_CART, figure_storageyard_cart)
    figure_storageyard_cart(figure *f) : figure_cartpusher(f) {}

    virtual figure_storageyard_cart *dcast_storageyard_cart() override { return this; }

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }

    void do_retrieve(int action_done);
};