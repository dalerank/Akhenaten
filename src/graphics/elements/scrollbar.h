#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "input/mouse.h"

#include <functional>

struct scrollbar_t {
    vec2i pos;
    int height;
    void (*on_scroll_callback)(void);
    int dot_padding;
    bool always_visible;
    int max_scroll_position;
    int scroll_position;
    int is_dragging_scroll;
    int scroll_position_drag;
    bool thin;

    void init(int scroll_position, int max_scroll_position);

    std::function<void()> _onscroll;

    template<class Func> scrollbar_t &onscroll(Func f) { _onscroll = f; return *this; }
};

/**
 * Resets the text to the specified scroll position and forces recalculation of lines
 * @param scrollbar Scrollbar
 * @param scroll_position Scroll position to set
 */
void scrollbar_reset(scrollbar_t* scrollbar, int scroll_position);

/**
 * Update the max position, adjusting the scroll position if necessary
 * @param scrollbar Scrollbar
 * @param max_scroll_position New max position
 */
void scrollbar_update_max(scrollbar_t* scrollbar, int max_scroll_position);

/**
 * Draws the scrollbar
 * @param scrollbar Scrollbar
 */
void scrollbar_draw(scrollbar_t* scrollbar);

/**
 * Handles mouse interaction with the scrollbar and scroll wheel
 * @param scrollbar Scrollbar
 * @param m Mouse state
 * @return True if any interaction was handled
 */
int scrollbar_handle_mouse(scrollbar_t* scrollbar, const mouse* m);
