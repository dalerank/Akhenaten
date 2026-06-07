#pragma once

#include "window/autoconfig_window.h"

struct hotkeys;
struct mouse;
struct tooltip_context;

struct window_city : public autoconfig_window_t<window_city> {
    virtual int handle_mouse(const mouse *m) override;
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override;

    void init_city();
    void handle_input(const mouse *m, const hotkeys *h);

    static window_city &instance();
    static void show();
};

void window_city_draw_all();
void window_city_draw_panels();
void window_city_draw();
void window_city_draw_background(int);
void window_city_draw_foreground(int);
void window_city_draw_paused_and_time_left();
void window_city_show();
void window_city_handle_hotkeys(const hotkeys *h);

extern bool city_has_loaded;
