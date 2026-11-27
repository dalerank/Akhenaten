#pragma once

#include "core/vec2i.h"
#include "core/xstring.h"

struct SDL_Texture;
struct SDL_Surface;

SDL_Texture *load_icon_texture(const char *name, vec2i &size);
SDL_Surface* load_icon_surface(const char* name, vec2i& size);
SDL_Texture* icon_texture_by_name(const xstring& name);
void icon_textures_forget();
