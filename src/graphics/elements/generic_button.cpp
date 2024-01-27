#include "generic_button.h"

#include "input/mouse.h"

namespace ui {
    struct state {
        vec2i offset;
        std::vector<generic_button> buttons;
    };

    state g_state;
    generic_button dummy;
}

void ui::begin_window(vec2i offset) {
    g_state.offset = offset;
    g_state.buttons.clear();
}

int ui::handle_mouse(const mouse *m) {
    int tmp_btn;
    return generic_buttons_handle_mouse(m, g_state.offset, g_state.buttons, tmp_btn);
}

int ui::button_hover(const mouse *m) {
    for (auto &btn : g_state.buttons) {
        if (is_button_hover(btn, g_state.offset)) {
            return (std::distance(&g_state.buttons.front(), &btn) + 1);
        }
    }

    return 0;
}

generic_button &ui::button(pcstr label, vec2i pos, vec2i size) {
    const vec2i offset = g_state.offset;

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    button_border_draw(offset.x + pos.x, offset.y + pos.y, size.x, size.y, focused ? 1 : 0);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    return g_state.buttons.back();
}


generic_button &ui::button(uint32_t id) {
    return (id < g_state.buttons.size()) ? g_state.buttons[id] : dummy;
}

static int get_button(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons) {
    for (int i = 0; i < num_buttons; i++) {
        if (x + buttons[i].x <= m->x && x + buttons[i].x + buttons[i].width > m->x && y + buttons[i].y <= m->y
            && y + buttons[i].y + buttons[i].height > m->y) {
            return i + 1;
        }
    }
    return 0;
}

static int get_button_min(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons, int minimum_button) {
    for (int i = minimum_button; i < num_buttons; i++) {
        if (x + buttons[i].x <= m->x && x + buttons[i].x + buttons[i].width > m->x && y + buttons[i].y <= m->y
            && y + buttons[i].y + buttons[i].height > m->y) {
            return i + 1;
        }
    }
    return 0;
}

int generic_buttons_handle_mouse(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons, int* focus_button_id) {
    int button_id = get_button(m, x, y, buttons, num_buttons);
    if (focus_button_id) {
        *focus_button_id = button_id;
    }

    if (!button_id) {
        return 0;
    }

    const generic_button* button = &buttons[button_id - 1];
    if (m->left.went_up) {
        button->left_click_handler(button->parameter1, button->parameter2);
        if (button->_onclick) {
            button->_onclick(button->parameter1, button->parameter2);
        }
    } else if (m->right.went_up) {
        button->right_click_handler(button->parameter1, button->parameter2);
    } else {
        return 0;
    }

    return button_id;
}

int generic_buttons_min_handle_mouse(const mouse* m, int x, int y, const generic_button* buttons, int num_buttons, int* focus_button_id, int minimum_button) {
    int button_id = get_button_min(m, x, y, buttons, num_buttons, minimum_button);
    if (focus_button_id)
        *focus_button_id = button_id;

    if (!button_id)
        return 0;

    const generic_button* button = &buttons[button_id - 1];
    if (m->left.went_up)
        button->left_click_handler(button->parameter1, button->parameter2);

    else if (m->right.went_up)
        button->right_click_handler(button->parameter1, button->parameter2);
    else
        return 0;

    return button_id;
}

bool is_button_hover(generic_button &button, vec2i context) {
    const mouse *m = mouse_get();
    vec2i bpos = context + vec2i{button.x, button.y};
    return (   bpos.x <= m->x && bpos.x + button.width > m->x
            && bpos.y <= m->y && bpos.y + button.height > m->y);
}