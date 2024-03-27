#pragma once

#include "figure/figure.h"

class figure_worker : public figure_impl {
public:
    figure_worker(figure *f) : figure_impl(f) {}
    virtual figure_worker *dcast_worker() override { return this; }

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void poof() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_LABORER, "worker"}; }
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LABOR; }

    tile2i small_mastaba_tile4work(building *b);
};