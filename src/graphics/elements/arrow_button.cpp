#include "arrow_button.h"

#include "graphics/elements/ui.h"

#include "js/js_game.h"

static const int REPEATS[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                              0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0};

static const time_millis REPEAT_MILLIS = 30;
static const unsigned int BUTTON_PRESSED_FRAMES = 3;

static int& repeat_storage(arrow_button* btn) {
    if (btn->repeats_ptr) {
        return *btn->repeats_ptr;
    }
    return btn->repeats;
}

struct arrow_button_images_t {
    image_desc arrow_button_tiny_down;
    image_desc arrow_button_tiny_up;
    image_desc arrow_button_down;
    image_desc arrow_button_up;
};

arrow_button_images_t g_arrow_button_images;

ANK_CONFIG_STRUCT(arrow_button_images_t,
                  arrow_button_tiny_down,
                  arrow_button_tiny_up,
                  arrow_button_down,
                  arrow_button_up)

void ANK_REGISTER_CONFIG_ITERATOR(config_load_arrowbutton_options) {
    g_config_arch.r("uioptions", g_arrow_button_images);
    assert(g_arrow_button_images.arrow_button_tiny_down.valid() && "Incorrect image desc loaded");
}

void arrow_buttons_draw(arrow_button* buttons, int num_buttons, bool tiny, vec2i base_offset) {
    for (int i = 0; i < num_buttons; i++) {
        int image_id = buttons[i].image_id;
        if (image_id < 0) {
            const bool isdown = (buttons[i].state & 0x10);
            if (tiny) {
                image_id = (isdown ? g_arrow_button_images.arrow_button_tiny_down : g_arrow_button_images.arrow_button_tiny_up).tid();
                image_id += (buttons[i].state & 0xf);
            } else {
                image_id = (isdown ? g_arrow_button_images.arrow_button_down : g_arrow_button_images.arrow_button_up).tid();
                const bool depress_look = (buttons[i].state & 0xf) == 2 || (buttons[i].pressed != 0);
                image_id += depress_look ? -1 : 0;
            }
        } else {
            image_id += (buttons[i].state & 0xf);
        }

        ui::image_abs(image_id, base_offset + vec2i{ buttons[i].x, buttons[i].y });
    }
}

int get_arrow_button(const mouse* m, arrow_button* buttons, int num_buttons) {
    for (int i = 0; i < num_buttons; i++) {
        if (buttons[i].x <= m->x && buttons[i].x + buttons[i].wsize > m->x
            && buttons[i].y <= m->y && buttons[i].y + buttons[i].wsize > m->y) {
            return i + 1;
        }
    }

    return 0;
}

int arrow_buttons_handle_mouse(const mouse* m, arrow_button* buttons, int num_buttons, int* focus_button_id) {
    static time_millis last_time = 0;

    const int hovered_id = get_arrow_button(m, buttons, num_buttons);
    const bool lmb_held = m->left.is_down;

    if (m->left.went_up || !lmb_held) {
        if (num_buttons == 1) {
            repeat_storage(&buttons[0]) = 0;
        }
    }

    if (num_buttons > 1) {
        for (int i = 0; i < num_buttons; i++) {
            arrow_button* btn = &buttons[i];
            const bool hold_same_button = btn->allow_repeat && hovered_id == i + 1 && lmb_held;
            if (btn->pressed) {
                btn->pressed--;
                if (!btn->pressed) {
                    if (!hold_same_button) {
                        repeat_storage(btn) = 0;
                    }
                }
            } else {
                if (!hold_same_button) {
                    repeat_storage(btn) = 0;
                }
            }
        }
    } else if (num_buttons == 1) {
        if (buttons[0].pressed) {
            buttons[0].pressed--;
        }
        if (!hovered_id) {
            repeat_storage(&buttons[0]) = 0;
        }
    }
    int button_id = hovered_id;
    if (focus_button_id) {
        *focus_button_id = button_id;
    }

    if (!button_id) {
        return 0;
    }

    time_millis curr_time = time_get_millis();
    int should_repeat = 0;
    if (curr_time - last_time >= REPEAT_MILLIS) {
        should_repeat = 1;
        last_time = curr_time;
    }

    arrow_button* btn = &buttons[button_id - 1];
    if (btn->allow_repeat && m->left.went_down) {
        btn->pressed = BUTTON_PRESSED_FRAMES;
        repeat_storage(btn) = 0;
        if (btn->click_handler) {
            btn->click_handler(btn->parameter1, btn->parameter2);
        }
        if (btn->_onclick) {
            btn->_onclick(btn->parameter1, btn->parameter2);
        }
        if (btn->_onclick_void) {
            btn->_onclick_void();
        }
        return button_id;
    }

    if (m->left.went_up) {
        btn->pressed = BUTTON_PRESSED_FRAMES;
        repeat_storage(btn) = 0;
        if (!btn->allow_repeat) {
            if (btn->click_handler) {
                btn->click_handler(btn->parameter1, btn->parameter2);
            }
            if (btn->_onclick) {
                btn->_onclick(btn->parameter1, btn->parameter2);
            }
            if (btn->_onclick_void) {
                btn->_onclick_void();
            }
        }
        return button_id;
    }

    if (btn->allow_repeat && lmb_held) {
        btn->pressed = BUTTON_PRESSED_FRAMES;
        if (should_repeat) {
            int& rep = repeat_storage(btn);
            rep++;
            if (rep < 48) {
                if (!REPEATS[rep]) {
                    return 0;
                }
            } else {
                rep = 47;
            }
            if (btn->click_handler) {
                btn->click_handler(btn->parameter1, btn->parameter2);
            }
            if (btn->_onclick) {
                btn->_onclick(btn->parameter1, btn->parameter2);
            }
            if (btn->_onclick_void) {
                btn->_onclick_void();
            }
            return button_id;
        }
        return 0;
    }
    return 0;
}
