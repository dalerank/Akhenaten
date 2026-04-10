#pragma once

#include "autoconfig_window.h"

namespace ui {
    struct message_list_window : public autoconfig_window_t<message_list_window> {
        using close_callback = void();

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual void init() override;

        static void show(close_callback close_cb);

        close_callback *_close_cb;
    };
}