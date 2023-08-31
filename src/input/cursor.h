#ifndef INPUT_CURSOR_H
#define INPUT_CURSOR_H

#include "graphics/window.h"

enum cursor_shape {
    CURSOR_ARROW = 0,
    CURSOR_SHOVEL = 1,
    CURSOR_SWORD = 2,
    CURSOR_MAX,
};

enum cursor_scale {
    CURSOR_SCALE_1 = 0,
    CURSOR_SCALE_1_5 = 1,
    CURSOR_SCALE_2 = 2,
};

struct cursor {
    int hotspot_x;
    int hotspot_y;
    int width;
    int height;
    const char* data;
};

const cursor* input_cursor_data(cursor_shape cursor_id, cursor_scale scale);

void input_cursor_update(e_window_id window);

#endif // INPUT_CURSOR_H
