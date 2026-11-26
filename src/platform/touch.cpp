#include "platform/touch.h"
#include "platform/platform.h"

#include "graphics/screen.h"
#include "input/touch.h"

static vec2i get_touch_coordinates(float x, float y) {
    vec2i coords;
    coords.x = (int)(x * screen_width());
    coords.y = (int)(y * screen_height());
    return coords;
}

void platform_touch_start(SDL_TouchFingerEvent* event) {
    if constexpr (platform.is_macos() && !platform.is_ios()) {
        // Attempt to disable trackpad touches on MacOS
        static SDL_TouchID trackpad_id;
        if (!trackpad_id)
            trackpad_id = SDL_GetTouchDevice(0);

        if (event->touchId == trackpad_id)
            return;
    }
#if defined(__vita__)
    // Only use main screen for vita
    if (event->touchId == 1)
        return;
#endif
    g_touch.finger_down(event->fingerId, get_touch_coordinates(event->x, event->y), event->timestamp);
}

void platform_touch_move(SDL_TouchFingerEvent* event) {
    g_touch.finger_move(event->fingerId, get_touch_coordinates(event->x, event->y), event->timestamp);
}

void platform_touch_end(SDL_TouchFingerEvent* event) {
    g_touch.finger_up(event->fingerId, event->timestamp);
}
