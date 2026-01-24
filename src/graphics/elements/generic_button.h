#pragma once

#include "core/xstring.h"
#include "input/mouse.h"
#include "graphics/text.h"
#include "graphics/elements/button.h"
#include "core/inplace_function.h"

#include <vector>
#include <functional>

struct generic_button {
    int x;
    int y;
    int width;
    int height;
    void (*left_click_handler)(int param1, int param2) = nullptr;
    void (*right_click_handler)(int param1, int param2) = nullptr;
    int parameter1 = 0;
    int parameter2 = 0;

    using onclick_cb = inplace_function<void(int, int)>;
    using onclick_void = inplace_function<void()>;
    onclick_cb _onclick;
    onclick_void _onclick_void;
    onclick_cb _onrclick;
    onclick_void _onrclick_void;
    xstring _tooltip;
    bool hovered = false;
    rect clip = { {0, 0}, {0, 0} };

    inline vec2i pos() const { return {x, y}; }
    inline vec2i size() const { return {width, height}; }

    generic_button &onclick(onclick_cb f) { _onclick = f; return *this; }
    generic_button &onclick(onclick_void f) { _onclick_void = f; return *this; }
    
    generic_button &onrclick(onclick_cb f) { _onrclick = f; return *this; }
    generic_button &onrclick(onclick_void f) { _onrclick_void = f; return *this; }
   
    generic_button &tooltip(textid t);
    generic_button &tooltip(const xstring &t);
    generic_button &tooltip(const std::initializer_list<int> &t);
};

int generic_buttons_handle_mouse(const mouse* m, vec2i pos, const generic_button* buttons, int num_buttons, int* focus_button_id);
int generic_buttons_min_handle_mouse(const mouse* m, vec2i pos, const generic_button* buttons, int num_buttons, int* focus_button_id, int minimum_button);

template<uint32_t N>
inline int generic_buttons_handle_mouse(const mouse *m, vec2i pos, const generic_button (&buttons)[N], int &focus_button_id) {
    return generic_buttons_handle_mouse(m, pos, buttons, N, &focus_button_id);
}

template<class T>
inline int generic_buttons_handle_mouse(const mouse *m, vec2i pos, const T &buttons, int &focus_button_id) {
    return buttons.size() > 0
                ? generic_buttons_handle_mouse(m, pos, &buttons.front(), (int)buttons.size(), &focus_button_id)
                : 0; 
}