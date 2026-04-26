#pragma once

#include "autoconfig_window.h"

namespace ui {
    struct message_list_window : public autoconfig_window_t<message_list_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}

        static void show();
    };
}