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
int main_menu_screen::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    g_render.clear_screen();
    return 0;
}

void main_menu_screen::show() {
    logs::info("[test-marker] main_menu_shown");
    sound_city_stop();
    sound_city_init();

    static window_type window = {
        "window_main_menu",
        [] (int flags) { instance().draw_background(flags); },
        [] (int flags) { instance().ui_draw_foreground(flags); },
        [] (auto m, auto h) { instance().ui_handle_mouse(m); },
    };

    instance().init();
    window_show(&window);
}

main_menu_screen &main_menu_screen::instance() {
    return g_main_menu;
}