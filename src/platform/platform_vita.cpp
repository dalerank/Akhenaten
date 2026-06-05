#include "platform.h"

#if defined(__vita__)

#include <SDL.h>

uint32_t platform_init_sdl_flags() {
    return SDL_INIT_JOYSTICK;
}

#endif
