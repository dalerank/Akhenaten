#pragma once

#include "city/constants.h"

struct mouse;

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
bool is_advisor_available(int btn_id);
void window_advisors_draw_dialog_background(void);

void window_advisors_show(void);

void window_advisors_show_checked(void);

int window_advisors_show_advisor(e_advisor advisor);
