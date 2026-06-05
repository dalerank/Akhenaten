#include "platform.h"

#if defined(GAME_PLATFORM_BROWSER)

#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>
#include <emscripten/emscripten.h>

namespace {
platform_pump_frame_cb g_emscripten_pump_frame;

void emscripten_main_loop() {
    if (g_emscripten_pump_frame) {
        g_emscripten_pump_frame();
    }
}
} // namespace

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
    (void)should_continue;
    g_emscripten_pump_frame = pump_frame;
    emscripten_set_main_loop(emscripten_main_loop, 0, 1);
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

void platform_t::open_url(pcstr url, pcstr prefix) {

}

pcstr platform_t::get_steam_path() {
    return "";
}

#endif