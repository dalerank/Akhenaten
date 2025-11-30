#include "platform.h"
#include "js/js_game.h"
#include "core/log.h"

#include <SDL.h>

int platform_sdl_version_at_least(int major, int minor, int patch) {
    SDL_version v;
    SDL_GetVersion(&v);
    return SDL_VERSIONNUM(v.major, v.minor, v.patch) >= SDL_VERSIONNUM(major, minor, patch);
}

bool platform_t::file_manager_should_case_correct_file() {
    const bool is_case_platform = !(is_windows() || is_android());
    return is_case_platform;
}

platform_t platform;