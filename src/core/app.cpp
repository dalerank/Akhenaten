#include "app.h"

#include "core/archive.h"
#include "game/game.h"
#include "game/game_events.h"
#include "game/game_events_history.h"
#include "platform/screen.h"
#include "graphics/screenshot.h"
#include "core/log.h"
#include "input/mouse.h"
#include "js/js_events.h"
#include "js/js_game.h"

#include <SDL.h>

application_t g_app;

ANK_SCRIPT_EVENT(event_request_exit, value)
void ANK_PERMANENT_CALLBACK(event_request_exit, ev) {
    app_post_event(USER_EVENT_QUIT);
}

ANK_SCRIPT_EVENT(event_display_options_apply_resolution, w, h)
void ANK_PERMANENT_CALLBACK(event_display_options_apply_resolution, ev) {
    app_window_resize({ev.w, ev.h});
}

ANK_SCRIPT_EVENT(event_app_toggle_fullscreen, value)

void app_window_resize(const vec2i& wsize) {
    static int s_width;
    static int s_height;

    s_width = wsize.x;
    s_height = wsize.y;
    SDL_Event event;
    event.user.type = SDL_USEREVENT;
    event.user.code = USER_EVENT_RESIZE;
    event.user.data1 = &s_width;
    event.user.data2 = &s_height;
    SDL_PushEvent(&event);
}

void app_fullscreen(bool fullscreen) {
    app_post_event(fullscreen ? USER_EVENT_FULLSCREEN : USER_EVENT_WINDOWED);
    game.set_fullscreen(fullscreen);
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

void app_terminate(const char* message) noexcept {
    logs::critical("%s", message);
    platform_screen_show_error_message_box("CRASHED", message);

    std::terminate();
}

void application_t::setup() {
    game_name = "Akhenaten";
    logs::info("Engine set to %s", game_name.c_str());
}

void application_t::register_modules() {
    for (application::ModuleIterator* m = application::ModuleIterator::tail; m; m = m->next) {
        m->func();
    }
}

void application_t::register_keyboard_event_handler(event_handler_cb cb) {
    keyboard_event_handlers.push_back(cb);
}

void application_t::handle_window_event(void* ev) {
#ifndef GAME_PLATFORM_NSWITCH
    const SDL_WindowEvent& event = ((SDL_Event*)ev)->window;
    switch (event.event) {
    case SDL_WINDOWEVENT_ENTER:
        g_mouse.set_inside_window(1);
        break;
    case SDL_WINDOWEVENT_LEAVE:
        g_mouse.set_inside_window(0);
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        logs::info("Window resized to %d x %d", (int)event.data1, (int)event.data2);
        platform_screen_resize(event.data1, event.data2, 1);
        break;
    case SDL_WINDOWEVENT_RESIZED:
        logs::info("System resize to %d x %d", (int)event.data1, (int)event.data2);
        break;
    case SDL_WINDOWEVENT_MOVED:
        logs::info("Window move to coordinates x: %d y: %d\n", (int)event.data1, (int)event.data2);
        platform_screen_move(event.data1, event.data2);
        break;

    case SDL_WINDOWEVENT_SHOWN:
        logs::info("Window %d shown", (unsigned int)event.windowID);
        active = true;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        logs::info("Window %d hidden", (unsigned int)event.windowID);
        active = false;
        break;
    }
#endif
}

void application_t::handle_keyboard_event(void* event) {
    for (auto& handler : keyboard_event_handlers) {
        handler(event);
    }
}

void application_t::subscribe_events() {
    events::subscribe_permanent([] (event_app_center_screen ev) {
        app_post_event(USER_EVENT_CENTER_WINDOW);
    });

    events::subscribe_permanent([] (event_app_toggle_fullscreen ev) {
        app_fullscreen(!game.is_fullscreen(false));
    });

    events::subscribe_permanent([] (event_app_screenshot ev) {
        graphics_save_screenshot(SCREENSHOT_DISPLAY);
    });

    events::subscribe_permanent([] (event_app_city_screenshot ev) {
        graphics_save_screenshot(SCREENSHOT_FULL_CITY);
    });
}
