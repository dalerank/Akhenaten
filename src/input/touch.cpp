#include "input/touch.h"

#include "input/mouse.h"

#include <cstdlib>

constexpr time_millis CLICK_TIME = 300;
constexpr int NOT_MOVING_RANGE = 5;
constexpr int SCROLL_FINGER_RADIUS = 25;
constexpr time_millis MILLIS_TOLERANCE_BETWEEN_LAST_MOVE_AND_TOUCH_END = 60;
constexpr time_millis STALE_TOUCH_TIME = 3000;

touch_input_t g_touch;

bool touch_t::start_delayed() const {
    return has_started && !has_moved && !has_ended && ((time_get_millis() - start_time) < CLICK_TIME / 2);
}

bool touch_t::not_click() const {
    return has_moved || (!has_ended && (time_get_millis() - start_time) >= CLICK_TIME)
           || (has_ended && (last_change_time - start_time) >= CLICK_TIME);
}

bool touch_t::was_click() const {
    return has_ended && !has_moved && (last_change_time - start_time) < CLICK_TIME;
}

const touch_t* touch_input_t::earliest() const {
    time_millis timestamp = -1;
    int touch_index = MAX_ACTIVE_TOUCHES;
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        const touch_t& t = finger[i];
        if (t.in_use && !t.start_delayed() && t.start_time < timestamp) {
            timestamp = t.start_time;
            touch_index = i;
        }
    }
    return &finger[touch_index];
}

const touch_t* touch_input_t::earliest_raw() const {
    time_millis timestamp = -1;
    int touch_index = MAX_ACTIVE_TOUCHES;
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        const touch_t& t = finger[i];
        if (t.in_use && t.start_time < timestamp) {
            timestamp = t.start_time;
            touch_index = i;
        }
    }
    return &finger[touch_index];
}

const touch_t* touch_input_t::latest() const {
    int active_touches = 0;
    time_millis timestamp = 0;
    int touch_index = MAX_ACTIVE_TOUCHES;
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        const touch_t& t = finger[i];
        if (t.in_use && !t.start_delayed()) {
            ++active_touches;
            if (t.start_time > timestamp) {
                timestamp = t.start_time;
                touch_index = i;
            }
        }
    }
    return (active_touches > 1) ? &finger[touch_index] : &finger[MAX_ACTIVE_TOUCHES];
}

int touch_input_t::active_count() const {
    int active_touches = 0;
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        if (finger[i].in_use)
            ++active_touches;
    }
    return active_touches;
}

bool touch_input_t::was_double_click(const touch_t& t) const {
    return t.was_click() && old_touch.was_click() && (t.start_time > old_touch.last_change_time)
           && (t.start_time - old_touch.last_change_time) < CLICK_TIME;
}

bool touch_input_t::is_scroll() const {
    if (active_count() != 2)
        return false;

    const touch_t* first = earliest();
    const touch_t* last = latest();
    return ((last->start_time - first->start_time) < CLICK_TIME) && !last->was_click();
}

int touch_input_t::get_scroll() {
    const touch_t* first = earliest();
    const touch_t* last = latest();
    if (!is_scroll() || !first->has_moved || !last->has_moved)
        return SCROLL_NONE;

    if (!last_scroll_position)
        last_scroll_position = first->start_point.y;

    int delta_x = abs((first->current_point.x - first->start_point.x) - (last->current_point.x - last->start_point.x));
    int delta_y = abs((first->current_point.y - first->start_point.y) - (last->current_point.y - last->start_point.y));
    if (delta_x > SCROLL_FINGER_RADIUS || delta_y > SCROLL_FINGER_RADIUS)
        return SCROLL_NONE;

    int delta = first->current_point.y - last_scroll_position;
    if (abs(delta) < NOT_MOVING_RANGE * 2)
        return SCROLL_NONE;

    last_scroll_position = first->current_point.y;
    return (delta > 0) ? SCROLL_UP : SCROLL_DOWN;
}

int touch_input_t::unused_index() const {
    int i = 0;
    while (i < MAX_ACTIVE_TOUCHES) {
        if (!finger[i].in_use)
            break;

        ++i;
    }
    return i;
}

int touch_input_t::index_of_finger(int64_t finger_id) const {
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        if (finger_ids[i] == finger_id && finger[i].in_use)
            return i;
    }
    return MAX_ACTIVE_TOUCHES;
}

void touch_input_t::finger_down(int64_t finger_id, vec2i start_coords, time_millis start_time) {
    int index = unused_index();
    if (index == MAX_ACTIVE_TOUCHES)
        return;

    touch_t& t = finger[index];
    t.in_use = true;
    t.has_started = true;
    t.has_ended = false;
    t.start_point = start_coords;
    t.current_point = start_coords;
    t.previous_frame_point = start_coords;
    t.frame_movement = {0, 0};
    t.last_movement = t.frame_movement;
    t.start_time = start_time;
    t.last_change_time = start_time;
    finger_ids[index] = finger_id;
}

