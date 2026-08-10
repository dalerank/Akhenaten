#include "platform/cursor.h"

#include "core/app.h"
#include "input/mouse.h"
#include "graphics/color.h"
#include "platform/arguments.h"
#include "switch.h"

#include "SDL.h"

#define CURSOR_SIZE 32

extern struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} SDL;

namespace {
switch_cursor cursors[CURSOR_MAX];

SDL_Texture* init_cursor(const cursor* c) {
    SDL_Texture* tex
      = SDL_CreateTexture(SDL.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, CURSOR_SIZE, CURSOR_SIZE);

    uint32_t pixels[CURSOR_SIZE * CURSOR_SIZE] = {0};

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            switch (c->data[y * c->width + x]) {
            case '#':
                pixels[y * CURSOR_SIZE + x] = ALPHA_OPAQUE | COLOR_BLACK;
                break;
            case '\'':
                pixels[y * CURSOR_SIZE + x] = ALPHA_OPAQUE | COLOR_WHITE;
                break;
            case ' ':
                pixels[y * CURSOR_SIZE + x] = ALPHA_TRANSPARENT;
                break;
            }
        }
    }

    SDL_UpdateTexture(tex, NULL, pixels, CURSOR_SIZE * 4);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

    return tex;
}
} // namespace

switch_cursor* current_cursor;

cursor_scale platform_cursor_t::scale_for(int /*scale_percentage*/) {
    return CURSOR_SCALE_1;
}

void platform_cursor_t::init(int /*scale_percentage*/) {
    for (int i = 0; i < CURSOR_MAX; i++) {
        const cursor* c = input_cursor_data((cursor_shape)i, CURSOR_SCALE_1);
        cursors[i].texture = init_cursor(c);
        cursors[i].hotspot_x = c->hotspot_x;
        cursors[i].hotspot_y = c->hotspot_y;
    }
    set(CURSOR_ARROW);
}

void platform_cursor_t::set(int cursor_id) {
    current_id = cursor_id;
    current_cursor = &cursors[cursor_id];
}

void mouse_set_cursor(int cursor_id) {
    xvalue<platform_cursor_t>::ref().set(cursor_id);
}

void ANK_REGISTER_APPLICATION_MODULE(register_platform_cursor_module) {
    xvalue<platform_cursor_t>::ref().init(g_args.get_cursor_scale_percentage());
}
