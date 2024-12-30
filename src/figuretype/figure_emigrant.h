#pragma once

#include "figure/figure.h"

class figure_emigrant : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_EMIGRANT, figure_emigrant)
    figure_emigrant(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual void update_animation() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_EMIGRANT, "emigrant"}; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual sound_key phrase_key() const override;
    virtual const animations_t &anim() const override;

    static figure *create(building *house, int num_people);
};