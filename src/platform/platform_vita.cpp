#include "platform.h"

#if defined(__vita__)

#include "core/log.h"
#include "input/touch.h"

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

pcstr platform_request_initial_data_directory() {
    return nullptr;
}

#endif
