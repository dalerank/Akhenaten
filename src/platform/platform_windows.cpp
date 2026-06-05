#include "platform.h"

#if defined(GAME_PLATFORM_WIN)

#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>

#include "windows.h"
#include "content/vfs.h"

uint32_t platform_init_sdl_flags() {
    return 0;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

void platform_run_init_callback() {
}

void platform_run_per_frame_callback() {
}

int platform_poll_event(CoreEvent* event) {
    return SDL_PollEvent(reinterpret_cast<SDL_Event*>(event));
}

pcstr platform_request_initial_data_directory() {
    return nullptr;
}

void platform_append_startup_log(pcstr message) {
}

void platform_hide_startup_log() {
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
    ShellExecuteA(0, "Open", url, 0, 0, SW_SHOW);
}

#include <ShlObj.h>

pcstr platform_t::get_steam_path() {
    DWORD dwType = REG_SZ;
    HKEY hKey = 0;
    char value[1024] = { 0 };
    DWORD value_length = 1024;
    RegOpenKeyA(HKEY_CURRENT_USER, "SOFTWARE\\Valve\\Steam", &hKey);
    RegQueryValueExA(hKey, "SteamPath", NULL, &dwType, (LPBYTE)&value, &value_length);

    static vfs::path steam_path;
    steam_path = value;

    return steam_path.c_str();
};

#endif