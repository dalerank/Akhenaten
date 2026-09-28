#include "core/app.h"
#include "input/mouse.h"
#include "platform/screen.h"

#include <SDL.h>

struct mouse_module_t {
    vec2i mouse_pos_from_event(int x, int y) const;

    void handle_motion(SDL_Event* ev);
    void handle_button_down(SDL_Event* ev);
    void handle_button_up(SDL_Event* ev);
    void handle_wheel(SDL_Event* ev);

    void handle_mouse_button(SDL_MouseButtonEvent* event, int is_down);
};

vec2i mouse_module_t::mouse_pos_from_event(int x, int y) const {
    return {g_platform_screen.scale_pixels_to_logical(x), g_platform_screen.scale_pixels_to_logical(y)};
}

void mouse_module_t::handle_mouse_button(SDL_MouseButtonEvent* event, int is_down) {
    auto& m = mouse::ref();
    if (!SDL_GetRelativeMouseMode()) {
        m.set_position(mouse_pos_from_event(event->x, event->y));
    }

    if (event->button == SDL_BUTTON_LEFT) {
        m.set_left_down(is_down);
    } else if (event->button == SDL_BUTTON_MIDDLE) {
        m.set_middle_down(is_down);
    } else if (event->button == SDL_BUTTON_RIGHT) {
        m.set_right_down(is_down);
    }
}

void mouse_module_t::handle_motion(SDL_Event* ev) {
    if (ev->type != SDL_MOUSEMOTION) {
        return;
    }

    if (ev->motion.which != SDL_TOUCH_MOUSEID && !SDL_GetRelativeMouseMode()) {
        mouse::ref().set_position(mouse_pos_from_event(ev->motion.x, ev->motion.y));
    }
}

void mouse_module_t::handle_button_down(SDL_Event* ev) {
    if (ev->type != SDL_MOUSEBUTTONDOWN) {
        return;
    }

    if (ev->button.which != SDL_TOUCH_MOUSEID) {
        handle_mouse_button(&ev->button, 1);
    }
}

void mouse_module_t::handle_button_up(SDL_Event* ev) {
    if (ev->type != SDL_MOUSEBUTTONUP) {
        return;
    }

    if (ev->button.which != SDL_TOUCH_MOUSEID) {
        handle_mouse_button(&ev->button, 0);
    }
}

void mouse_module_t::handle_wheel(SDL_Event* ev) {
    if (ev->type != SDL_MOUSEWHEEL) {
        return;
    }

    if (ev->wheel.which != SDL_TOUCH_MOUSEID) {
        mouse::ref().set_scroll(ev->wheel.y > 0 ? SCROLL_UP : ev->wheel.y < 0 ? SCROLL_DOWN : SCROLL_NONE);
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_mouse_module) {
    static mouse_module_t mod;
    g_app.register_mouse_event_handler([&](void* ev) { mod.handle_motion((SDL_Event*)ev); });
    g_app.register_mouse_event_handler([&](void* ev) { mod.handle_button_down((SDL_Event*)ev); });
    g_app.register_mouse_event_handler([&](void* ev) { mod.handle_button_up((SDL_Event*)ev); });
    g_app.register_mouse_event_handler([&](void* ev) { mod.handle_wheel((SDL_Event*)ev); });
}
