#pragma once

#include "figure/figure.h"

enum e_rioter_action {
    ACTION_120_RIOTER_CREATED = 120,
    ACTION_121_RIOTER_MOVING = 121,
    ACTION_122_RIOTER_HIDE = 122,
    ACTION_123_RIOTER_LEAVING = 123,
    ACTION_122_RIOTER_ATTACK = 124,
};

class figure_rioter : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_RIOTER, figure_rioter)
    figure_rioter(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return { FIGURE_RIOTER, "rioter" }; }
    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;

    int collapse_building();
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};