#ifndef GRAPHICS_IMAGE_BUTTON_H
#define GRAPHICS_IMAGE_BUTTON_H

#include "button.h"
#include "input/mouse.h"

#include "core/time.h"

enum { IB_BUILD = 2, IB_NORMAL = 4, IB_SCROLL = 6, IB_OVERSEER = 8 };

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
    char enabled;
    // state
    char pressed;
    char floating;
    char focused;
    time_millis pressed_since;
};

void image_buttons_draw(int x, int y, image_button* buttons, int num_buttons, int starting_button = 0);

bool image_buttons_handle_mouse(const mouse* m, int x, int y, image_button* buttons, int num_buttons,
                                int* focus_button_id);
void image_buttons_release_press(image_button* buttons, int num_buttons);

#endif // GRAPHICS_IMAGE_BUTTON_H
