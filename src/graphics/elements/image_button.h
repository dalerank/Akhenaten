#pragma once

#include "button.h"
#include "input/mouse.h"

#include "core/time.h"

#include <utility>

enum { 
    IB_BUILD = 2,
    IB_NORMAL = 4,
    IB_SCROLL = 6,
    IB_OVERSEER = 8
};

struct image_button {
    short x_offset;
    short y_offset;
    short width;
    short height;
    short button_type;
    unsigned int image_collection;
    unsigned int image_group;
    short image_offset;
    void (*left_click_handler)(int param1, int param2);
    void (*right_click_handler)(int param1, int param2);
    int parameter1;
    int parameter2;
    bool enabled;
    // state
    char pressed;
    char floating;
    char focused;
    time_millis pressed_since;
};

template<class T>
bool image_buttons_handle_mouse(const mouse *m, vec2i pos, T &buttons, int &focus_button_id) {
    return image_buttons_handle_mouse(m, pos.x, pos.y, std::begin(buttons), (int)std::size(buttons), &focus_button_id);
}

template<class T>
void image_buttons_draw(vec2i pos, T &buttons, int starting_button = 0) {
    image_buttons_draw(pos.x, pos.y, std::begin(buttons), (int)std::size(buttons), starting_button);
}

void image_buttons_draw(int x, int y, image_button* buttons, int num_buttons, int starting_button = 0);
bool image_buttons_handle_mouse(const mouse* m, int x, int y, image_button* buttons, int num_buttons, int* focus_button_id);
void image_buttons_release_press(image_button* buttons, int num_buttons);
