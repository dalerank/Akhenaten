#include "platform.h"
#include "js/js_game.h"
#include "core/bstring.h"

#include <SDL.h>

#include <filesystem>

static_assert(sizeof(SDL_Event) <= sizeof(CoreEvent::storage),
              "CoreEvent storage is too small for SDL_Event");

void platform_resolve_user_directory(bstring512& dir);
uint32_t platform_init_sdl_flags();
void platform_post_hint_init();
void platform_setup_begin();
void platform_run_init_callback();
void platform_run_per_frame_callback();
int platform_poll_event(CoreEvent* event);
pcstr platform_request_initial_data_directory();
void platform_append_startup_log(pcstr message);
void platform_hide_startup_log();
bool platform_run_main_loop(platform_pump_frame_cb pump_frame, platform_should_continue_cb should_continue);
void platform_screen_warp_mouse(int *x, int *y);
void platform_show_virtual_keyboard(const uint8_t *text, int max_length);
void platform_hide_virtual_keyboard(void);

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

void platform_t::init_callback() {
    platform_run_init_callback();
}

void platform_t::per_frame_callback() {
    platform_run_per_frame_callback();
}

int platform_t::poll_event(CoreEvent* event) {
    return platform_poll_event(event);
}

pcstr platform_t::request_initial_data_directory() {
    return platform_request_initial_data_directory();
}

void platform_t::append_startup_log(pcstr message) {
    platform_append_startup_log(message);
}

void platform_t::hide_startup_log() {
    platform_hide_startup_log();
}

bool platform_t::run_main_loop(platform_pump_frame_cb pump_frame, platform_should_continue_cb should_continue) {
    return platform_run_main_loop(pump_frame, should_continue);
}

void platform_t::screen_warp_mouse(int *x, int *y) {
    platform_screen_warp_mouse(x, y);
}

void platform_t::show_virtual_keyboard(const uint8_t *text, int max_length) {
    platform_show_virtual_keyboard(text, max_length);
}

void platform_t::hide_virtual_keyboard() {
    platform_hide_virtual_keyboard();
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
