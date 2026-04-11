#pragma once

#include "window/autoconfig_window.h"

namespace ui {
    struct hold_festival_window : public autoconfig_window_t<hold_festival_window> {
        std::function<void()> callback;
        bool background;

        using widget::load;

        void close();
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }

        static void show(bool bg, std::function<void()> cb = nullptr);
    };
}

