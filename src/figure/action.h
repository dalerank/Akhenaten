#pragma once

#include <cstdint>

#include "core/tokenum.h"

using e_figure_action = uint16_t;

enum e_common_action {
    ACTION_0_COMMON_NONE = 0,
    ACTION_8_RECALCULATE = 8,

    // Sentinel for JS token range (covers ACTION_8). High ids stay unbound.
    ACTION_9_COMMON_MAX = 9,

    // Delivery boy / caravan donkey flee to exit when leader dies (Enhanced: gameplay_change_follower_runaway).
    FIGURE_ACTION_132_FOLLOWER_RUNAWAY = 132,
    FIGURE_ACTION_148_FLEEING = 148,
    FIGURE_ACTION_149_CORPSE = 149,
};
using e_common_action_tokens_t = token_holder<e_common_action, ACTION_0_COMMON_NONE, ACTION_9_COMMON_MAX>;
extern const e_common_action_tokens_t e_common_action_tokens;

enum e_roamer_action {
    ACTION_10_ROAMER_GOING = 10,
    ACTION_125_ROAMER_ROAMING = 125,
    ACTION_126_ROAMER_RETURNING = 126
};