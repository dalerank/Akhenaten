#pragma once

#include "figure/figure.h"

class figure_reed_gatherer : public figure_impl {
public:
    figure_reed_gatherer(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_REED_GATHERER, "reed"}; }
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};
