#pragma once

#include "autoconfig_window.h"

namespace ui {
    struct window_dinasty_menu : public autoconfig_window_t<window_dinasty_menu> {
        bool to_begin_history;
        bool has_saved_games;
        pcstr last_autosave;

        bstring256 player_name;
        bstring256 player_name_title;

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void init() override;
    
        static void show();
    };
}

