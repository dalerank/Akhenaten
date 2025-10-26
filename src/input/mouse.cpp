#include "input/mouse.h"

#include "graphics/screen.h"

enum { SYSTEM_NONE = 0, SYSTEM_UP = 1, SYSTEM_DOWN = 2, SYSTEM_DOUBLE_CLICK = 4 };

#define DOUBLE_CLICK_TIME 500

mouse g_mouse;
static mouse dialog;
static time_millis last_click;

const mouse& mouse::get() { return g_mouse; }
mouse& mouse::ref() { return g_mouse; }

static void clear_mouse_button(mouse_button* button) {
    button->is_down = 0;
    button->went_down = 0;
    button->went_up = 0;
    button->double_click = 0;
    button->system_change = SYSTEM_NONE;
}

void mouse::set_from_touch(const touch_t* first, const touch_t* last) {
    x = first->current_point.x;
    y = first->current_point.y;
    scrolled = touch_get_scroll();
    is_inside_window = !first->has_ended;
    is_touch = 1;

    left.system_change = SYSTEM_NONE;
    right.system_change = SYSTEM_NONE;

    if (touch_is_scroll()) {
        reset_button_state();
        return;
    }

    left.is_down = (!first->has_ended && first->in_use);
    left.went_down = first->has_started;
    left.went_up = first->has_ended;
    left.double_click = touch_was_double_click(first);

    right.is_down = (!last->has_ended && last->in_use);
    right.went_down = last->has_started;
    right.went_up = last->has_ended;

    clear_mouse_button(&middle);
}

void mouse::set_position(vec2i p) {
    if (p.x != this->x || p.y != this->y) {
        last_click = 0;
    }

    this->x = p.x;
    this->y = p.y;
    is_touch = 0;
    is_inside_window = 1;
}

void mouse::set_left_down(int down) {
    left.system_change |= down ? SYSTEM_DOWN : SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    if (!down) {
        time_millis now = time_get_millis();
        left.system_change |= ((last_click < now) && ((now - last_click) <= DOUBLE_CLICK_TIME)) ? SYSTEM_DOUBLE_CLICK : SYSTEM_NONE;
        last_click = now;
    }
}

void mouse::set_middle_down(int down) {
    middle.system_change |= down ? SYSTEM_DOWN : SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    last_click = 0;
}

void mouse::set_right_down(int down) {
    right.system_change |= down ? SYSTEM_DOWN : SYSTEM_UP;
    is_touch = 0;
    is_inside_window = 1;
    last_click = 0;
}

void mouse::set_inside_window(int inside) {
    is_inside_window = inside;
    is_touch = 0;
}

void mouse::init() {
    set_inside_window(1);
}

static void update_button_state(mouse_button* button) {
    button->went_down = (button->system_change & SYSTEM_DOWN) == SYSTEM_DOWN;
    button->went_up = (button->system_change & SYSTEM_UP) == SYSTEM_UP;
    button->double_click = (button->system_change & SYSTEM_DOUBLE_CLICK) == SYSTEM_DOUBLE_CLICK;
    button->system_change = SYSTEM_NONE;
    button->is_down = (button->is_down || button->went_down) && !button->went_up;
}

void mouse::determine_button_state() {
    update_button_state(&left);
    update_button_state(&middle);
    update_button_state(&right);
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
    left.went_up = 0;
    middle.went_up = 0;
    right.went_up = 0;
}

void mouse::reset_button_state(void) {
    last_click = 0;
    clear_mouse_button(&left);
    clear_mouse_button(&middle);
    clear_mouse_button(&right);
}

const mouse* mouse_in_dialog(const mouse* m) {
    dialog.left = m->left;
    dialog.middle = m->middle;
    dialog.right = m->right;
    dialog.scrolled = m->scrolled;
    dialog.is_inside_window = m->is_inside_window;
    dialog.is_touch = m->is_touch;

    dialog.x = m->x - screen_dialog_offset_x();
    dialog.y = m->y - screen_dialog_offset_y();
    return &dialog;
}
