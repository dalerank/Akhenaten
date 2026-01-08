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
int widget_top_menu_get_tooltip_text(tooltip_context* c);

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

    struct {
        int population = 0;
    } states;

    ui::widget headers;

    top_menu_widget_t() : autoconfig_window("top_menu_widget") {}

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
    void advisors_handle(menu_item &item);
    void help_handle(menu_item &item);
    void options_handle(menu_item &item);
    void set_text_for_debug_render();
    void set_text_for_debug_city();
    void set_text_for_autosave();
    void set_text_for_tooltips();
    void set_text_for_warnings();
    void item_update_text(pcstr path, pcstr text);
    void header_update_text(pcstr header, pcstr text);
    xstring menu_handle_mouse(const mouse *m, menu_header *menu, xstring &focus_item_id);
    xstring get_subitem(const mouse *m, menu_header &menu);
    void calculate_menu_dimensions(menu_header &menu);
    void debug_render_change_opt(menu_item &item);
    void debug_change_opt(menu_item &item);
    void debug_opt_text(int opt, bool v);
    void debug_render_text(int opt, const xstring name, bool v);


    void menu_item_update(pcstr header, int item, pcstr text);
    void update_date(event_advance_day);
    void update_finance(event_finance_changed ev);
};
ANK_CONFIG_STRUCT(top_menu_widget_t,
    headers, offset, item_height, background, spacing, offset_rotate_basic, sidebar_offset)