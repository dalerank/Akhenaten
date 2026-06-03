#include "core/app.h"
#include "game/game.h"
#include "js/js_game.h"

#ifdef GAME_PLATFORM_WIN
#include <windows.h>
#endif

struct app_updater_module_t {
    void download_latest_version();
};

void app_updater_module_t::download_latest_version() {
#ifdef GAME_PLATFORM_WIN
    game.mt.detach_task([]() {
        ShellExecuteA(0, "Open", "update_binary_windows.cmd", 0, 0, SW_SHOW);
    });
#endif
}

void __game_download_latest_version() {
    static app_updater_module_t mod;
    mod.download_latest_version();
}
ANK_FUNCTION(__game_download_latest_version)

void ANK_REGISTER_APPLICATION_MODULE(register_app_updater_module) {
}
