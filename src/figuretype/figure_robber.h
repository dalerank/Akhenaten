#pragma once

#include "figure/figure.h"

class figure_robber : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ROBBER, figure_robber)
        figure_robber(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_ROBBER, "robber" }; }
    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};