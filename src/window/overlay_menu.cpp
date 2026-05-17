#include "overlay_menu.h"

#include "graphics/window.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "graphics/elements/ui.h"

struct overlay_menu_widget : public autoconfig_window_t<overlay_menu_widget> {
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
};

overlay_menu_widget g_overlay_menu_widget;

void overlay_menu_widget::ui_draw_foreground(UiFlags flags) {
    window_city_draw_panels();
    widget_sidebar_city_draw_foreground();
    window_city_draw();
    autoconfig_window::ui_draw_foreground(flags);
}


void window_overlay_menu_show() {
    static window_type window = {
        "window_overlay_menu",
        [] (int flags) { g_overlay_menu_widget.draw_background(flags); },
        [] (int flags) { g_overlay_menu_widget.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_overlay_menu_widget.ui_handle_mouse(m); },
    };
    g_overlay_menu_widget.init();
    window_show(&window);
}