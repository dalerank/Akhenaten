#include "platform.h"
#include "js/js_game.h"
#include "core/bstring.h"

#include <SDL.h>

#include <filesystem>

void platform_resolve_user_directory(bstring512& dir);
uint32_t platform_init_sdl_flags();
void platform_post_hint_init();
void platform_setup_begin();
pcstr platform_request_initial_data_directory();

int platform_sdl_version_at_least(int major, int minor, int patch) {
    SDL_version v;
    SDL_GetVersion(&v);
    return SDL_VERSIONNUM(v.major, v.minor, v.patch) >= SDL_VERSIONNUM(major, minor, patch);
}

uint32_t platform_t::sdl_init_flags() {
    return platform_init_sdl_flags();
}

void platform_t::post_hint_init() {
    platform_post_hint_init();
}

void platform_t::setup_begin() {
    platform_setup_begin();
}

pcstr platform_t::request_initial_data_directory() {
    return platform_request_initial_data_directory();
}

bool platform_t::file_manager_should_case_correct_file() {
    const bool is_case_platform = !(is_windows() || is_android());
    return is_case_platform;
}

platform_t platform;

pcstr platform_t::user_directory() {
    static bstring512 udirectory;
    if (!udirectory.empty()) {
        return udirectory.c_str();
    }

    platform_resolve_user_directory(udirectory);

    std::error_code ec;
    std::filesystem::create_directories(udirectory.c_str(), ec);
    return udirectory.c_str();
}
