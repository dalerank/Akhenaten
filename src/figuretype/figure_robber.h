#pragma once

#include "figure/figure.h"

enum e_robber_action {
    // OG FIG_THIEF (figure_criminal_action): wait → route to rich building → steal → die.
    ACTION_8_ROBBER_WAITING = 8,
    ACTION_9_ROBBER_GOING_TO_ROB = 9,
    ACTION_10_ROBBER_FLEEING = 10,
    // Remake (Enhanced: gameplay_change_robber_remake).
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
    virtual void update_animation() override;

    static void create(building *b);
};
