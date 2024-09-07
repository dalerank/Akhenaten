#pragma once

enum { SLIDE_DIRECTION_IN = 0, SLIDE_DIRECTION_OUT = 1 };

typedef void (*back_sidebar_draw_function)();
typedef back_sidebar_draw_function slide_finished_function;
typedef void (*front_sidebar_draw_function)(int x_offset);

void sidebar_slide(int direction,
                   back_sidebar_draw_function back_sidebar_callback,
                   front_sidebar_draw_function front_sidebar_callback,
                   slide_finished_function finished_callback);
