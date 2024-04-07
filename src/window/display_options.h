#pragma once

#include "platform/renderer.h"
#include "graphics/elements/ui.h"

struct scroll_list_panel;

namespace ui {
    struct window_display_options {
        using close_callback = void();

        void show(close_callback close_cb);
        void init(close_callback close_cb);
        void draw_foreground();
        void handle_input(const mouse *m, const hotkeys *h);

    private:
        int focus_button_id;

        close_callback *_close_cb;
        vec2i original_resolution;
        vec2i selected_resolution;
        scroll_list_panel* panel = nullptr;
        std::vector<video_mode> video_modes;
        
    public:
        static window_display_options window;
    };
}
