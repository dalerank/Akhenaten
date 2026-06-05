#include "platform.h"

#if defined(__vita__)

#include <SDL.h>

uint32_t platform_init_sdl_flags() {
    return SDL_INIT_JOYSTICK;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

pcstr platform_request_initial_data_directory() {
    return nullptr;
}

#endif
