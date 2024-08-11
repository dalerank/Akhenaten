#pragma once

#include "grid/point.h"
#include "graphics/elements/ui.h"

struct object_info;
struct tooltip_context;

struct common_info_window : public ui::widget {
    common_info_window();

    virtual bool check(object_info &c) { return false; }
    virtual int get_height_id(object_info &c) { return 0; }
    virtual void window_info_background(object_info &c);
    virtual void window_info_foreground(object_info &c) { draw(); }
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual std::pair<int, int> get_tooltip(object_info &c) { return {0, 0}; }
    virtual void update_buttons(object_info &c);

    void draw_tooltip(tooltip_context *c);
    widget &ui;
};

void window_building_info_show(const tile2i& point);
int window_building_info_get_type();
void window_building_info_show_storage_orders();
void window_info_register_handler(common_info_window *handler);