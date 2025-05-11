#include "app.h"

#include "game/settings.h"
#include "game/game_events.h"
#include "platform/screen.h"
#include "graphics/screenshot.h"
#include "core/log.h"
#include <SDL.h>

application_t g_application;

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
    g_settings.set_fullscreen(fullscreen);
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

void app_request_exit() {
    app_post_event(USER_EVENT_QUIT);
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

void application_t::subscribe_events() {
    events::subscribe_permanent([] (event_app_center_screen ev) {
        app_post_event(USER_EVENT_CENTER_WINDOW);
    });

    events::subscribe_permanent([] (event_app_toggle_fullscreen ev) {
        app_fullscreen(!g_settings.is_fullscreen(e_setting_none));
    });

    events::subscribe_permanent([] (event_app_screenshot ev) {
        graphics_save_screenshot(SCREENSHOT_DISPLAY);
    });

    events::subscribe_permanent([] (event_app_city_screenshot ev) {
        graphics_save_screenshot(SCREENSHOT_FULL_CITY);
    });
}
