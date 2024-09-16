#pragma once

#include "window/autoconfig_window.h"

namespace ui {

struct sidebar_window_expanded : public autoconfig_window_t<sidebar_window_expanded> {
    int focus_tooltip_text_id;
    int x_offset;

    image_desc extra_block;
    vec2i extra_block_size;
    int extra_block_x;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground() override {}
    virtual void ui_draw_foreground() override;
    virtual int draw_background() override { return 0; }

    virtual void load(archive arch, pcstr section) override;
    virtual void init() override;

    void draw_overlay_text();
    void draw_buttons_expanded();
    void draw_number_of_messages();
    void refresh_build_menu_buttons();
};

struct sidebar_window_collapsed : public autoconfig_window_t<sidebar_window_collapsed> {
    int focus_tooltip_text_id;
    int x_offset;

    image_desc extra_block;
    vec2i extra_block_size;
    int extra_block_x;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground() override {}
    virtual void ui_draw_foreground() override;
    virtual int draw_background() override { return 0; }

    virtual void load(archive arch, pcstr section) override;
    virtual void init() override;

    void refresh_build_menu_buttons();
};

struct sidebar_window {
};

}

void widget_sidebar_city_init();

void widget_sidebar_city_draw_foreground();
void widget_sidebar_city_draw_foreground_military();

int widget_sidebar_city_handle_mouse(const mouse* m);
int widget_sidebar_city_handle_mouse_build_menu(const mouse* m);

int widget_sidebar_city_get_tooltip_text();

void widget_sidebar_city_release_build_buttons();