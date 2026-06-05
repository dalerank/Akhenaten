#include "platform.h"

#if defined(GAME_PLATFORM_BROWSER)

#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>

uint32_t platform_init_sdl_flags() {
    return 0;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

void platform_run_init_callback() {
}

pcstr platform_request_initial_data_directory() {
    return nullptr;
}

void platform_resolve_user_directory(bstring512& dir) {
    char* pref = SDL_GetPrefPath("", "Akhenaten");
    if (pref) {
        dir = pref;
        SDL_free(pref);
    } else {
        logs::warn("platform::user_directory: SDL_GetPrefPath failed, using cwd");
        dir = ".";
    }
}

void platform_t::open_url(pcstr url, pcstr prefix) {

}

pcstr platform_t::get_steam_path() {
    return "";
}

#endif