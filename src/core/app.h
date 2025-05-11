#pragma once

#include "core/vec2i.h"
#include "core/xstring.h"

struct event_app_center_screen { int value; };
struct event_app_toggle_fullscreen { int value; };
struct event_app_screenshot { int value; };

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
