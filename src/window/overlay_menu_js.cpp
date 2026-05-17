#include "overlay_menu.h"

#include "core/profiler.h"
#include "graphics/view/view.h"
#include "js/js_game.h"
#include "game/game.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"

void __ui_window_overlay_menu_show() {
    window_overlay_menu_show();
}
ANK_FUNCTION(__ui_window_overlay_menu_show)

int __ui_overlay_menu_viewport_offset_x() {
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);
    return view_pos.x + view_size.x;
}
ANK_FUNCTION(__ui_overlay_menu_viewport_offset_x)

void __ui_window_city_draw_panels() {
    window_city_draw_panels();
}
ANK_FUNCTION(__ui_window_city_draw_panels)

void __ui_widget_sidebar_city_draw_foreground() {
    widget_sidebar_city_draw_foreground();
}
ANK_FUNCTION(__ui_widget_sidebar_city_draw_foreground)

void __ui_window_city_draw() {
    window_city_draw();
}
ANK_FUNCTION(__ui_window_city_draw)
