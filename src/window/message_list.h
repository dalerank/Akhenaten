#pragma once

#include "autoconfig_window.h"
#include "graphics/elements/scroll_list_panel.h"

namespace ui {
    struct message_list_window : public autoconfig_window_t<message_list_window> {
        using close_callback = void();

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void init() override;
        virtual void archive_load(archive arch) override;

        static void show(close_callback close_cb);

        void draw_message(int index, int flags, const scroll_list_panel::entry_data &entry, vec2i pos, e_font font);

        scroll_list_panel *panel = nullptr;
        close_callback *_close_cb;

        int num_messages_in_view;
    };
}