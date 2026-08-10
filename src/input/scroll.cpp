#include "scroll.h"

#include "core/calc.h"
#include "core/direction.h"
#include "core/speed.h"
#include "graphics/screen.h"
#include "graphics/view/view.h" // g_camera
#include "input/touch.h"
#include "game/game_config.h"
#include "game/game.h"
#include "js/js_game.h"
#include "platform/arguments.h"

#include <cmath>
#include <cstdlib>

enum key_state { KEY_STATE_UNPRESSED = 0, KEY_STATE_PRESSED = 1, KEY_STATE_HELD = 2, KEY_STATE_AXIS = 3 };

scroll_t g_scroll;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_scroll_config) {
    g_config_arch.r("scroll_config", g_scroll.config);
}

ANK_GLOBAL_OBJECT(g_scroll.config, __scroll_config,
    mouse_border,
    touch_border,
    drag_min_delta,
    drag_decay_time,
    regular_decay_time,
    key_wait_time_after_hold,
    key_pressed,
    key_max_value,
    tile_x_pixels,
    tile_y_pixels,
    mouse_pan_log_k)

float scroll_t::dampen_mouse_relative_pan_delta(float d) const {
    const float a = std::fabs(d);
    if (a < 1e-5f)
        return 0.f;
    const float k = config.mouse_pan_log_k;
    const float sign = d > 0.f ? 1.f : -1.f;
    return sign * (std::log(1.f + k * a) / k);
}

void scroll_t::clear_speed() {
    speed_clear(speed.x);
    speed_clear(speed.y);
    speed.decaying = 0;
}

int scroll_t::arrow_key_t::get_value() {
    if (state == KEY_STATE_AXIS)
        return value;

    if (!!game_features::gameui_smooth_scrolling) {
        return state != KEY_STATE_UNPRESSED;
    }

    if (state == KEY_STATE_PRESSED) {
        state = KEY_STATE_HELD;
        return 1;
    }
    if (state == KEY_STATE_HELD && time_get_millis() - last_change >= g_scroll.config.key_wait_time_after_hold)
        return 1;

    return 0;
}

float scroll_t::arrow_key_t::get_normalized_value() {
    int v = get_value();
    if (v == g_scroll.config.key_pressed)
        return 1.0f;

    return fminf(value / g_scroll.config.key_max_value, 1.0f);
}

void scroll_t::arrow_key_t::restart_unless(const arrow_key_t *exception) {
    if (this == exception)
        return;
    if (state != KEY_STATE_UNPRESSED && state != KEY_STATE_AXIS) {
        state = KEY_STATE_PRESSED;
        last_change = time_get_millis();
    }
}

void scroll_t::arrows_t::restart_all_except(const arrow_key_t *arrow) {
    g_scroll.clear_speed();
    up.restart_unless(arrow);
    down.restart_unless(arrow);
    left.restart_unless(arrow);
    right.restart_unless(arrow);
}

int scroll_t::get_key_state_for_value(int value) const {
    if (!value)
        return KEY_STATE_UNPRESSED;

    if (value == config.key_pressed)
        return KEY_STATE_PRESSED;

    return KEY_STATE_AXIS;
}

void scroll_t::arrow_key_t::set(int new_value) {
    int new_state = g_scroll.get_key_state_for_value(new_value);
    if (new_state != KEY_STATE_AXIS && new_state != KEY_STATE_UNPRESSED && state != KEY_STATE_UNPRESSED)
        return;
    // Key should retain axis state even if its value is zero
    if (state != KEY_STATE_AXIS || new_state != KEY_STATE_UNPRESSED)
        state = new_state;

    value = new_value;
    last_change = time_get_millis();
    if (new_state != KEY_STATE_AXIS && !game_features::gameui_smooth_scrolling)
        g_scroll.arrows.restart_all_except(this);
}

int scroll_t::in_progress() const {
    return is_scrolling || drag.active;
}

int scroll_t::speed_factor() const {
    return calc_bound((100 - game_features::gameopt_scroll_speed.to_int()) / 10, 0, 10);
}