void touch_input_t::finger_move(int64_t finger_id, vec2i current_coords, time_millis current_time) {
    int index = index_of_finger(finger_id);
    if (index == MAX_ACTIVE_TOUCHES)
        return;

    touch_t& t = finger[index];
    t.last_change_time = current_time;
    t.current_point = current_coords;
    if ((abs(current_coords.x - t.start_point.x) > NOT_MOVING_RANGE)
        || (abs(current_coords.y - t.start_point.y) > NOT_MOVING_RANGE))
        t.has_moved = true;
}

void touch_input_t::finger_up(int64_t finger_id, time_millis current_time) {
    int index = index_of_finger(finger_id);
    if (index == MAX_ACTIVE_TOUCHES)
        return;

    touch_t& t = finger[index];
    t.has_ended = true;
    // This is needed because sometimes SDL waits for up to three frames to register the touch end
    if (current_time - t.last_change_time < MILLIS_TOLERANCE_BETWEEN_LAST_MOVE_AND_TOUCH_END)
        t.frame_movement = t.last_movement;

    finger_ids[index] = 0;
}

void touch_input_t::clear_all() {
    finger.fill({});
    finger_ids.fill(0);
    old_touch = {};
    last_scroll_position = 0;
    touchpad_mode_click_type = e_emulated_click::none;
    mouse::ref().is_touch = 0;
}

void touch_input_t::reset(bool reset_old_touch) {
    time_millis now = time_get_millis();
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        touch_t& t = finger[i];
        if (!t.in_use)
            continue;

        if (!t.has_ended && (now - t.last_change_time > STALE_TOUCH_TIME)) {
            t.has_ended = true;
        }

        if (t.has_ended) {
            t.in_use = false;
            if (!reset_old_touch)
                old_touch = t;
            else {
                old_touch.last_change_time = 0;
            }
            t.has_started = false;
            t.has_moved = false;
            t.has_ended = false;
            last_scroll_position = 0;
        } else {
            t.frame_movement = t.current_point - t.previous_frame_point;
            if (t.frame_movement.x != 0 || t.frame_movement.y != 0)
                t.last_movement = t.frame_movement;

            t.previous_frame_point = t.current_point;
            t.has_started = t.start_delayed();
        }
    }
}

bool touch_input_t::any_went_up() const {
    for (int i = 0; i < MAX_ACTIVE_TOUCHES; ++i) {
        if (finger[i].has_ended)
            return true;
    }
    return false;
}

bool touch_input_t::handle_emulated_mouse_clicks() {
    auto &m = mouse::ref();
    m.reset_scroll();
    switch (touchpad_mode_click_type) {
    case e_emulated_click::left:
        m.set_left_down(false);
        break;
    case e_emulated_click::right:
        m.set_right_down(false);
        break;
    default:
        m.reset_button_state();
        return false;
    }
    m.determine_button_state();
    touchpad_mode_click_type = e_emulated_click::none;
    return true;
}

void touch_input_t::handle_mouse_touchpad() {
    auto &m = mouse::ref();
    if (handle_emulated_mouse_clicks())
        return;

    int num_fingers = active_count();

    if (!num_fingers)
        return;

    if (any_went_up()) {
        if (num_fingers == 1 && earliest()->was_click()) {
            m.set_left_down(true);
            m.determine_button_state();
            touchpad_mode_click_type = e_emulated_click::left;
        } else if (num_fingers == 2 && (earliest()->was_click() || latest()->was_click())) {
            m.set_right_down(true);
            m.determine_button_state();
            touchpad_mode_click_type = e_emulated_click::right;
        }
    } else {
        const touch_t* t = earliest();
        if (!t->has_moved)
            return;
        m.move_relative(t->frame_movement);
    }
}

void touch_input_t::handle_mouse_direct() {
    auto &m = mouse::ref();
    m.reset_scroll();
    m.reset_button_state();

    m.set_position(m.warp_position(earliest()->current_point));
}

bool touch_input_t::to_mouse() {
    const touch_t* first = earliest();
    auto &m = mouse::ref();

    if (!first->in_use) {
        m.is_touch = 0;
        if (touchpad_mode_click_type != e_emulated_click::none)
            return handle_emulated_mouse_clicks();

        return false;
    }
    switch (mode) {
    case e_touch_mode::touchpad:
        handle_mouse_touchpad();
        break;
    case e_touch_mode::direct:
        handle_mouse_direct();
        break;
    default:
        m.set_from_touch(first, latest());
        break;
    }
    return true;
}

void touch_input_t::cycle_mode() {
    mode = static_cast<e_touch_mode>((static_cast<int>(mode) + 1) % static_cast<int>(e_touch_mode::count));
}
