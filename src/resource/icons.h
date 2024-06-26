#pragma once

#include "core/vec2i.h"

struct SDL_Texture;
struct SDL_Surface;

SDL_Texture *load_icon_texture(const char *name, vec2i &size);
SDL_Surface *load_icon_surface(const char *name, vec2i &size);