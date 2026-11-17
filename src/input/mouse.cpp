#include "input/mouse.h"

#include "graphics/screen.h"
#include "input/touch.h"
#include "platform/platform.h"

#include <SDL_mouse.h>

mouse g_mouse;

const mouse& mouse::get() {
    return g_mouse;
}
mouse& mouse::ref() {
    return g_mouse;
}

void mouse_button::clear() {
    is_down = false;
    went_down = false;
    went_up = false;
    double_click = false;
    system_change = SYSTEM_NONE;
}

void mouse_button::update() {
    went_down = (system_change & SYSTEM_DOWN) == SYSTEM_DOWN;
    went_up = (system_change & SYSTEM_UP) == SYSTEM_UP;
    double_click = (system_change & SYSTEM_DOUBLE_CLICK) == SYSTEM_DOUBLE_CLICK;
    system_change = SYSTEM_NONE;
    is_down = (is_down || went_down) && !went_up;
}

void mouse::set_from_touch(const touch_t* first, const touch_t* last) {
    x = first->current_point.x;
    y = first->current_point.y;
    scrolled = g_touch.get_scroll();
    is_inside_window = !first->has_ended;
    is_touch = 1;

    left.system_change = mouse_button::SYSTEM_NONE;
    right.system_change = mouse_button::SYSTEM_NONE;

    if (g_touch.is_scroll()) {
        reset_button_state();
        return;
    }

    left.is_down = (!first->has_ended && first->in_use);
    left.went_down = first->has_started;
    left.went_up = first->has_ended;
    left.double_click = g_touch.was_double_click(*first);

    right.is_down = (!last->has_ended && last->in_use);
    right.went_down = last->has_started;
    right.went_up = last->has_ended;

    middle.clear();
}

void mouse::set_position(vec2i p) {
    if (p.x != x || p.y != y) {
        last_click = 0;
    }

    x = p.x;
    y = p.y;
    is_touch = 0;
    is_inside_window = 1;
}

void mouse::set_left_down(bool down) {
    left.system_change |= down ? mouse_button::SYSTEM_DOWN : mouse_button::SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    if (!down) {
        time_millis now = time_get_millis();
        left.system_change |= ((last_click < now) && ((now - last_click) <= DOUBLE_CLICK_TIME))
                                ? mouse_button::SYSTEM_DOUBLE_CLICK
                                : mouse_button::SYSTEM_NONE;
        last_click = now;
    }
}

void mouse::set_middle_down(bool down) {
    middle.system_change |= down ? mouse_button::SYSTEM_DOWN : mouse_button::SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    last_click = 0;
}

void mouse::set_right_down(bool down) {
    right.system_change |= down ? mouse_button::SYSTEM_DOWN : mouse_button::SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    last_click = 0;
}

void mouse::set_inside_window(bool inside) {
    is_inside_window = inside;
    is_touch = 0;
}

void mouse::init() {
    relative_mode = false;
    relative_mode_restore = {0, 0};
    set_inside_window(true);
    g_touch.clear_all();
}

vec2i mouse::relative_state() {
    vec2i delta;
    SDL_GetRelativeMouseState(&delta.x, &delta.y);
    return delta;
}

vec2i mouse::warp_position(vec2i p) {
    platform.screen_warp_mouse(&p.x, &p.y);
    return p;
}

void mouse::set_relative_mode(bool enabled) {
    if (enabled == relative_mode)
        return;

    if (enabled) {
        SDL_GetMouseState(&relative_mode_restore.x, &relative_mode_restore.y);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        // Discard the first value, which is incorrect
        // (the first one gives the relative position to center of window)
        relative_state();
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        relative_mode_restore = warp_position(relative_mode_restore);
        set_position(relative_mode_restore);
    }
    relative_mode = enabled;
}

void mouse::move_relative(vec2i delta) {
    set_position(warp_position(pos() + delta));
}

void mouse::determine_button_state() {
    left.update();
    middle.update();
    right.update();
}

void mouse::set_scroll(int state) {
    scrolled = state;
    is_touch = 0;
    is_inside_window = 1;
}

void mouse::reset_scroll() {
    scrolled = SCROLL_NONE;
}

void mouse::reset_up_state() {
    left.went_up = false;
    middle.went_up = false;
    right.went_up = false;
}

void mouse::reset_button_state() {
    last_click = 0;
    left.clear();
    middle.clear();
    right.clear();
}

const mouse* mouse::in_dialog() const {
    static mouse dialog;
    dialog.left = left;
    dialog.middle = middle;
    dialog.right = right;
    dialog.scrolled = scrolled;
    dialog.is_inside_window = is_inside_window;
    dialog.is_touch = is_touch;

    dialog.x = x - screen_dialog_offset_x();
    dialog.y = y - screen_dialog_offset_y();
    return &dialog;
}
