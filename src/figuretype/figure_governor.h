#pragma once

#include "figure/figure.h"

enum e_governor_action {
    ACTION_120_GOVERNOR_CREATED = 120,
    ACTION_121_GOVERNOR_MOVING = 121,
};

class figure_governor : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_GOVERNOR, figure_governor)
    figure_governor(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
};