int scroll_t::is_smooth() const {
    return !!game_features::gameui_smooth_scrolling || drag.active || speed.decaying;
}

int scroll_t::should_scroll() {
    time_millis current_time = time_get_millis();
    time_millis diff = current_time - last_time;
    unsigned int scroll_delay = speed_factor();
    int further_delay = constant_input ? 20 - (int)(fmaxf(speed.modifier_x, speed.modifier_y) * 20) : 0;
    if (scroll_delay < 10) { // 0% = 10 = no scroll at all
        if (diff >= 12 * (scroll_delay + further_delay) + 2) {
            last_time = current_time;
            return 1;
        }
    }
    return 0;
}

int scroll_t::direction_from_sides(int top, int left, int bottom, int right) {
    // two sides
    if (left && top)
        return DIR_7_TOP;

    else if (left && bottom)
        return DIR_5_LEFT;

    else if (right && top)
        return DIR_1_RIGHT;

    else if (right && bottom)
        return DIR_3_BOTTOM;

    // one side
    if (left)
        return DIR_6_TOP_LEFT;

    else if (right)
        return DIR_2_BOTTOM_RIGHT;

    else if (top)
        return DIR_0_TOP_RIGHT;

    else if (bottom)
        return DIR_4_BOTTOM_LEFT;

    // none of them
    return DIR_8_NONE;
}

void scroll_t::set_custom_margins(vec2i pos, vec2i size) {
    limits.active = 1;
    limits.pos = pos;
    limits.size = size;
}

void scroll_t::restore_margins() {
    limits.active = 0;
}

void scroll_t::drag_start(drag_source source) {
    if (drag.active)
        return;
    drag.active = 1;
    drag.is_touch = (source == drag_source::touch) ? 1 : 0;
    drag.apply_middle_mouse_pan_speed = (source == drag_source::middle_mouse_pan) ? 1 : 0;
    drag.moved = 0;
    drag.delta = {0, 0};
    drag.travel = {0, 0};
    if (!drag.is_touch)
        g_mouse.get_relative_state(nullptr, nullptr);

    clear_speed();
}

int scroll_t::set_speed_from_drag(bool keep_delta) {
    if (!drag.active)
        return 0;
    int delta_x = 0;
    int delta_y = 0;
    if (!drag.is_touch) {
        g_mouse.get_relative_state(&delta_x, &delta_y);
        float fx = dampen_mouse_relative_pan_delta((float)delta_x);
        float fy = dampen_mouse_relative_pan_delta((float)delta_y);
        if (drag.apply_middle_mouse_pan_speed) {
            float s = game_features::gameopt_middle_mouse_pan_speed.to_float();
            if (s < 0.f)
                s = 0.f;
            if (s > 100.f)
                s = 100.f;
            const float mul = s / 100.f;
            fx *= mul;
            fy *= mul;
        }
        delta_x = (int)std::lround(fx);
        delta_y = (int)std::lround(fy);
    } else {
        const touch_t* t = get_earliest_touch();
        delta_x = -t->frame_movement.x;
        delta_y = -t->frame_movement.y;
    }
    drag.delta.x += delta_x;
    drag.delta.y += delta_y;
    drag.travel.x += std::abs(delta_x);
    drag.travel.y += std::abs(delta_y);
    if (!drag.moved
        && (drag.travel.x > config.drag_min_delta || drag.travel.y > config.drag_min_delta)) {
        drag.moved = 1;
    }
    speed_set_target(speed.x, drag.delta.x, SPEED_CHANGE_IMMEDIATE, 0);
    speed_set_target(speed.y, drag.delta.y, SPEED_CHANGE_IMMEDIATE, 0);
    if (!keep_delta) {
        drag.delta = {0, 0};
    }
    return 1;
}

