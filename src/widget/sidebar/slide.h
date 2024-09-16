#pragma once

enum { SLIDE_DIRECTION_IN = 0, SLIDE_DIRECTION_OUT = 1 };

using back_sidebar_draw_function = void(int x_offset);
using front_sidebar_draw_function = void(int x_offset);
using slide_finished_function = void();

void sidebar_slide(int direction,
                   back_sidebar_draw_function back_sidebar_callback,
                   front_sidebar_draw_function front_sidebar_callback,
                   slide_finished_function finished_callback);
