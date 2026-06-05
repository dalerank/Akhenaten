#include "platform.h"

#if defined(GAME_PLATFORM_NSWITCH)

#include <SDL.h>

uint32_t platform_init_sdl_flags() {
    return SDL_INIT_JOYSTICK;
}

void platform_post_hint_init() {
}

void platform_setup_begin() {
}

#endif
