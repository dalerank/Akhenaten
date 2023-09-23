#pragma once

struct SDL_Texture;
struct SDL_Surface;

SDL_Texture *load_icon_texture(const char *name);
SDL_Surface *load_icon_surface(const char *name);