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

    void update(int &x_offset, int expanded_offset_x, std::function<void()> callback);
};

struct sidebar_window_expanded_t : public autoconfig_window {
    int focus_tooltip_text_id;
    int x_offset;

    // static
    image_desc extra_block;
    image_desc relief_block;
    image_desc def_image;
    int extra_block_x;
    int expanded_offset_x;
    slide_driver slider;

    // dynamic
    int opened_menu;
    vec2i extra_block_size;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual pcstr get_section() const override { return "sidebar_window_expanded"; }

    virtual void archive_load(archive arch) override;
    virtual void init() override;

    void init_ui();
    void subscribe_events();

    void refresh_build_menu_buttons();
    void expand();
    void collapse();

    void draw_sidebar_extra(vec2i offset);

    sidebar_window_expanded_t() : autoconfig_window("sidebar_window_expanded") {}
};

struct sidebar_window_collapsed_t : public autoconfig_window {
    int focus_tooltip_text_id;
    int x_offset;

    // static
    image_desc extra_block;
    image_desc relief_block;
    int extra_block_x;
    int expanded_offset_x;
    slide_driver slider;

    // dynamic
    vec2i extra_block_size;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual pcstr get_section() const override { return "sidebar_window_collapsed"; }

    virtual void archive_load(archive arch) override;
    virtual void init() override;

    sidebar_window_collapsed_t() : autoconfig_window("sidebar_window_collapsed") {}

    void refresh_build_menu_buttons();

    void expand();
    void collapse();
};

struct sidebar_window {
};

} // namespace ui

ANK_CONFIG_STRUCT(ui::slide_driver, 
    deceleration_offset_x, slide_acceleration_millis, slide_speed_x)

ANK_CONFIG_STRUCT(ui::sidebar_window_expanded_t, 
    extra_block, relief_block, 
    extra_block_x, expanded_offset_x,
    def_image, slider)

ANK_CONFIG_STRUCT(ui::sidebar_window_collapsed_t,
    extra_block, relief_block,
    extra_block_x, expanded_offset_x,
    slider)

void widget_sidebar_city_init();
int widget_sidebar_city_offset_x();
int widget_sidebar_city_offset_max();
int widget_sidebar_city_collapsed_max();
int widget_sidebar_city_expanded_max();

void widget_sidebar_city_draw_foreground();
void widget_sidebar_city_draw_foreground_military();

int widget_sidebar_city_handle_mouse(const mouse* m);
int widget_sidebar_city_handle_mouse_build_menu(const mouse* m);
