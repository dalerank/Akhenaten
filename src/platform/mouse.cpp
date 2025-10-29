#include "input/mouse.h"
#include "game/system.h"
#include "platform/screen.h"

#include <SDL_mouse.h>

struct mouse_data_t {
    int x;
    int y;
    int enabled;
};

mouse_data_t g_mouse_data;

void system_mouse_get_relative_state(int* x, int* y) {
    SDL_GetRelativeMouseState(x, y);
}

void system_mouse_set_relative_mode(int enabled) {
    auto &data = g_mouse_data;
    if (enabled == data.enabled)
        return;

    if (enabled) {
        SDL_GetMouseState(&data.x, &data.y);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        // Discard the first value, which is incorrect
        // (the first one gives the relative position to center of window)
        system_mouse_get_relative_state(NULL, NULL);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        system_set_mouse_position(&data.x, &data.y);
        mouse::ref().set_position({ data.x, data.y });
    }
    data.enabled = enabled;
}

void system_move_mouse_cursor(int delta_x, int delta_y) {
    int x = mouse::get().x + delta_x;
    int y = mouse::get().y + delta_y;
    system_set_mouse_position(&x, &y);
    mouse::ref().set_position({ x, y });
}
