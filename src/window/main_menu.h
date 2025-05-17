#pragma once

#include "window/autoconfig_window.h"

struct main_menu_screen : autoconfig_window_t<main_menu_screen> {
    virtual int get_tooltip_text() override { return 0; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;

    virtual void init() override;

    static void show(bool restart_music);
    static main_menu_screen &instance();
};

