#pragma once

#include "SDL.h"

void platform_handle_key_down(SDL_KeyboardEvent* event);

void platform_handle_key_up(SDL_KeyboardEvent* event);

void platform_handle_text(SDL_TextInputEvent* event);