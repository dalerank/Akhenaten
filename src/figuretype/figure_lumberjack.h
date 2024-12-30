#pragma once

#include "figure/figure.h"

class figure_lumberjack : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_LUMBERJACK, figure_lumberjack)
    figure_lumberjack(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_LUMBERJACK, "woodcutter"}; }
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};