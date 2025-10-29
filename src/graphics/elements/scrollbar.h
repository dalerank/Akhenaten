#pragma once

#include "graphics/color.h"
#include "graphics/font.h"
#include "input/mouse.h"

#include <functional>

struct scrollbar_t {
    vec2i pos;
    int height;
    void (*on_scroll_callback)(void) = nullptr;
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

void scrollbar_reset(scrollbar_t* scrollbar, int scroll_position);
void scrollbar_update_max(scrollbar_t* scrollbar, int max_scroll_position);
void scrollbar_draw(vec2i offset, scrollbar_t* scrollbar);
int scrollbar_handle_mouse(vec2i offset, scrollbar_t* scrollbar, const mouse* m);
