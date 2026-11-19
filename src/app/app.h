#pragma once

#include "core/vec2i.h"
#include "core/xstring.h"
#include "core/xfunction.h"
#include "core/hvector.h"

#include "core/app_events.h"
#include "core/app_module.h"

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
void app_handle_close_request();
void app_terminate(const char* message) noexcept;

struct hud_end_context_t {
    uint32_t time_before_run;
    uint32_t time_between_run_and_draw;
    uint32_t time_after_draw;
};

struct application_t {
    bool active = true;
    bool quit = false;

    xstring game_name;

    using event_handler_cb = xfunction<void(void*)>;
    hvector<event_handler_cb, 32> keyboard_event_handlers;
    hvector<event_handler_cb, 8> mouse_event_handlers;
    hvector<event_handler_cb, 8> user_event_handlers;
    hvector<event_handler_cb, 8> touch_event_handlers;
    hvector<event_handler_cb, 8> hud_end_handlers;

    void setup();

    void subscribe_events();
    void register_modules();

    void register_keyboard_event_handler(event_handler_cb);
    void register_mouse_event_handler(event_handler_cb);
    void register_user_event_handler(event_handler_cb);
    void register_touch_event_handler(event_handler_cb);
    void register_hud_end_handler(event_handler_cb);
    void pump_one_frame();

    void handle_keyboard_event(void* event);
    void handle_mouse_event(void* event);
    void handle_user_event(void* event);
    void handle_touch_event(void* event);
    void handle_window_event(void* event);
    void handle_hud_end(hud_end_context_t* context);
};

extern application_t g_app;
