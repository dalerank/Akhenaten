#pragma once

#include "animal.h"

class figure_birds : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BIRDS, figure_birds)
    figure_birds(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_BIRDS, "birds"}; }
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};