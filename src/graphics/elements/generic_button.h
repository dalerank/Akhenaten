#pragma once

#include "core/string.h"
#include "input/mouse.h"
#include "graphics/text.h"
#include "graphics/elements/button.h"

#include <vector>
#include <cstdint>
#include <functional>

struct generic_button {
    int x;
    int y;
    int width;
    int height;
    void (*left_click_handler)(int param1, int param2);
    void (*right_click_handler)(int param1, int param2);
    int parameter1;
    int parameter2;

    std::function<void(int,int)> onclick;
};

int generic_buttons_handle_mouse(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons, int* focus_button_id);
int generic_buttons_min_handle_mouse(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons, int* focus_button_id, int minimum_button);

bool is_button_hover(generic_button &button, vec2i context);

template<class T, uint32_t N>
inline int generic_buttons_handle_mouse(const mouse *m, vec2i pos, const T (&buttons)[N], int &focus_button_id) {
    return generic_buttons_handle_mouse(m, pos.x, pos.y, buttons, N, &focus_button_id);
}

template<class T>
inline int generic_buttons_handle_mouse(const mouse *m, vec2i pos, const T &buttons, int &focus_button_id) {
    return generic_buttons_handle_mouse(m, pos.x, pos.y, &buttons.front(), (int)buttons.size(), &focus_button_id);
}

namespace ui {

struct state {
    vec2i offset;
    std::vector<generic_button> buttons;
};

extern state g_state;

inline void begin_window(vec2i offset) {
    g_state.offset = offset;
    g_state.buttons.clear();
}

inline int handle_mouse(const mouse *m) {
    int tmp_btn;
    return generic_buttons_handle_mouse(m, g_state.offset, g_state.buttons, tmp_btn);
}

template<class Func>
void button(pcstr label, vec2i pos, vec2i size, Func func) {
    const vec2i offset = g_state.offset;

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0, func});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    button_border_draw(offset.x + pos.x, offset.y + pos.y, size.x, size.y, focused ? 1 : 0);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
}

}