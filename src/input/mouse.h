#pragma once

#include "input/touch.h"
#include "core/vec2i.h"

struct mouse_button {
    enum e_system_change { SYSTEM_NONE = 0, SYSTEM_UP = 1, SYSTEM_DOWN = 2, SYSTEM_DOUBLE_CLICK = 4 };

    bool is_down = false;      /**< Mouse button is down */
    bool went_down = false;    /**< Mouse button went down during this cycle */
    bool went_up = false;      /**< Mouse button went up during this cycle */
    bool double_click = false; /**< Mouse double clicked during this cycle */
    int system_change = SYSTEM_NONE;

    void clear();
    void update();
};

enum e_scroll {
    SCROLL_NONE = 0,
    SCROLL_UP = -1,
    SCROLL_DOWN = 1
};

struct mouse : public vec2i {
    int scrolled = SCROLL_NONE; /**< Scroll state (up/down/none) */
    mouse_button left;          /**< Left mouse button */
    mouse_button middle;        /**< Middle mouse button */
    mouse_button right;         /**< Right mouse button */
    int is_inside_window = 0;   /**< Whether the mouse is in the window */
    int is_touch = 0;           /**< Whether the mouse is a translated touch event */

    static const mouse &get();
    static mouse &ref();

    void init();
    vec2i pos() const { return *this; }
    const mouse* in_dialog() const;

    void set_inside_window(bool inside);
    void set_relative_mode(bool enabled);
    vec2i relative_state();
    vec2i warp_position(vec2i p);
    void move_relative(vec2i delta);

    void set_position(vec2i p);
    void set_left_down(bool down);
    void set_middle_down(bool down);
    void set_right_down(bool down);
    void set_scroll(int state);
    void set_from_touch(const touch_t* first, const touch_t* last);
    void reset_up_state();
    void reset_scroll();
    void reset_button_state();
    void determine_button_state();

private:
    static constexpr time_millis DOUBLE_CLICK_TIME = 500;

    bool relative_mode = false;
    vec2i relative_mode_restore;
    time_millis last_click = 0;
};

extern mouse g_mouse;

/**
 * Set cursor to the specified cursor in @link input/cursor.h @endlink
 * @param cursor_id Cursor to set
 */
void mouse_set_cursor(int cursor_id);
