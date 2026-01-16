#pragma once

#include "window/autoconfig_window.h"

struct speed_options_window : public autoconfig_window_t<speed_options_window> {
    using close_callback_t = std::function<void()>;

    virtual int handle_mouse(const mouse *m) override;
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    static void show(close_callback_t cb);
};
