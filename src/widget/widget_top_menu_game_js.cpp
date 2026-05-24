#include "widget_top_menu_game.h"

#include "js/js_game.h"
#include "window/popup_dialog.h"
#include "window/window_city.h"
#include "window/file_dialog_save.h"
#include "window/file_dialog_delete.h"
#include "window/main_menu.h"
#include "window/autoconfig_window.h"
#include "window/hotkey_config.h"
#include "window/message_dialog_new.h"
#include "graphics/window.h"
#include "graphics/screenshot.h"
#include "core/log.h"
#include "core/profiler.h"
#include "game/game.h"
#include "editor/tool.h"

pcstr __widget_top_menu_save_map(int, int) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_save_show(FILE_TYPE_SAVED_GAME);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_save_map)

pcstr __widget_top_menu_delete_map(int, int) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_delete_show(FILE_TYPE_SAVED_GAME);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_delete_map)

pcstr __widget_top_menu_exit_game(int, int) {
    widget_top_menu_clear_state();
    popup_dialog::show_yesno("#popup_dialog_quit", [] (bool accepted) {
        if (accepted) {
            widget_top_menu_clear_state();
            main_menu_screen::show(/*restart_music*/true);
        } else {
            window_city_show();
        }
    });

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_exit_game)

pcstr __widget_top_menu_hotkeys_options(int, int) {
    window_hotkey_config_show([] {});
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_hotkeys_options)

pcstr __widget_top_menu_features(int, int) {
    autoconfig_window::show("window_features");
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_features)

pcstr __widget_top_menu_show_help(int, int) {
    logs::info("__widget_top_menu_show_help invoked");
    widget_top_menu_clear_state();
    window_go_back();
    window_message_dialog_show("message_dialog_help", -1, window_city_draw_all);
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_show_help)

pcstr __widget_top_menu_show_about(int, int) {
    widget_top_menu_clear_state();
    window_go_back();
    window_message_dialog_show("message_dialog_about", -1, window_city_draw_all);
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_show_about)

ANK_FUNCTION(widget_top_menu_clear_state);

void __game_make_screenshot(int mode) {
    widget_top_menu_clear_state();
    window_go_back();
    graphics_save_screenshot(mode ? SCREENSHOT_FULL_CITY : SCREENSHOT_DISPLAY);
}
ANK_FUNCTION_1(__game_make_screenshot)

pcstr __widget_top_menu_toggle_debug_properties(int, int) {
    game.debug_properties = !game.debug_properties;
    widget_top_menu_clear_state();
    window_go_back();
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_toggle_debug_properties)

pcstr __widget_top_menu_toggle_debug_terrain_paint(int, int) {
    game.debug_terrain_paint = !game.debug_terrain_paint;
    if (!game.debug_terrain_paint) {
        editor_tool_deactivate();
    }
    widget_top_menu_clear_state();
    window_go_back();
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_toggle_debug_terrain_paint)
