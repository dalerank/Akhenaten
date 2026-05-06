#pragma once

#include "graphics/elements/tooltip.h"
#include "input/hotkey.h"
#include "input/mouse.h"
#include "core/xfunction.h"

#include <array>

struct window_type {
    xstring id;
    xfunction <void(int)> draw_background;
    xfunction <void(int)> draw_foreground;
    xfunction <void(const mouse*, const hotkeys*)> handle_input;
    xfunction <void(tooltip_context*)> draw_tooltip;
    xfunction <void()> draw_refresh;
};

struct windows_manager_t {
    std::array<window_type, 6> window_queue;
    int queue_index;
    window_type *current_window;
    int underlying_windows_redrawing;

    void update_input_after();
    void handle_input(const mouse *m, const hotkeys *h);
    void handle_tooltip(const mouse *m);
    bool window_is(xstring id);

    static xstring window_city;
    static xstring window_main_menu;
};

extern windows_manager_t g_window_manager;

void window_draw(int force);

void window_draw_underlying_window(int);

void window_show(const window_type* window);

xstring window_get_id(void);

void window_go_back(void);
