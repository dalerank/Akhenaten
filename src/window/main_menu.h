#pragma once

#include "window/autoconfig_window.h"

struct main_menu_screen : autoconfig_window_t<main_menu_screen> {
    virtual int get_tooltip_text() override { return 0; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {};

    static void show();
    static main_menu_screen &instance();
};

