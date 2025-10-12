#pragma once

#include "figure_animal.h"

enum e_ostrich_action {
    ACTION_8_OSTRICH_RECALCULATE = 8,
    ACTION_10_OSTRICH_GOING = 10,
    ACTION_15_OSTRICH_TERRIFIED = 15,
    ACTION_16_OSTRICH_FLEEING = 16,
    ACTION_18_OSTRICH_ROOSTING = 18,
    ACTION_19_OSTRICH_IDLE = 19,
    ACTION_24_OSTRICH_SPAWNED = 24,
    ACTION_196_OSTRICH_AT_REST = 196
};

class figure_ostrich : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_OSTRICH, figure_ostrich)
    figure_ostrich(figure *f) : figure_impl(f) {}
    virtual figure_ostrich *dcast_ostrich() override { return this; }

    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_OSTRICH, "ostrich"}; }
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual bool play_die_sound() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};