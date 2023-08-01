#pragma once

enum e_direction {
    DIR_0_TOP_RIGHT = 0,
    DIR_1_RIGHT = 1,
    DIR_2_BOTTOM_RIGHT = 2,
    DIR_3_BOTTOM = 3,
    DIR_4_BOTTOM_LEFT = 4,
    DIR_5_LEFT = 5,
    DIR_6_TOP_LEFT = 6,
    DIR_7_TOP = 7,
    DIR_8_NONE = 8,
    DIR_FIGURE_NONE = 8, // DIR_FIGURE_NONE = 8,
    DIR_FIGURE_REROUTE = 9,
    DIR_FIGURE_CAN_NOT_REACH = 10,
    DIR_FIGURE_ATTACK = 11,
};
