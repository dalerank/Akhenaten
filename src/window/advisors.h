#ifndef WINDOW_ADVISORS_H
#define WINDOW_ADVISORS_H

#include "city/constants.h"
#include "input/mouse.h"

struct advisor_window_type {
    /**
     * @return height of the advisor in blocks of 16px
     */
    int (*draw_background)(void);
    void (*draw_foreground)(void);
    int (*handle_mouse)(const mouse* m);
    int (*get_tooltip_text)(void);
};

int window_advisors_get_advisor(void);

void window_advisors_draw_dialog_background(void);

void window_advisors_show(void);

void window_advisors_show_checked(void);

int window_advisors_show_advisor(int advisor);

#endif // WINDOW_ADVISORS_H
