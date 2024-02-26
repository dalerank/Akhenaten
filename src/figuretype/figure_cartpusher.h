#pragma once

#include "figure/figure.h"

class figure_cartpusher : public figure_impl {
public:
    figure_cartpusher(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) override;
    virtual e_figure_sound phrase() const override { return {FIGURE_CART_PUSHER, "cartpusher"}; }
    virtual e_overlay get_overlay() const override { return OVERLAY_NONE; }
    virtual sound_key phrase_key() const override;

    void do_deliver(bool storageyard_cart, int action_done);
    void do_retrieve(int ACTION_DONE);
    void calculate_destination(bool warehouseman);

    void determine_deliveryman_destination();
    void determine_granaryman_destination();
    void determine_storageyard_cart_destination();
};