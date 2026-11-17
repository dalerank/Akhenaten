#pragma once

#include "core/vec2i.h"
#include "core/system_time.h"

#include <array>
#include <cstdint>

constexpr int MAX_ACTIVE_TOUCHES = 2;

enum class e_touch_mode { original = 0, touchpad = 1, direct = 2, count = 3 };

struct touch_t {
    bool in_use = false;
    bool has_started = false;
    bool has_moved = false;
    bool has_ended = false;
    vec2i start_point;
    vec2i current_point;
    vec2i previous_frame_point;
    vec2i frame_movement;
    vec2i last_movement;
    time_millis start_time = 0;
    time_millis last_change_time = 0;

    bool not_click() const;
    bool was_click() const;
    bool start_delayed() const;
};

struct touch_input_t {
    const touch_t* earliest() const;
    const touch_t* latest() const;
    // Like earliest(), but includes fingers still in the start_delayed window.
    const touch_t* earliest_raw() const;
    int active_count() const;

    bool was_double_click(const touch_t& t) const;
    bool is_scroll() const;
    int get_scroll();

    void reset(bool reset_old_touch);
    void clear_all();

    void finger_down(int64_t finger_id, vec2i start_coords, time_millis start_time);
    void finger_move(int64_t finger_id, vec2i current_coords, time_millis current_time);
    void finger_up(int64_t finger_id, time_millis current_time);

    bool to_mouse();

    void set_mode(e_touch_mode m) { mode = m; }
    void cycle_mode();

private:
    enum class e_emulated_click { none, left, right };

    std::array<touch_t, MAX_ACTIVE_TOUCHES + 1> finger{};
    std::array<int64_t, MAX_ACTIVE_TOUCHES> finger_ids{};
    touch_t old_touch;
    int last_scroll_position = 0;
    e_touch_mode mode = e_touch_mode::original;
    e_emulated_click touchpad_mode_click_type = e_emulated_click::none;

    int index_of_finger(int64_t finger_id) const;
    int unused_index() const;
    bool any_went_up() const;
    bool handle_emulated_mouse_clicks();
    void handle_mouse_touchpad();
    void handle_mouse_direct();
};

extern touch_input_t g_touch;
