#pragma once

#include "input/mouse.h"
#include "core/delegate.h"

#include "generic_button.h"

struct arrow_button {
    int x;
    int y;
    int image_id;
    int wsize;
    void (*click_handler)(int param1, int param2);
    int parameter1;
    int parameter2;
    // state
    char pressed;
    int state;
    int repeats;
    xstring _tooltip;

    using onclick_cb = inplace_function<void(int, int)>;
    using onclick_simple_cb = inplace_function<void()>;
    onclick_cb _onclick;
    onclick_simple_cb _onclick_void;

    inline vec2i pos() const { return { x, y }; }
    inline vec2i size() const { return { wsize, wsize }; }

    arrow_button &onclick(onclick_cb f) { _onclick = f; return *this; }
    arrow_button &onclick(onclick_simple_cb f) { _onclick_void = f; return *this; }
};

void arrow_buttons_draw(arrow_button* buttons, int num_buttons, bool tiny = false);
int get_arrow_button(const mouse *m, arrow_button *buttons, int num_buttons);
int arrow_buttons_handle_mouse(const mouse* m, arrow_button* buttons, int num_buttons, int* focus_button_id);

template<class T>
bool arrow_buttons_handle_mouse(const mouse *m, T &buttons, int &focus_button_id) {
    return buttons.size() > 0 
        ? arrow_buttons_handle_mouse(m, &buttons.front(), (int)buttons.size(), &focus_button_id)
        : 0;
}

inline void arrow_buttons_draw(arrow_button &button, bool tiny) {
    arrow_buttons_draw(&button, 1, tiny);
}