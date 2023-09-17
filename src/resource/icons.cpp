#include "icons.h"

#include "discord_icon.h"
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