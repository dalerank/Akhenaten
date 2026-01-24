#pragma once

#include "button.h"
#include "input/mouse.h"
#include "core/xstring.h"
#include "core/system_time.h"
#include "core/inplace_function.h"

enum {
    IB_BUILD = 2,
    IB_NORMAL = 4,
    IB_SCROLL = 6,
    IB_OVERSEER = 8
};

struct image_button {
    int x;
    int y;
    int width;
    int height;
    short button_type;
    uint32_t image_collection;
    uint32_t image_group;
    int image_offset;
    void (*left_click_handler)(int param1, int param2) = nullptr;
    void (*right_click_handler)(int param1, int param2) = nullptr;
    int parameter1;
    int parameter2;
    bool enabled;
    // state
    char pressed;
    char floating;
    uint8_t hovered;
    time_millis pressed_since;
    xstring _tooltip;

    using onclick_cb = inplace_function<void(int, int)>;
    using onclick_void = inplace_function<void()>;

    onclick_cb _onclick, _onrclick;
    onclick_void _onclick_void, _onrclick_void;

    image_button &onclick(onclick_cb f) { _onclick = f; return *this; }
    image_button &onclick(onclick_void f) { _onclick_void = f; return *this; }

    image_button &onrclick(onclick_cb f) { _onrclick = f; return *this; }
    image_button &onrclick(onclick_void f) { _onrclick_void = f; return *this; }

    image_button &tooltip(textid t);
    image_button &tooltip(const xstring &t);
    inline vec2i pos() const { return { x, y }; }
    inline vec2i size() const { return { width, height }; }
};

template<size_t N>
bool image_buttons_handle_mouse(const mouse *m, vec2i pos, image_button(&buttons)[N], int &focus_button_id) {
    return image_buttons_handle_mouse(m, pos, std::begin(buttons), (int)N, &focus_button_id);
}

template<class T>
bool image_buttons_handle_mouse(const mouse *m, vec2i pos, T &buttons, int &focus_button_id) {
    return buttons.size() > 0
        ? image_buttons_handle_mouse(m, pos.x, pos.y, &buttons.front(), (int)buttons.size(), &focus_button_id)
        : 0;
}

template<class T>
void image_buttons_draw(vec2i pos, T &buttons, int starting_button = 0) {
    image_buttons_draw(pos, std::begin(buttons), (int)std::size(buttons), starting_button);
}

void image_buttons_draw(vec2i pos, image_button *buttons, int num_buttons, int starting_button = 0);
bool image_buttons_handle_mouse(const mouse *m, vec2i pos, image_button *buttons, int num_buttons, int *focus_button_id);

void image_buttons_release_press(image_button *buttons, int num_buttons);
