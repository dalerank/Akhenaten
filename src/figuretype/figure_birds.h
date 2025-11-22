#pragma once

#include "figure_animal.h"

enum e_birds_action {
    ACTION_8_BIRDS_RECALCULATE = 8,
    ACTION_10_BIRDS_GOING = 10,
    ACTION_16_BIRDS_FLEEING = 16,
    ACTION_15_BIRDS_TERRIFIED = 15,
    ACTION_18_BIRDS_ROOSTING = 18,
    ACTION_24_BIRDS_SPAWNED = 24,
};

class figure_birds : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_BIRDS, figure_birds)
    figure_birds(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;

    virtual sound_key phrase_key() const override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};