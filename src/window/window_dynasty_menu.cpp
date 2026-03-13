#include "window_dynasty_menu.h"

#include "window_city.h"
#include "player_selection.h"

#include "game/settings.h"
#include "game/player.h"
#include "graphics/window.h"
#include "input/input.h"

#include "graphics/elements/ui.h"

ui::window_dinasty_menu g_dinasty_menu;

void ui::window_dinasty_menu::init() {
    player_data_load((const uint8_t*)g_settings.player_name.c_str());
    autoconfig_window::init();
}

int ui::window_dinasty_menu::ui_handle_mouse(const mouse *m) {
    int result = autoconfig_window::ui_handle_mouse(m);
    if (result)
        return result;
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_player_selection_init();
        window_player_selection_show();
    }
    return 0;
}

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