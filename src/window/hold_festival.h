#pragma once

#include "window/autoconfig_window.h"

namespace ui {
    struct hold_festival_window : public autoconfig_window_t<hold_festival_window> {
        std::function<void()> callback;
        bool background;

        using widget::load;

        void close();
        virtual int draw_background(UiFlags flags) override;
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual int get_tooltip_text() override { return 0; }
        virtual void init() override {}
        void get_tooltip(tooltip_context *c);
    };
}

void window_hold_festival_show(bool bg, std::function<void()> cb = nullptr);
