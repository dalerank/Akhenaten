#pragma once

#include "figure/figure.h"

class figure_delivery_boy : public figure_impl {
public:
    figure_delivery_boy(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_DELIVERY_BOY, "marketboy"}; }
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_BAZAAR_ACCESS; }
};