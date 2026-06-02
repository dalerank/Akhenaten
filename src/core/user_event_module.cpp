#include "core/app.h"
#include "platform/screen.h"

#include <SDL.h>

#define INTPTR(d) (*(int*)(d))

struct user_event_module_t {
    void handle_resize(SDL_Event* ev);
    void handle_fullscreen(SDL_Event* ev);
    void handle_windowed(SDL_Event* ev);
    void handle_center_window(SDL_Event* ev);
};

void user_event_module_t::handle_resize(SDL_Event* ev) {
    if (ev->type != SDL_USEREVENT || ev->user.code != USER_EVENT_RESIZE) {
        return;
    }

    platform_screen_set_window_size(INTPTR(ev->user.data1), INTPTR(ev->user.data2));
}

void user_event_module_t::handle_fullscreen(SDL_Event* ev) {
    if (ev->type != SDL_USEREVENT || ev->user.code != USER_EVENT_FULLSCREEN) {
        return;
    }

    platform_screen_set_fullscreen();
}

void user_event_module_t::handle_windowed(SDL_Event* ev) {
    if (ev->type != SDL_USEREVENT || ev->user.code != USER_EVENT_WINDOWED) {
        return;
    }

    platform_screen_set_windowed();
}

void user_event_module_t::handle_center_window(SDL_Event* ev) {
    if (ev->type != SDL_USEREVENT || ev->user.code != USER_EVENT_CENTER_WINDOW) {
        return;
    }

    platform_screen_center_window();
}

void ANK_REGISTER_APPLICATION_MODULE(register_user_event_module) {
    static user_event_module_t mod;
    g_app.register_user_event_handler([&](void* ev) { mod.handle_resize((SDL_Event*)ev); });
    g_app.register_user_event_handler([&](void* ev) { mod.handle_fullscreen((SDL_Event*)ev); });
    g_app.register_user_event_handler([&](void* ev) { mod.handle_windowed((SDL_Event*)ev); });
    g_app.register_user_event_handler([&](void* ev) { mod.handle_center_window((SDL_Event*)ev); });
}
