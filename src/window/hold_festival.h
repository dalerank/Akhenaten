#pragma once

#include "graphics/elements/ui.h"

namespace ui {
    struct hold_festival_window : public widget {
        std::function<void()> callback;
        bool background;

        using widget::load;

        void close();
        void draw_background();
        void handle_input(const mouse *m, const hotkeys *h);
        void get_tooltip(tooltip_context *c);
    };
}

void window_hold_festival_show(bool bg, std::function<void()> cb = nullptr);
