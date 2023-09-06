#include "app.h"

#include "game/settings.h"
#include <SDL.h>

void app_window_resize(const display_size& wsize) {
    static int s_width;
    static int s_height;

    s_width = wsize.w;
    s_height = wsize.h;
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = USER_EVENT_RESIZE;
    event.user.data1 = &s_width;
    event.user.data2 = &s_height;
    SDL_PushEvent(&event);
}

void app_fullscreen(bool fullscreen) {
    app_post_event(fullscreen ? USER_EVENT_FULLSCREEN : USER_EVENT_WINDOWED);
    if (!fullscreen) {
        app_window_resize({1200, 800});
    }
}

void app_post_event(int code) {
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = code;
    SDL_PushEvent(&event);
}