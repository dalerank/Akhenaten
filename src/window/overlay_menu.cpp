#include "overlay_menu.h"

#include "graphics/window.h"
#include "graphics/elements/ui.h"
#include "window/autoconfig_window.h"

struct overlay_menu_widget : public autoconfig_window_t<overlay_menu_widget> {
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual bool is_modal() const override { return true; }
};

overlay_menu_widget g_overlay_menu_widget;

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