#pragma once

#include "grid/point.h"
#include "city/city.h"
#include "core/variant.h"
#include "graphics/elements/ui.h"

struct object_info;
struct tooltip_context;

struct event_show_tile_info { tile2i tile; bool avoid_mouse; pcstr source_location; };
struct event_update_tile_info { bool avoid_mouse; };

struct common_info_window : public ui::widget {
    virtual pcstr section() const { return ""; }
    virtual bool check(object_info &c) { return false; }
    virtual vec2i bgsize() const;
    virtual void window_info_background(object_info &c) { update_buttons(c); }
    virtual void window_info_foreground(object_info &c);
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual textid get_tooltip(object_info &c) { return {0, 0}; }
    virtual void update_buttons(object_info &c);

    using widget::load;
    virtual void archive_load(archive arch) override;
    virtual void init(object_info &c);
    virtual void update(object_info &c) {}
    static object_info& get_object_info();

    void draw_tooltip(tooltip_context *c);

    svector<xstring, 8> open_sounds;

    static void register_handlers();
};

int window_building_info_get_type();
void window_building_info_show_storage_orders();

void window_building_register_handler(common_info_window *handler);
void window_figure_register_handler(common_info_window *handler);

// Recompute size/position of the currently open info window after resolution change.
void window_info_on_resolution_changed();