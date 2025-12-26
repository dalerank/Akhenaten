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
    int selected_button = 0;
    int selected_city = 1;
    vec2i min_pos, max_pos;
    vec2i draw_offset;
    vec2i last_mouse_pos;
    int is_scrolling;
    int finished_scroll;
    int trade_column_spacing;
    int trade_row_spacing;
    int info_y_traded;
    int trade_button_offset_x;
    int info_y_city_desc;
    int trade_resource_size;
    const int sell_res_group = 47;
    int trade_button_offset_y;
    vec2i start_pos, finish_pos;
    image_desc image, bottom_image, horizontal_bar,
        vertical_bar, cross_bar, trade_amount,
        closed_trade_route_hl, open_trade_route, open_trade_route_hl;
    xstring hovered_object_tooltip;
    //svector<object_trade_info, 16> buying_goods;
    //svector<object_trade_info, 16> selling_goods;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    virtual void archive_load(archive arch) override;

    void draw_map();
    void draw_empire_object(const empire_object &obj);
    void draw_paneling();
    void clear_city_info();
    void draw_object_info();
    void draw_enemy_army_info(const empire_object *object);
    void draw_kingdome_army_info(const empire_object *object);
    void draw_city_want_sell(ui::element *e, UiFlags flags);
    void draw_city_want_buy(ui::element *e, UiFlags flags);
    void draw_city_selling(ui::element *e, UiFlags flags);
    void draw_city_buy(ui::element *e, UiFlags flags);
    bool is_outside_map(int x, int y);
    void determine_selected_object(const mouse *m);
    void draw_city_info(const empire_object *object);
    void draw_trade_resource(UiFlags flags, e_resource resource, int trade_now, int trade_max, vec2i offset, e_font font);
    void draw_trade_route(int route_id, e_empire_route_state effect);
    void draw_object_tooltip();
    void draw_tooltip(tooltip_context *c);
};


void window_empire_show();
void window_empire_show_checked();