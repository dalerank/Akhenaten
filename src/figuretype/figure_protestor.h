#pragma once

#include "figure/figure.h"

class figure_protestor : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PROTESTER, figure_protestor)
    figure_protestor(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};