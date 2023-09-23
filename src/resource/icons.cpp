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
#include "app_icon.h"

#if defined(GAME_PLATFORM_WIN)
#pragma warning ( pop )
#else
#pragma clang diagnostic pop
#endif

#include "platform/screen.h"
#include "platform/renderer.h"

#include <SDL.h>

#include <string.h>

SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src);

SDL_Texture *load_icon_texture(const char *name) {
    SDL_Surface *loadedSurface = nullptr;
    if (strcmp(name, "discord") == 0) {
        return graphics_renderer()->create_texture_from_png_buffer((void*)gDiscordIcon, gDiscordIcon_length);
    } else if (strcmp(name, "app") == 0) {
        return graphics_renderer()->create_texture_from_png_buffer((void*)gAppIcon, gAppIcon_length);
    }

    return nullptr;
}

SDL_Surface *load_icon_surface(const char *name) {
    SDL_RWops *rw = nullptr;
    if (strcmp(name, "discord") == 0) {
        rw = SDL_RWFromMem((void*)gDiscordIcon, gDiscordIcon_length);
    } else if (strcmp(name, "app") == 0) {
        rw = SDL_RWFromMem((void*)gAppIcon, gAppIcon_length);
    }

    if (rw) {
        return IMG_LoadPNG_RW(rw);
    }

    return nullptr;
}