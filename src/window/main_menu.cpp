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
#include "sound/sound.h"
#include "sound/sound_city.h"
#include "io/gamestate/boilerplate.h"
#include "graphics/elements/ui_js.h"
#include "resource/icons.h"
#include "platform/renderer.h"
#include "js/js_game.h"

#ifdef GAME_PLATFORM_WIN
#include <windows.h>
#endif

main_menu_screen g_main_menu;

void __game_download_latest_version() {
#ifdef GAME_PLATFORM_WIN
    game.mt.detach_task([] () {
        ShellExecuteA(0, "Open", "update_binary_windows.cmd", 0, 0, SW_SHOW);
    });
#endif // GAME_PLATFORM_WIN
}
ANK_FUNCTION(__game_download_latest_version)

int main_menu_screen::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    g_render.clear_screen();
    return 0;
}

void main_menu_screen::draw_foreground(UiFlags flags) {
    ui.begin_frame();
    ui.draw();
}

void main_menu_screen::init() {
    autoconfig_window::init();
}

void main_menu_screen::show(bool restart_music) {
    logs::info("[test-marker] main_menu_shown");
    sound_city_stop();
    sound_city_init();
    if (restart_music) {
        g_sound.play_intro();
    }

    static window_type window = {
        "window_main_menu",
        [] (int flags) { instance().draw_background(flags); },
        [] (int flags) { instance().draw_foreground(flags); },
        [] (auto m, auto h) { instance().ui_handle_mouse(m); },
    };

    instance().init();
    window_show(&window);
}

main_menu_screen &main_menu_screen::instance() {
    return g_main_menu;
}