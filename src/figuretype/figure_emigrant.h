#pragma once

#include "figure/figure.h"

class figure_emigrant : public figure_impl {
public:
    figure_emigrant(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_EMIGRANT, "emigrant"}; }
    virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual sound_key phrase_key() const override;
};