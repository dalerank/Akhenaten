#pragma once

#include "button.h"
#include "input/mouse.h"

#include <vector>
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
    return generic_buttons_handle_mouse(m, pos.x, pos.y, &buttons.front(), buttons.size(), &focus_button_id);
}