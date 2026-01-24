#include "image_button.h"

#include "io/gamefiles/lang.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "sound/sound.h"
#include "core/custom_span.hpp"
#include "game/game.h"

#define PRESSED_EFFECT_MILLIS 100
#define PRESSED_REPEAT_INITIAL_MILLIS 300
#define PRESSED_REPEAT_MILLIS 50

static void fade_pressed_effect(image_button* buttons, int num_buttons) {
    time_millis current_time = time_get_millis();
    const bool left_is_down = mouse::get().left.is_down;
    for (int i = 0; i < num_buttons; i++) {
        image_button& btn = buttons[i];
        if (!btn.pressed) {
            continue;
        }

        if (current_time - btn.pressed_since > PRESSED_EFFECT_MILLIS) {
            if (btn.button_type != IB_BUILD && btn.button_type != IB_OVERSEER && !left_is_down)
                btn.pressed = 0;
        }
    }
}

static void remove_pressed_effect_build(image_button* buttons, int num_buttons) {
    // un-press all buttons
    auto btns = make_span(buttons, num_buttons);
    for (auto &btn: btns) {
        if (btn.pressed) {
            btn.pressed = 0;
            btn.floating = 0;
        }
    }
}

void image_buttons_draw(vec2i pos, image_button* buttons, int num_buttons, int starting_button) {
    painter ctx = game.painter();
    fade_pressed_effect(buttons, num_buttons);
    for (int i = starting_button; i < starting_button + num_buttons; i++) {
        image_button* btn = &buttons[i];

        int image_id = image_id_from_group(btn->image_collection, btn->image_group) + btn->image_offset;
        if (btn->enabled) {
            if (btn->pressed) {
                image_id += 2;
            } else if (btn->hovered) {
                image_id += 1;
            }
        } else {
            image_id += 3;
        }

        ctx.img_generic(image_id, pos + vec2i{btn->x, btn->y});
    }
}

bool image_buttons_handle_mouse(const mouse* m, vec2i pos, image_button* buttons, int num_buttons, int* focus_button_id) {
    fade_pressed_effect(buttons, num_buttons);
    //    remove_pressed_effect_build(buttons, num_buttons);
    image_button* hit_button = 0;
    if (focus_button_id)
        *focus_button_id = 0;

    for (int i = 0; i < num_buttons; i++) {
        image_button* btn = &buttons[i];
        if (btn->hovered)
            btn->hovered--;

        if (pos.x + btn->x <= m->x && pos.x + btn->x + btn->width > m->x && pos.y + btn->y <= m->y
            && pos.y + btn->y + btn->height > m->y) {
            if (focus_button_id)
                *focus_button_id = i + 1;

            if (btn->enabled) {
                btn->hovered = 2;
                hit_button = btn;
            }
        } else if (btn->floating) {
            if (btn->button_type != IB_BUILD) // remove "press" when hovering away from button
                btn->pressed = 0;
            else if (!m->left.is_down) { // remove "press" when fully canceling
                btn->pressed = 0;
                btn->floating = 0;
            }
        }
    }

    if (!hit_button) {
        return false;
    }

    if (hit_button->button_type == IB_SCROLL) {
        if (!m->left.went_down && !m->left.is_down) {
            return false;
        }
    }

    // on click, press button and set reminder to this button (floating = true)
    if (m->left.went_down && hit_button->button_type != IB_SCROLL) {
        hit_button->pressed = 1;
        hit_button->floating = 1;
    }
    if (m->left.is_down && hit_button->floating) // resume "pressing" when mouse is over the button again
        hit_button->pressed = 1;

    if (m->left.went_up) {
        g_sound.play_effect(SOUND_EFFECT_ICON);
        remove_pressed_effect_build(buttons, num_buttons);
        if (hit_button->button_type == IB_BUILD || hit_button->button_type == IB_OVERSEER) {
            hit_button->pressed = 1;
        }
        hit_button->floating = 0;
        hit_button->pressed_since = time_get_millis();

        if (hit_button->left_click_handler) {
            hit_button->left_click_handler(hit_button->parameter1, hit_button->parameter2);
        }
        if (hit_button->_onclick) {
            hit_button->_onclick(hit_button->parameter1, hit_button->parameter2);
        }
        if (hit_button->_onclick_void) {
            hit_button->_onclick_void();
        }
    } else if (m->right.went_up) {
        if (hit_button->button_type == IB_BUILD || hit_button->button_type == IB_OVERSEER)
            hit_button->pressed = 1;
        hit_button->floating = 0;
        hit_button->pressed_since = time_get_millis();

        if (hit_button->right_click_handler) {
            hit_button->right_click_handler(hit_button->parameter1, hit_button->parameter2);
        }
        if (hit_button->_onrclick) {
            hit_button->_onrclick(hit_button->parameter1, hit_button->parameter2);
        }
        if (hit_button->_onrclick_void) {
            hit_button->_onrclick_void();
        }
    } else if (hit_button->button_type == IB_SCROLL && m->left.is_down) {
        time_millis delay = hit_button->pressed == 2 ? PRESSED_REPEAT_MILLIS : PRESSED_REPEAT_INITIAL_MILLIS;
        if (time_get_millis() - hit_button->pressed_since >= delay) {
            hit_button->pressed = 2;
            hit_button->floating = 0;
            hit_button->pressed_since = time_get_millis();

            if (hit_button->left_click_handler) {
                hit_button->left_click_handler(hit_button->parameter1, hit_button->parameter2);
            }
        }
    }
    return true;
}

void image_buttons_release_press(image_button* buttons, int num_buttons) {
    remove_pressed_effect_build(buttons, num_buttons);
}

image_button &image_button::tooltip(textid t) { _tooltip = (pcstr)lang_get_string(t); return *this; }
image_button &image_button::tooltip(const xstring &t) { _tooltip = t; return *this; }
