#include "platform.h"

#if defined(GAME_PLATFORM_LINUX)

#include "core/bstring.h"
#include "core/log.h"
#include "content/vfs.h"

#include <SDL.h>

void platform_t::open_url(pcstr url, pcstr prefix) {
    bstring256 command(prefix, "xdg-open '", url, "'");
    logs::info("%s", command);
    [[maybe_unused]] auto result = ::system(command.c_str());
}

#include <pwd.h>
#include <unistd.h>

pcstr platform_t::get_steam_path() {
    const passwd *pw = getpwuid(getuid());
    if (!pw || !pw->pw_dir) {
        return {};
    }

    vfs::path home_dir(pw->pw_dir);

    static vfs::path steam_path;
    steam_path.concat(home_dir.c_str(), "/.local/share/Steam");

    return steam_path.c_str();
}

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

bool platform_run_main_loop(platform_pump_frame_cb pump_frame, platform_should_continue_cb should_continue) {
    while (should_continue()) {
        pump_frame();
    }
    return true;
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

#endif