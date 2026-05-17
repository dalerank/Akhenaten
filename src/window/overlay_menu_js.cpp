#include "overlay_menu.h"

#include "core/profiler.h"
#include "graphics/view/view.h"
#include "js/js_game.h"
#include "game/game.h"

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
