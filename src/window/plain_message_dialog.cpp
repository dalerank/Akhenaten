#include "plain_message_dialog.h"

#include "core/string.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"

static void button_ok(int param1, int param2);

static image_button buttons[] = {
  {223, 140, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 0, button_ok, button_none, 1, 0, 1},
};

static struct {
    const uint8_t* title;
    const uint8_t* message;
} data;

static int init(int title, int message) {
    if (window_is(WINDOW_PLAIN_MESSAGE_DIALOG)) {
        // don't show popup over popup
        return 0;
    }
    data.title = translation_for(title);
    data.message = translation_for(message);
    return 1;
}

static void draw_background(int) {
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{80, 80}, 30, 12);
    text_draw_centered(data.title, 80, 100, 480, FONT_LARGE_BLACK_ON_LIGHT, 0);
    text_draw_multiline(data.message, 100, 140, 450, FONT_NORMAL_BLACK_ON_LIGHT, 0);
    graphics_reset_dialog();
}

static void draw_foreground(int) {
    graphics_set_to_dialog();
    image_buttons_draw({80, 80}, buttons, 1);
    graphics_reset_dialog();
}

static void close(void) {
    window_go_back();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (image_buttons_handle_mouse(mouse_in_dialog(m), {80, 80}, buttons, 1, 0))
        return;
    if (input_go_back_requested(m, h) || h->enter_pressed)
        close();
}

static void button_ok(int param1, int param2) {
    close();
}

void window_plain_message_dialog_show(int title, int message) {
    if (init(title, message)) {
        window_type window = {
            WINDOW_PLAIN_MESSAGE_DIALOG,
            draw_background,
            draw_foreground,
            handle_input
        };
        window_show(&window);
    }
}
