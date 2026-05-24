#include "widget_top_menu_game.h"

#include "js/js_game.h"
#include "window/hotkey_config.h"
#include "graphics/window.h"
#include "graphics/screenshot.h"
#include "core/log.h"
#include "core/profiler.h"
#include "game/game.h"
#include "editor/tool.h"

pcstr __widget_top_menu_hotkeys_options(int, int) {
    window_hotkey_config_show([] {});
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_hotkeys_options)

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