int scroll_t::drag_end() {
    if (!drag.active)
        return 0;
    int has_scrolled = drag.moved;

    drag.active = 0;
    drag.moved = 0;
    drag.apply_middle_mouse_pan_speed = 0;

    if (!drag.is_touch)
        g_mouse.set_relative_mode(0);
    else if (has_scrolled) {
        const touch_t* t = get_earliest_touch();
        speed_set_target(speed.x, -t->frame_movement.x, SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(speed.y, -t->frame_movement.y, SPEED_CHANGE_IMMEDIATE, 1);
    }
    speed_set_target(speed.x, 0, config.drag_decay_time, 1);
    speed_set_target(speed.y, 0, config.drag_decay_time, 1);

    return has_scrolled;
}

int scroll_t::set_arrow_input(arrow_key_t *arrow, const arrow_key_t *opposite_arrow, float *modifier) {
    if (arrow->get_value() && (!opposite_arrow || !opposite_arrow->is_active())) {
        if (arrow->state == KEY_STATE_AXIS) {
            constant_input = 1;
            *modifier = arrow->get_normalized_value();
        }
        return 1;
    }
    return 0;
}

int scroll_t::get_direction(const mouse *m) {
    int is_inside_window = m->is_inside_window;
    int width = screen_width();
    int height = screen_height();
    if (game.is_fullscreen() && m->x < width && m->y < height) {
        // For Windows 10, in fullscreen mode, on HiDPI screens, this is needed
        // to get scrolling to work
        is_inside_window = 1;
    }
    if (!is_inside_window && !m->is_touch)
        return DIR_8_NONE;

    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
    int border = config.mouse_border;
    int x = m->x;
    int y = m->y;
    constant_input = 0;
    speed.modifier_x = 0.0f;
    speed.modifier_y = 0.0f;
    if (limits.active) {
        border = config.touch_border;
        width = limits.size.x;
        height = limits.size.y;
        x -= limits.pos.x;
        y -= limits.pos.y;
        constant_input = 1;
    }
    // mouse near map edge
    // NOTE: using <= width/height (instead of <) to compensate for rounding
    // errors caused by scaling the display. SDL adds a 1px border to either
    // the right or the bottom when the aspect ratio does not match exactly.
    if ((!m->is_touch || limits.active) && (x >= 0 && x <= width && y >= 0 && y <= height)) {
        if (x < border) {
            left = 1;
            speed.modifier_x = 1 - x / (float)border;
        } else if (x >= width - border) {
            right = 1;
            speed.modifier_x = 1 - (width - x) / (float)border;
        }
        if (y < border) {
            top = 1;
            speed.modifier_y = 1 - y / (float)border;
        } else if (y >= height - border) {
            bottom = 1;
            speed.modifier_y = 1 - (height - y) / (float)border;
        }
    }
    // keyboard/joystick arrow keys
    left |= set_arrow_input(&arrows.left, nullptr, &speed.modifier_x);
    right |= set_arrow_input(&arrows.right, &arrows.left, &speed.modifier_x);
    top |= set_arrow_input(&arrows.up, nullptr, &speed.modifier_y);
    bottom |= set_arrow_input(&arrows.down, &arrows.up, &speed.modifier_y);

    if (constant_input) {
        if (!speed.modifier_x)
            speed.modifier_x = speed.modifier_y;

        if (!speed.modifier_y)
            speed.modifier_y = speed.modifier_x;
    }

    return direction_from_sides(top, left, bottom, right);
}

int scroll_t::get_alignment_delta(int direction, int camera_max_offset, int camera_offset) {
    if (camera_offset == 0)
        return 0;

    int calc_direction = SPEED_DIRECTION_STOPPED;
    switch (direction) {
    case SPEED_DIRECTION_STOPPED:
        calc_direction = (camera_offset >= camera_max_offset / 2) ? SPEED_DIRECTION_POSITIVE : SPEED_DIRECTION_NEGATIVE;
        direction = SPEED_DIRECTION_POSITIVE;
        break;
    case SPEED_DIRECTION_NEGATIVE:
        calc_direction
          = (camera_offset >= camera_max_offset * 0.666667) ? SPEED_DIRECTION_POSITIVE : SPEED_DIRECTION_NEGATIVE;
        break;
    default:
        calc_direction = (camera_offset >= camera_max_offset / 3) ? SPEED_DIRECTION_POSITIVE : SPEED_DIRECTION_NEGATIVE;
        break;
    }
    return (calc_direction == SPEED_DIRECTION_POSITIVE) ? (camera_max_offset - camera_offset)
                                                        : (camera_offset * -direction);
}

bool scroll_t::set_speed_from_input(const mouse *m, type t) {
    if (g_args.no_mouse()) {
        clear_speed();
        return false;
    }

    const bool keep_inertia = !!game_features::gameui_keep_camera_inertia;
    if (set_speed_from_drag(keep_inertia)) {
        return true;
    }

    int direction = get_direction(m);
    if (direction == DIR_8_NONE) {
        time_millis time = !!game_features::gameui_smooth_scrolling ? config.regular_decay_time : SPEED_CHANGE_IMMEDIATE;
        speed_set_target(speed.x, 0, time, 1);
        speed_set_target(speed.y, 0, time, 1);
        return false;
    }
    if (speed.decaying)
        clear_speed();

    vec2i dir = config.direction(direction);
    int y_fraction = t == CITY ? 2 : 1;
    const auto &steps = config.steps_for(t);

    if (!game_features::gameui_smooth_scrolling && !limits.active) {
        int do_scroll = should_scroll();
        int step = steps[0];
        int align_x = 0;
        int align_y = 0;
        if (t == CITY) {
            vec2i camera_pixels = g_camera.camera_pixel_offset_internal;
            align_x = get_alignment_delta(dir.x, config.tile_x_pixels, camera_pixels.x);
            align_y = get_alignment_delta(dir.y, config.tile_y_pixels, camera_pixels.y);
        }
        speed_set_target(speed.x, (step + align_x) * dir.x * do_scroll, SPEED_CHANGE_IMMEDIATE, 0);
        speed_set_target(speed.y, ((step / y_fraction) + align_y) * dir.y * do_scroll, SPEED_CHANGE_IMMEDIATE, 0);
        return true;
    }

    int max_speed = steps[speed_factor()];
    int max_speed_x = max_speed * dir.x;
    int max_speed_y = (max_speed / y_fraction) * dir.y;

    if (!constant_input) {
        if (speed_get_current_direction(speed.x) * dir.x < 0)
            speed_invert(speed.x);

        else if (speed.x.desired_speed != max_speed_x)
            speed_set_target(speed.x, max_speed_x, config.regular_decay_time, 1);

        if (speed_get_current_direction(speed.y) * dir.y < 0)
            speed_invert(speed.y);

        else if (speed.y.desired_speed != max_speed_y)
            speed_set_target(speed.y, max_speed_y, config.regular_decay_time, 1);

    } else {
        speed_set_target(speed.x, (int)(max_speed_x * speed.modifier_x), SPEED_CHANGE_IMMEDIATE, 1);
        speed_set_target(speed.y, (int)(max_speed_y * speed.modifier_y), SPEED_CHANGE_IMMEDIATE, 1);
    }
    return true;
}

vec2i scroll_t::get_delta(const mouse* m, type t) {
    is_scrolling = set_speed_from_input(m, t);
    vec2i delta{speed_get_delta(speed.x), speed_get_delta(speed.y)};
    if (!is_scrolling) {
        speed.decaying = speed_is_changing(speed.x) || speed_is_changing(speed.y);
        is_scrolling = speed.decaying;
    }
    return delta;
}

void scroll_t::stop() {
    clear_speed();
    g_mouse.set_relative_mode(0);
    is_scrolling = 0;
    constant_input = 0;
    drag.active = 0;
    drag.apply_middle_mouse_pan_speed = 0;
    limits.active = 0;
}

void scroll_t::arrow(arrow_dir which, int value) {
    arrow_key_t *key = nullptr;
    switch (which) {
    case arrow_dir::up: key = &arrows.up; break;
    case arrow_dir::down: key = &arrows.down; break;
    case arrow_dir::left: key = &arrows.left; break;
    case arrow_dir::right: key = &arrows.right; break;
    }
    if (key)
        key->set(value);
}

void __scroll_arrow(int which, int value) {
    g_scroll.arrow(static_cast<scroll_t::arrow_dir>(which), value);
}
ANK_FUNCTION_2(__scroll_arrow)
