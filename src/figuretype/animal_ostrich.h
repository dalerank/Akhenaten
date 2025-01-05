#pragma once

#include "figure_animal.h"

class figure_ostrich : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH, figure_ostrich)
    figure_ostrich(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_OSTRICH, "ostrich"}; }
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};