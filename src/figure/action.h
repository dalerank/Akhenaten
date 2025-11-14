#pragma once

#include <cstdint>

using e_figure_action = uint16_t;

enum e_common_action {
    ACTION_8_RECALCULATE = 8,

    FIGURE_ACTION_148_FLEEING = 148,
    FIGURE_ACTION_149_CORPSE = 149,
    FIGURE_ACTION_150_ATTACK = 150,
};

enum e_roamer_action {
    ACTION_10_ROAMER_GOING = 10,
    ACTION_125_ROAMER_ROAMING = 125,
    ACTION_126_ROAMER_RETURNING = 126
};