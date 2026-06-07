#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "core/profiler.h"
#include "platform/platform.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "game/game.h"
#include "game/game_config.h"
#include "core/app.h"
#include "window/popup_dialog.h"
#include "window/file_dialog.h"
#include "window/window_city.h"
#include "sound/sound_city.h"
#include "io/gamestate/boilerplate.h"
#include "graphics/elements/ui_js.h"
#include "resource/icons.h"
#include "platform/renderer.h"

main_menu_screen g_main_menu;

void main_menu_screen::show() {
    logs::info("[test-marker] main_menu_shown");
    sound_city_stop();
    sound_city_init();

    static window_type window = {
        "window_main_menu",
        [] (int flags) { g_main_menu.draw_background(flags); },
        [] (int flags) { g_main_menu.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_main_menu.ui_handle_mouse(m); },
    };

    window_show(&window);
}

main_menu_screen &main_menu_screen::instance() {
    return g_main_menu;
}