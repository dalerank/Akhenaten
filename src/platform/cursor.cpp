#include "platform/cursor.h"

#include "core/app.h"
#include "input/mouse.h"
#include "platform/arguments.h"

#include "SDL.h"

color platform_cursor_t::color_for(char type) {
    for (const auto& entry : mouse_colors) {
        if (entry.type == type) {
            return entry.value;
        }
    }
    return ALPHA_TRANSPARENT;
}

void* platform_cursor_t::generate_cursor_surface(const char* data, int width, int height) {
    SDL_Surface* cursor_surface
      = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    color* pixels = (color*)cursor_surface->pixels;
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = color_for(data[i]);
    }
    return cursor_surface;
}

cursor_scale platform_cursor_t::scale_for(int scale_percentage) {
    if (scale_percentage <= 100)
        return CURSOR_SCALE_1;
    else if (scale_percentage <= 150)
        return CURSOR_SCALE_1_5;
    else {
        return CURSOR_SCALE_2;
    }
}

void platform_cursor_t::init(int scale_percentage) {
    cursor_scale cur_scale = scale_for(scale_percentage);
    for (int i = 0; i < CURSOR_MAX; i++) {
        const cursor* c = input_cursor_data((cursor_shape)i, cur_scale);
        surfaces[i] = generate_cursor_surface(c->data, c->width, c->height);
        cursors[i] = SDL_CreateColorCursor(static_cast<SDL_Surface*>(surfaces[i]), c->hotspot_x, c->hotspot_y);
    }
    set(current_id);
}

void platform_cursor_t::set(int cursor_id) {
    current_id = cursor_id;
    SDL_SetCursor(static_cast<SDL_Cursor*>(cursors[cursor_id]));
}

void mouse_set_cursor(int cursor_id) {
    xvalue<platform_cursor_t>::ref().set(cursor_id);
}

void ANK_REGISTER_APPLICATION_MODULE(register_platform_cursor_module) {
    xvalue<platform_cursor_t>::ref().init(g_args.get_cursor_scale_percentage());
}
