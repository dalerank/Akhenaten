#include "icons.h"
#include "platform/platform.h"

#if defined(GAME_PLATFORM_WIN)
#pragma warning( push )
#pragma warning( disable : 4838 )
#pragma warning( disable : 4309 )
#else
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnarrowing"
#endif

#include "discord_icon.h"

#if defined(GAME_PLATFORM_WIN)
#pragma warning ( pop )
#else
#pragma clang diagnostic pop
#endif

#include "platform/screen.h"
#include "platform/renderer.h"

#include <SDL.h>

#include <string.h>

SDL_Texture *load_icon(const char *name) {
    SDL_Surface *loadedSurface = nullptr;
    if (strcmp(name, "discord") == 0) {
        return graphics_renderer()->create_texture_from_png_buffer((void*)gDiscordIcon, gDiscordIcon_length);
    }

    return nullptr;
}