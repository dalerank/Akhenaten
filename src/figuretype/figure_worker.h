#pragma once

#include "figure/figure.h"

class figure_worker : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LABORER, figure_worker)
    
    figure_worker(figure *f) : figure_impl(f) {}
    virtual figure_worker *dcast_worker() override { return this; }

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_LABORER, "worker"}; }
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LABOR; }
    virtual figure_sound_t get_sound_reaction(pcstr key) const;

    tile2i mastaba_tile4work(building *b);
};