#pragma once

#include "figure/figure.h"

enum e_robber_action {
    ACTION_120_ROBBER_CREATED = 120,
    ACTION_121_ROBBER_MOVING = 121,
    ACTION_122_ROBBER_HIDE = 122,
    ACTION_123_ROBBER_LEAVING = 123,
};

class figure_robber : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_ROBBER, figure_robber)
    figure_robber(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    static void create(building *b);
};