#pragma once 

#include "window/autoconfig_window.h"

struct set_salary_window : public autoconfig_window_t<set_salary_window> {
    using close_callback_t = std::function<void()>;

    close_callback_t close_callback;
    bool show_background;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    void close();

    static void show(close_callback_t cb, bool show_bt);
};

