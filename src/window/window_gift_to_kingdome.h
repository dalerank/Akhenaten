#pragma once

#include "window/autoconfig_window.h"

namespace ui {

    struct gift_to_kingdome_window : public autoconfig_window_t<gift_to_kingdome_window> {
        int32_t selected_gift_size;

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;

        virtual void init() override;

        bool can_buy_gift(int size);
        void select_link(int new_gift);
        static void show();
    };
}

