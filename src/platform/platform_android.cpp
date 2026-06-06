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

void platform_run_init_callback() {
}

void platform_run_per_frame_callback() {
}

int platform_poll_event(CoreEvent* event) {
    return SDL_PollEvent(reinterpret_cast<SDL_Event*>(event));
}

pcstr platform_request_initial_data_directory() {
    android_append_startup_log("Startup: asking for data folder");
    pcstr initial_user_dir = android_show_pharaoh_path_dialog(false);
    if (!initial_user_dir || !*initial_user_dir) {
        android_append_startup_log("Startup: no folder selected");
        exit(-2);
    }
    android_append_startup_log("Startup: folder selected");
    return initial_user_dir;
}

void platform_append_startup_log(pcstr message) {
    android_append_startup_log(message);
}

void platform_hide_startup_log() {
    android_set_startup_log_visible(0);
}

bool platform_run_main_loop(platform_pump_frame_cb pump_frame, platform_should_continue_cb should_continue) {
    while (should_continue()) {
        pump_frame();
    }
    return true;
}

void platform_resolve_user_directory(bstring512& dir) {
    dir = SDL_AndroidGetExternalStoragePath();
}

void platform_t::open_url(pcstr url, pcstr prefix) {

}

pcstr platform_t::get_steam_path() {
    return "";
}

void platform_show_virtual_keyboard(const uint8_t *text, int max_length) {
    (void)text;
    (void)max_length;
    if (!SDL_IsTextInputActive()) {
        SDL_StartTextInput();
    }
}

void platform_hide_virtual_keyboard(void) {
    if (SDL_IsTextInputActive()) {
        SDL_StopTextInput();
    }
}

#endif
