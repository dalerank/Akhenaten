#include "platform.h"

#if defined(GAME_PLATFORM_ANDROID)

#include "android/android.h"
#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>
#include <SDL_system.h>

uint32_t platform_init_sdl_flags() {
    return 0;
}

void platform_post_hint_init() {
    SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
}

void platform_setup_begin() {
    android_clear_startup_log();
    android_append_startup_log("Startup: setup()");
}

void platform_resolve_user_directory(bstring512& dir) {
    dir = SDL_AndroidGetExternalStoragePath();
}

void platform_t::open_url(pcstr url, pcstr prefix) {

}

pcstr platform_t::get_steam_path() {
    return "";
}

#endif
