#pragma once

#include "figure/figure.h"

class figure_constable : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_CONSTABLE, figure_constable)
    figure_constable(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_CONSTABLE, "police"}; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual const animations_t &anim() const override;

    bool fight_enemy(int category, int max_distance);
};