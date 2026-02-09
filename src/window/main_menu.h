#pragma once

#include "window/autoconfig_window.h"

struct main_menu_screen : autoconfig_window_t<main_menu_screen> {
    virtual int get_tooltip_text() override { return 0; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int draw_background(UiFlags flags) override;
    virtual void draw_foreground(UiFlags flags) override;
    virtual void on_resolution_changed_instance() override;
    virtual int ui_handle_mouse(const mouse *m) override;

    virtual void init() override;

    static void show(bool restart_music);
    static main_menu_screen &instance();

private:
    // Logical center of the main menu button column for the
    // initial resolution when the UI was loaded. We use this
    // as a stable anchor to keep the menu centered when the
    // game resolution changes at runtime.
    vec2i _base_center{0, 0};
    bool _base_center_initialized{false};
};

