#include "window_dynasty_menu.h"

#include "window_city.h"
#include "player_selection.h"

#include "graphics/window.h"
#include "input/input.h"
#include "graphics/elements/ui_js.h"
#include "js/js_struct.h"

ui::window_dinasty_menu g_dinasty_menu;

void ui::window_dinasty_menu::show() {
    static window_type window = {
        WINDOW_GAME_SELECTION,
        [] (int flags) { g_dinasty_menu.draw_background(flags); },
        [] (int flags) { g_dinasty_menu.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_dinasty_menu.ui_handle_mouse(m); }
    };
    g_dinasty_menu.init();
    window_show(&window);
}