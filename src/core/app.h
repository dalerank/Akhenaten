#pragma once

#include "core/vec2i.h"
#include "core/xstring.h"
#include "core/xfunction.h"
#include "core/hvector.h"

struct event_app_center_screen { int value; };
struct event_app_toggle_fullscreen { int value; };
struct event_app_screenshot { int value; };
struct event_app_city_screenshot { int value; };
struct event_request_exit { int value; };
struct event_display_options_apply_resolution { int w; int h; };

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
void app_terminate(const char* message) noexcept;

struct application_t {
    bool active = true;
    bool quit = false;

    xstring game_name;

    using event_handler_cb = xfunction<void(void*)>;
    hvector<event_handler_cb, 32> keyboard_event_handlers;
    hvector<event_handler_cb, 8> user_event_handlers;
    hvector<event_handler_cb, 8> touch_event_handlers;

    void setup();

    void subscribe_events();
    void register_modules();

    void register_keyboard_event_handler(event_handler_cb);
    void register_user_event_handler(event_handler_cb);
    void register_touch_event_handler(event_handler_cb);
    void pump_one_frame();

    void handle_keyboard_event(void* event);
    void handle_user_event(void* event);
    void handle_touch_event(void* event);
    void handle_window_event(void* event);
};

extern application_t g_app;

namespace application {

    struct AppTag {};
    using module_iterator_function_cb = void();
    using ModuleIterator = FuncLinkedList<module_iterator_function_cb*, AppTag>;

} // end namespace application

#define ANK_REGISTER_APPLICATION_MODULE(func) func(); \
    namespace application {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static application::ModuleIterator ANK_CONFIG_CC1(module_handler, __LINE__)(func); void func()
