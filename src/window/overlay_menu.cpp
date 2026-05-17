#include "overlay_menu.h"

#include "overlays/city_overlay.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "js/js_game.h"
#include "graphics/elements/ui.h"

struct overlay_submenu_t {
    xstring title;
    svector<e_overlay, 16> ids;
};
ANK_CONFIG_STRUCT(overlay_submenu_t, title, ids)

struct overlay_menu_t {
    svector<overlay_submenu_t, 16> menus;

    void archive_unload() { menus.clear(); }
    auto &emplace_back() { return menus.emplace_back(); }

    void archive_init() {
        assert(!menus.empty() && "Overlay menu not loaded!");
    }
};
ANK_CONFIG_STRUCT(overlay_menu_t, menus)

overlay_menu_t ANK_VARIABLE(overlay_menu);

struct overlay_menu_widget : public autoconfig_window_t<overlay_menu_widget> {
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
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

int overlay_menu_widget::ui_handle_mouse(const mouse *m) {
    const int r = autoconfig_window::ui_handle_mouse(m);

    return r;
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