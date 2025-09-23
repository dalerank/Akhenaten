#pragma once

#include "window/autoconfig_window.h"
#include "core/speed.h"

namespace ui {

struct slide_driver {
    enum e_slide_mode {
        e_slide_none = 0,
        e_slide_collapse = 1,
        e_slide_expand = 2,
    };

    int deceleration_offset_x;
    int slide_acceleration_millis;
    e_slide_mode slide_mode = e_slide_none;
    speed_type slide_speed;
    int slide_speed_x;
    int position;

    void archive_load(archive arch);
    void update(int &x_offset, int expanded_offset_x, std::function<void()> callback);
};

struct sidebar_window_expanded : public autoconfig_window_t<sidebar_window_expanded> {
    int focus_tooltip_text_id;
    int x_offset;

    image_desc extra_block;
    image_desc relief_block;
    image_desc def_image;
    vec2i extra_block_size;
    int extra_block_x;
    int expanded_offset_x;
    int opened_menu;
    slide_driver slider;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;

    virtual void load(archive arch, pcstr section) override;
    virtual void init() override;

    void init_ui();
    void subscribe_events();

    void refresh_build_menu_buttons();
    void expand();
    void collapse();

    void draw_sidebar_extra(vec2i offset);
};

struct sidebar_window_collapsed : public autoconfig_window_t<sidebar_window_collapsed> {
    int focus_tooltip_text_id;
    int x_offset;

    image_desc extra_block;
    image_desc relief_block;
    vec2i extra_block_size;
    int extra_block_x;
    int expanded_offset_x;
    slide_driver slider;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;

    virtual void load(archive arch, pcstr section) override;
    virtual void init() override;

    void refresh_build_menu_buttons();

    void expand();
    void collapse();
};

struct sidebar_window {
};

}

void widget_sidebar_city_init();
int widget_sidebar_city_offset_x();
int widget_sidebar_city_offset_max();
int widget_sidebar_city_collapsed_max();
int widget_sidebar_city_expanded_max();

void widget_sidebar_city_draw_foreground();
void widget_sidebar_city_draw_foreground_military();

int widget_sidebar_city_handle_mouse(const mouse* m);
int widget_sidebar_city_handle_mouse_build_menu(const mouse* m);
