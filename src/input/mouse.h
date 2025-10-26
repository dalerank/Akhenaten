#pragma once

#include "input/touch.h"
#include "core/vec2i.h"

struct mouse_button {
    bool is_down;      /**< Mouse button is down */
    bool went_down;    /**< Mouse button went down during this cycle */
    bool went_up;      /**< Mouse button went up during this cycle */
    bool double_click; /**< Mouse double clicked during this cycle */
    int system_change;
};

enum e_scroll { 
    SCROLL_NONE = 0, 
    SCROLL_UP = -1, 
    SCROLL_DOWN = 1 
};

struct mouse : public vec2i {
    int scrolled;         /**< Scroll state (up/down/none) */
    mouse_button left;    /**< Left mouse button */
    mouse_button middle;  /**< Middle mouse button */
    mouse_button right;   /**< Right mouse button */
    int is_inside_window; /**< Whether the mouse is in the window */
    int is_touch;         /**< Whether the mouse is a translated touch event */

    void set_inside_window(int inside);
    vec2i pos() const { return *this; }
    void init();

    static const mouse &get();
    static mouse &ref();
    void set_position(vec2i p);
};

extern mouse g_mouse;


void mouse_set_left_down(int down);

void mouse_set_middle_down(int down);

void mouse_set_right_down(int down);

void mouse_set_scroll(int state);


void mouse_set_from_touch(const touch_t * first, const touch_t * last);

void mouse_reset_up_state(void);

void mouse_reset_scroll(void);

void mouse_reset_button_state(void);

void mouse_determine_button_state(void);

const mouse* mouse_in_dialog(const mouse* m);