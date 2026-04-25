#include "arrow_button.h"

#include "graphics/elements/ui.h"

#include <cassert>
// Bitmask: 1 = do fire this repeat step (keyboard-style acceleration on hold).
static const int REPEATS[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                              0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0};

static constexpr time_millis kRepeatStepMs = 30;
static constexpr int kPressVisualFrames = 3;

// ---------------------------------------------------------------------------
// config / image bundle

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

// ---------------------------------------------------------------------------
// small helpers (mouse, repeat store, click dispatch)

static int& repeat_of(arrow_button* btn) {
    if (btn->repeats_ptr) {
        return *btn->repeats_ptr;
    }
    return btn->repeats;
}

static void call_handlers(arrow_button* b) {
    if (b->click_handler) {
        b->click_handler(b->parameter1, b->parameter2);
    }
    if (b->_onclick) {
        b->_onclick(b->parameter1, b->parameter2);
    }
    if (b->_onclick_void) {
        b->_onclick_void();
    }
}

static void update_press_state_and_repeats(const mouse* m, int hovered, arrow_button* buttons, int num) {
    const bool lmb = m->left.is_down;

    if (m->left.went_up || !lmb) {
        if (num == 1) {
            repeat_of(&buttons[0]) = 0;
        }
    }

    if (num > 1) {
        for (int i = 0; i < num; i++) {
            arrow_button* b = &buttons[i];
            const bool hold_on_this = b->allow_repeat && hovered == i + 1 && lmb;
            if (b->pressed) {
                b->pressed--;
                if (b->pressed == 0 && !hold_on_this) {
                    repeat_of(b) = 0;
                }
            } else {
                if (!hold_on_this) {
                    repeat_of(b) = 0;
                }
            }
        }
    } else if (num == 1) {
        if (buttons[0].pressed) {
            buttons[0].pressed--;
        }
        if (!hovered) {
            repeat_of(&buttons[0]) = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// public API

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
    const int hovered = get_arrow_button(m, buttons, num_buttons);
    update_press_state_and_repeats(m, hovered, buttons, num_buttons);

    if (focus_button_id) {
        *focus_button_id = hovered;
    }
    if (!hovered) {
        return 0;
    }

    arrow_button* btn = &buttons[hovered - 1];
    const bool lmb_held = m->left.is_down;

    static time_millis s_repeat_last = 0;
    int should_repeat = 0;
    {
        const time_millis t = time_get_millis();
        if (t - s_repeat_last >= kRepeatStepMs) {
            should_repeat = 1;
            s_repeat_last = t;
        }
    }

    if (btn->allow_repeat && m->left.went_down) {
        btn->pressed = kPressVisualFrames;
        repeat_of(btn) = 0;
        call_handlers(btn);
        return hovered;
    }

    if (m->left.went_up) {
        btn->pressed = kPressVisualFrames;
        repeat_of(btn) = 0;
        if (!btn->allow_repeat) {
            call_handlers(btn);
        }
        return hovered;
    }

    if (btn->allow_repeat && lmb_held) {
        btn->pressed = kPressVisualFrames;
        if (!should_repeat) {
            return 0;
        }
        int& rep = repeat_of(btn);
        rep++;
        if (rep < 48) {
            if (!REPEATS[rep]) {
                return 0;
            }
        } else {
            rep = 47;
        }
        call_handlers(btn);
        return hovered;
    }

    return 0;
}
