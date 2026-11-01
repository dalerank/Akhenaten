#pragma once

#include "figure/figure.h"

enum e_protestor_action {
    // Remake hunt (gameplay_change_protestor_hunt_nobles): wait → chase noble / noble house.
    ACTION_8_PROTESTOR_WAITING = 8,
    ACTION_9_PROTESTOR_HUNTING = 9,
};

class figure_protestor : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PROTESTER, figure_protestor)
    figure_protestor(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void update_animation() override;
};
