#pragma once

#include "core/event.h"
#include "core/vec2i.h"
#include "core/xstring.h"

struct event_app: game_event { int value; event_app(const char *name, const int value): game_event(name, "app"), value(value) {}; };
struct event_app_center_screen: event_app { explicit event_app_center_screen(const int value): event_app("event_app_center_screen", value) {}; };
struct event_app_toggle_fullscreen: event_app { explicit event_app_toggle_fullscreen(const int value): event_app("event_app_toggle_fullscreen", value) {}; };
struct event_app_screenshot: event_app { explicit event_app_screenshot(const int value): event_app("event_app_screenshot", value) {}; };
struct event_app_city_screenshot: event_app { explicit event_app_city_screenshot(const int value): event_app("event_app_city_screenshot", value) {}; };

enum e_user_event {
    USER_EVENT_QUIT,
    USER_EVENT_RESIZE,
    USER_EVENT_FULLSCREEN,
    USER_EVENT_WINDOWED,
    USER_EVENT_CENTER_WINDOW,
};

void app_window_resize(const vec2i& wsize);
void app_fullscreen(bool fullscreen);
void app_post_event(int code);
void app_request_exit();
void app_terminate(const char* message) noexcept;

struct application_t {
    bool active = true;
    bool quit = false;

    xstring game_name;

    void setup();

    void subscribe_events();
};

extern application_t g_application;
