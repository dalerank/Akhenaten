#pragma once

#include "input/mouse.h"

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

    using function_cb = std::function<void(int, int)>;
    function_cb _onclick;

    inline vec2i pos() const { return { x, y }; }
    inline vec2i size() const { return { wsize, wsize }; }

    arrow_button &onclick(function_cb f) { _onclick = f; return *this; }
    arrow_button &onclick(std::function<void()> f) { return onclick([f] (int, int) { f(); }); }
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