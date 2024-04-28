#pragma once

#include "city/constants.h"
#include "graphics/elements/ui.h"

struct mouse;

struct advisor_window : public ui::widget {
    virtual int draw_background() = 0;
    virtual void draw_foreground() = 0;
    virtual int handle_mouse(const mouse *m) = 0;
    virtual int get_tooltip_text() = 0;
    virtual void init() = 0;
};

int window_advisors_get_advisor();
bool is_advisor_available(int btn_id);
void window_advisors_draw_dialog_background();
void window_advisors_show();
void window_advisors_show_checked();
int window_advisors_show_advisor(e_advisor advisor);
