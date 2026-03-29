#pragma once

#include "window/autoconfig_window.h"

enum e_empire_route_state {
    ROUTE_CLOSED = 0,
    ROUTE_CLOSED_SELECTED = 1,
    ROUTE_OPEN = 2,
    ROUTE_OPEN_SELECTED = 3,
};

struct empire_object;

struct empire_window : public autoconfig_window_t<empire_window> {
    vec2i min_pos, max_pos;
    vec2i draw_offset;
    vec2i last_mouse_pos;
    int is_scrolling;
    int finished_scroll;
    const int sell_res_group = 47;
    vec2i start_pos, finish_pos;
    image_desc image, horizontal_bar,
        cross_bar, trade_amount,
        closed_trade_route_hl, open_trade_route, open_trade_route_hl;
    xstring hovered_object_tooltip;

    /** Filled in draw_empire_object, drawn last in draw_map (above other routes and map overlays). */
    int deferred_selected_trade_route_id = -1;
    e_empire_route_state deferred_selected_trade_route_state = ROUTE_CLOSED;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    virtual void archive_load(archive arch) override;

    void draw_map();
    void draw_empire_object(int object_index, const empire_object &obj);
    void draw_paneling();
    void draw_object_info();
    bool is_outside_map(int x, int y);
    void determine_selected_object(const mouse *m);
    void draw_trade_route(int route_id, e_empire_route_state effect);
    void draw_distant_battle_path();
    void draw_object_tooltip();
    void draw_tooltip(tooltip_context *c);
};


void window_empire_show();
void window_empire_show_checked();