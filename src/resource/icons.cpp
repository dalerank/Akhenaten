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
#include "cmrc/cmrc.hpp"

CMRC_DECLARE(akhenaten);

#include <SDL.h>
#include <string.h>
#include <assert.h>

SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src);
constexpr pcstr internal_res_path = "res/";

std::pair<void *, uint32_t> internal_read_data(pcstr path) {
    if (!path || !*path) {
        return {nullptr, 0};
    }

    auto fs = cmrc::akhenaten::get_filesystem();

    bstring256 fs_path(internal_res_path, (*path == ':') ? (path + 1) : path);
    if (!fs.exists(fs_path.c_str())) {
        return {nullptr, 0};
    }

    auto fd1 = fs.open(fs_path.c_str());
    return {(void*)fd1.begin(), (uint32_t)fd1.size()};
}

SDL_Texture *load_icon_texture(const char *name) {
    SDL_Surface *loadedSurface = nullptr;
    if (strcmp(name, "discord") == 0) {
        return graphics_renderer()->create_texture_from_png_buffer((void*)gDiscordIcon, gDiscordIcon_length);
    }
    
    auto data = internal_read_data(name);
    return graphics_renderer()->create_texture_from_png_buffer((void*)data.first, data.second);
}

SDL_Surface *load_icon_surface(const char *name) {
    SDL_RWops *rw = nullptr;
    if (strcmp(name, "discord") == 0) {
        rw = SDL_RWFromMem((void*)gDiscordIcon, gDiscordIcon_length);
    } else {
        auto data = internal_read_data(name);
        rw = SDL_RWFromMem((void *)data.first, data.second);
    }

    if (rw) {
        return IMG_LoadPNG_RW(rw);
    }

    return nullptr;
}