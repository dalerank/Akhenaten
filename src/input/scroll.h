#pragma once

#include "input/mouse.h"
#include "core/speed.h"
#include "core/archive.h"

#include <array>

struct scroll_t {
    enum class type {
        city = 0,
        empire = 1,
    };

    enum class drag_source {
        touch = 0,
        mouse = 1,
        middle_mouse_pan = 2,
    };

    enum class arrow_dir {
        up = 0,
        down = 1,
        left = 2,
        right = 3,
    };

    struct config_t {
        int mouse_border = 5;
        int touch_border = 100;
        int drag_min_delta = 4;
        int drag_decay_time = 350;
        int regular_decay_time = 75;
        int key_wait_time_after_hold = 500;
        int key_pressed = 1;
        float key_max_value = 30000.0f;
        int tile_x_pixels = 60;
        int tile_y_pixels = 30;
        float mouse_pan_log_k = 0.052f;
        std::array<int, 9> direction_x{{0, 1, 1, 1, 0, -1, -1, -1, 0}};
        std::array<int, 9> direction_y{{-1, -1, 0, 1, 1, 1, 0, -1, 0}};
        std::array<int, 11> step_city{{60, 44, 30, 20, 16, 12, 10, 8, 6, 4, 2}};
        std::array<int, 11> step_empire{{20, 15, 10, 7, 5, 4, 3, 3, 2, 2, 1}};

        const std::array<int, 11>& steps_for(type t) const { return t == type::city ? step_city : step_empire; }

        vec2i direction(int dir) const {
            return {direction_x[dir], direction_y[dir]};
        }
    } config;

    bool in_progress() const;
    bool is_smooth() const;

    vec2i get_delta(const mouse *m, type t);

    void drag_start(drag_source source);
    bool drag_end();

    void stop();

    void set_custom_margins(vec2i pos, vec2i size);
    void restore_margins();

    void arrow(arrow_dir which, int value);
    void set_mouse_input(bool enabled);

private:
    enum class key_state {
        unpressed = 0,
        pressed = 1,
        held = 2,
        axis = 3,
    };

    struct arrow_key_t {
        key_state state = key_state::unpressed;
        int value = 0;
        time_millis last_change = 0;

        bool is_active() const { return value != 0; }
    };

    struct arrows_t {
        arrow_key_t up;
        arrow_key_t down;
        arrow_key_t left;
        arrow_key_t right;
    };

    struct drag_t {
        bool active = false;
        bool is_touch = false;
        bool apply_middle_mouse_pan_speed = false;
        bool moved = false;
        vec2i delta;
        vec2i travel;
    };

    struct camera_speed_t {
        speed_type x{};
        speed_type y{};
        bool decaying = false;
        float modifier_x = 0.f;
        float modifier_y = 0.f;
    };

    struct margins_t {
        bool active = false;
        vec2i pos;
        vec2i size;
    };

    bool mouse_input = true;
    bool is_scrolling = false;
    bool constant_input = false;
    arrows_t arrows;
    drag_t drag;
    camera_speed_t speed;
    time_millis last_time = 0;
    margins_t limits;

    bool should_scroll();
    int speed_factor() const;
    void clear_speed();
    float dampen_mouse_relative_pan_delta(float d) const;
    key_state key_state_for_value(int value) const;
    int arrow_value(arrow_key_t& arrow);
    float arrow_normalized_value(arrow_key_t& arrow);
    void set_arrow(arrow_key_t& arrow, int value);
    void restart_arrow_unless(arrow_key_t& arrow, const arrow_key_t* exception);
    void restart_arrows_except(const arrow_key_t* arrow);
    bool set_arrow_input(arrow_key_t& arrow, const arrow_key_t* opposite_arrow, float& modifier);
    int get_direction(const mouse *m);
    static int direction_from_sides(bool top, bool left, bool bottom, bool right);
    static int get_alignment_delta(int direction, int camera_max_offset, int camera_offset);
    bool set_speed_from_drag(bool keep_delta);
    bool set_speed_from_input(const mouse *m, type t);
};

extern scroll_t g_scroll;

ANK_CONFIG_STRUCT(scroll_t::config_t,
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
    mouse_pan_log_k,
    direction_x,
    direction_y,
    step_city,
    step_empire)
