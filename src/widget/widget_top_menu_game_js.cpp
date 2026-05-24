#include "widget_top_menu_game.h"

#include "js/js_game.h"
#include "window/hotkey_config.h"
#include "graphics/window.h"
#include "core/profiler.h"
#include "game/game.h"
#include "editor/tool.h"

pcstr __widget_top_menu_hotkeys_options(int, int) {
    window_hotkey_config_show([] {});
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_hotkeys_options)

ANK_FUNCTION(widget_top_menu_clear_state);

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
