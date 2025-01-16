#pragma once

#include "autoconfig_window.h"

namespace ui {

    struct window_mission_end : public autoconfig_window_t<window_mission_end> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }

        autoconfig_window &getui();

        virtual void init() override {};
    };

    struct window_mission_won : public autoconfig_window_t<window_mission_won> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }
        virtual void init() override;

        void advance_to_next_mission();
    };

    struct window_mission_lost : public autoconfig_window_t<window_mission_lost> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }

        virtual void init() override;
    };

}

void window_mission_end_show_won(void);
void window_mission_end_show_fired(void);
