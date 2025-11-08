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

struct inres_icon {
    pcstr name;
    void *data;
    int length;
};

static inres_icon inres_icons[] = {
    {"!discord", (void*)gDiscordIcon, (int)gDiscordIcon_length}
};

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

SDL_Texture *load_icon_texture(pcstr name, vec2i &size) {
    SDL_Surface *loadedSurface = nullptr;
    if (name && *name == '!') {
        auto it = std::find_if(std::begin(inres_icons), std::end(inres_icons), [name] (auto &it) { return strcmp(name, it.name) == 0; });
        if (it != std::end(inres_icons)) {
            return g_render.create_texture_from_png_buffer(it->data, it->length, size);
        }
    }
    
    auto data = internal_read_data(name);
    auto texture = g_render.create_texture_from_png_buffer((void*)data.first, data.second, size);

    return texture;
}

SDL_Surface *load_icon_surface(pcstr name, vec2i &size) {
    SDL_RWops *rw = nullptr;

    if (name && *name == '!') {
        auto it = std::find_if(std::begin(inres_icons), std::end(inres_icons), [name] (auto &it) { return strcmp(name, it.name) == 0; });
        if (it != std::end(inres_icons)) {
            rw = SDL_RWFromMem(it->data, it->length);
        }
    } else {
        auto data = internal_read_data(name);
        rw = SDL_RWFromMem((void *)data.first, data.second);
    }

    if (rw) {
        return IMG_LoadPNG_RW(rw);
    }

    return nullptr;
}