#pragma once

#include "figure/figure.h"

class figure_ostrich_hunter : public figure_impl {
public:
    figure_ostrich_hunter(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    //virtual void poof() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_OSTRICH_HUNTER, "oshunter"}; }
    virtual sound_key phrase_key() const override;
    virtual figure_sound_t get_sound_reaction(pcstr key) const;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
};