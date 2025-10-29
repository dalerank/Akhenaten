#pragma once

#include "platform/renderer.h"
#include "autoconfig_window.h"

class scroll_list_panel;

namespace ui {
    struct display_options_window : public autoconfig_window_t<display_options_window> {
        using close_callback = void();

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void init() override {};
        virtual void archive_load(archive arch) override;

        void init(close_callback close_cb);

        static void show(close_callback close_cb);

    private:
        int focus_button_id;

        close_callback *_close_cb;
        vec2i original_resolution;
        vec2i selected_resolution;
        scroll_list_panel* panel = nullptr;
        int num_files_in_view;
        std::vector<video_mode> video_modes;
    };
}
