#pragma once

#include "window/autoconfig_window.h"
#include "city/city_finance.h"
#include "game/simulation_time.h"

struct mouse;
struct hotkeys;
struct tooltip_context;

void widget_top_menu_clear_state();
void widget_top_menu_draw();
void widget_top_menu_handle_input(const mouse* m, const hotkeys* h);

struct top_menu_widget_t : autoconfig_window {
    int offset_rotate;
    int offset_rotate_basic;

    xstring open_sub_menu;
    xstring focus_menu_id;
    xstring focus_sub_menu_id;

    vec2i offset;
    int item_height;
    int spacing;
    int sidebar_offset;
    image_desc background;

    ui::widget headers;

    top_menu_widget_t() : autoconfig_window("top_menu_widget") {}

    virtual pcstr get_section() const override { return "top_menu_widget"; }
    virtual void archive_load(archive arch) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;
    virtual void on_mission_start() override;
    void draw_background_impl();
    void draw_elements_impl();
    void draw_rotate_buttons();
    xstring get_selected_header(const mouse *m);
    xstring bar_handle_mouse(const mouse *m);
    bool handle_input_submenu(const mouse *m, const hotkeys *h);
    void sub_menu_draw_foreground(int flags);
    void sub_menu_draw_background(int flags);
    void sub_menu_draw_text(const xstring header, const xstring focus_item_id);
    void sub_menu_init();
    void item_update_text(pcstr path, pcstr text);
    xstring menu_handle_mouse(const mouse *m, menu_header *menu, xstring &focus_item_id);
    xstring get_subitem(const mouse *m, menu_header &menu);
    void calculate_menu_dimensions(menu_header &menu);

    void menu_item_update(pcstr header, int item, pcstr text);
};
ANK_CONFIG_STRUCT(top_menu_widget_t,
    headers, offset, item_height, background, spacing, offset_rotate_basic, sidebar_offset)