#include "difficulty_options.h"

#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "input/input.h"

static void arrow_button_difficulty(int is_down, int param2);
static void arrow_button_gods(int param1, int param2);

static arrow_button arrow_buttons[] = {{0, 54, 15, 24, arrow_button_difficulty, 0, 0},
                                       {24, 54, 17, 24, arrow_button_difficulty, 1, 0},
                                       {24, 102, 21, 24, arrow_button_gods, 2, 0}};

static struct {
    void (*close_callback)(void);
} data;

static void draw_foreground(int) {
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{48, 80}, 24, 12);

    lang_text_draw_centered(153, 0, 48, 94, 384, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw_centered(153, g_settings.difficulty() + 1, 70, 142, 244, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_centered(153, g_settings.gods_enabled ? 7 : 6, 70, 190, 244, FONT_NORMAL_BLACK_ON_LIGHT);
    arrow_buttons_draw(/*{288, 80},*/ arrow_buttons, 3);
    lang_text_draw_centered(153, 8, 48, 246, 384, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (arrow_buttons_handle_mouse(mouse_in_dialog(m), /*{288, 80}*/ arrow_buttons, 3, 0))
        return;

    if (input_go_back_requested(m, h))
        data.close_callback();
}

static void arrow_button_difficulty(int is_down, int param2) {
    if (is_down) {
        g_settings.difficulty.decrease();
    } else {
        g_settings.difficulty.increase();
    }
}

static void arrow_button_gods(int param1, int param2) {
    g_settings.toggle_gods_enabled();
}

void window_difficulty_options_show(void (*close_callback)(void)) {
    static window_type window = {
        WINDOW_DIFFICULTY_OPTIONS,
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };
    data.close_callback = close_callback;
    window_show(&window);
}
