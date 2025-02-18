#pragma once

#include "figure/figure.h"

class figure_tower_sentry : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TOWER_SENTRY, figure_tower_sentry)
    figure_tower_sentry(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_SCRIBER, "towers" }; }
    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;
    virtual void poof() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    void tower_sentry_pick_target();
    int tower_sentry_init_patrol(building *b, int *x_tile, int *y_tile);
    void move_ticks_tower_sentry(int num_ticks);
};