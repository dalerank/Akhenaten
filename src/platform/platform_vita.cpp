#include "platform.h"

#if defined(__vita__)

#include "core/log.h"
#include "input/touch.h"
#include "platform/vita/vita_input.h"

#include <SDL.h>
#include <vita2d.h>

#include <cstdlib>

uint32_t platform_init_sdl_flags() {
    return SDL_INIT_JOYSTICK;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

void platform_run_init_callback() {
    if (!vita2d_init()) {
        logs::info("Exiting: vita2d init failed");
        exit(-1);
    }

    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
    touch_set_mode(TOUCH_MODE_TOUCHPAD);
}

void platform_run_per_frame_callback() {
    platform_per_frame_callback();
}

int platform_poll_event(CoreEvent* event) {
    return vita_poll_event(reinterpret_cast<SDL_Event*>(event));
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

void platform_show_virtual_keyboard(const uint8_t *text, int max_length) {
    vita_show_virtual_keyboard(text, max_length);
}

void platform_hide_virtual_keyboard(void) {
    vita_hide_virtual_keyboard();
}

#endif
