#include "platform.h"

#if defined(GAME_PLATFORM_NSWITCH)

#include "input/touch.h"
#include "platform/switch/switch_input.h"

#include <SDL.h>

uint32_t platform_init_sdl_flags() {
    return SDL_INIT_JOYSTICK;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

void platform_run_init_callback() {
    touch_set_mode(TOUCH_MODE_TOUCHPAD);
}

void platform_run_per_frame_callback() {
    platform_per_frame_callback();
}

int platform_poll_event(CoreEvent* event) {
    return switch_poll_event(reinterpret_cast<SDL_Event*>(event));
}

pcstr platform_request_initial_data_directory() {
    return nullptr;
}

#endif
