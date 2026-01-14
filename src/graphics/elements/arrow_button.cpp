#include "arrow_button.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/game.h"
#include "graphics/elements/ui.h"

#include "js/js_game.h"

static const int REPEATS[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                              0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0};

static const time_millis REPEAT_MILLIS = 30;
static const unsigned int BUTTON_PRESSED_FRAMES = 3;

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

void arrow_buttons_draw(arrow_button* buttons, int num_buttons, bool tiny) {
    painter ctx = game.painter();
    for (int i = 0; i < num_buttons; i++) {
        int image_id = buttons[i].image_id;
        if (image_id < 0) {
            const bool isdown = (buttons[i].state & 0x10);
            if (tiny) {
                image_id = (isdown ? g_arrow_button_images.arrow_button_tiny_down : g_arrow_button_images.arrow_button_tiny_up).tid();
                image_id += (buttons[i].state & 0xf);
            } else {
                image_id = (isdown ? g_arrow_button_images.arrow_button_down : g_arrow_button_images.arrow_button_up).tid();
                image_id += buttons[i].pressed ? -1 : 0;
            }
        }
        else {
            image_id += (buttons[i].state & 0xf);
        }

        ctx.img_generic(image_id, vec2i{ buttons[i].x, buttons[i].y });
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

    time_millis curr_time = time_get_millis();
    int should_repeat = 0;
    if (curr_time - last_time >= REPEAT_MILLIS) {
        should_repeat = 1;
        last_time = curr_time;
    }

    for (int i = 0; i < num_buttons; i++) {
        arrow_button* btn = &buttons[i];
        if (btn->pressed) {
            btn->pressed--;
            if (!btn->pressed) {
                btn->repeats = 0;
            }
        } else {
            btn->repeats = 0;
        }
    }
    int button_id = get_arrow_button(m, buttons, num_buttons);
    if (focus_button_id) {
        *focus_button_id = button_id;
    }

    if (!button_id) {
        return 0;
    }

    arrow_button* btn = &buttons[button_id - 1];
    if (m->left.went_up) {
        btn->pressed = BUTTON_PRESSED_FRAMES;
        btn->repeats = 0;
        btn->click_handler(btn->parameter1, btn->parameter2);
        if (btn->_onclick) {
            btn->_onclick(btn->parameter1, btn->parameter2);
        }
        return button_id;
    }

    if (m->left.is_down) {
        btn->pressed = BUTTON_PRESSED_FRAMES;
        if (should_repeat) {
            btn->repeats++;
            if (btn->repeats < 48) {
                if (!REPEATS[btn->repeats]) {
                    return 0;
                }
            } else {
                btn->repeats = 47;
            }
            btn->click_handler(btn->parameter1, btn->parameter2);
            if (btn->_onclick) {
                btn->_onclick(btn->parameter1, btn->parameter2);
            }
        }
        return button_id;
    }
    return 0;
}
