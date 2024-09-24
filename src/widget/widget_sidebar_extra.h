#pragma once
#include "input/mouse.h"

enum {
    SIDEBAR_EXTRA_DISPLAY_NONE = 0,
    SIDEBAR_EXTRA_DISPLAY_GAME_SPEED = 1,
    SIDEBAR_EXTRA_DISPLAY_UNEMPLOYMENT = 2,
    SIDEBAR_EXTRA_DISPLAY_RATINGS = 4,
    SIDEBAR_EXTRA_DISPLAY_ALL = 7
};

int sidebar_extra_draw(vec2i offset);
int sidebar_extra_handle_mouse(const mouse* m);
