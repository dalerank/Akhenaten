#include "speed_options.h"

#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "game/game.h"
#include "input/input.h"

static void button_ok(int param1, int param2);
static void button_cancel(int param1, int param2);

static void arrow_button_game(int is_down, int param2);
static void arrow_button_scroll(int is_down, int param2);

static generic_button buttons[] = {
  {144, 232, 192, 20, button_ok, button_none, 1, 0},
  {144, 262, 192, 20, button_cancel, button_none, 1, 0},
};

static arrow_button arrow_buttons[] = {
  {112, 100, 17, 24, arrow_button_game, 1, 0},
  {136, 100, 15, 24, arrow_button_game, 0, 0},
  {112, 136, 17, 24, arrow_button_scroll, 1, 0},
  {136, 136, 15, 24, arrow_button_scroll, 0, 0},
};

static struct {
    int focus_button_id;
    void (*close_callback)(void);

    int original_game_speed;
    int original_scroll_speed;
} data;

static void init(void (*close_callback)()) {
    data.focus_button_id = 0;
    data.close_callback = close_callback;
    data.original_game_speed = game.game_speed;
    data.original_scroll_speed = g_settings.scroll_speed;
}

static void draw_foreground(int) {
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{80, 80}, 20, 14);
    // ok/cancel labels
    small_panel_draw({ 144, 232 }, 12, data.focus_button_id == 1 ? 1 : 2);
    small_panel_draw({ 144, 262 }, 12, data.focus_button_id == 2 ? 1 : 2);

    // title
    lang_text_draw_centered(45, 0, 96, 92, 288, FONT_LARGE_BLACK_ON_LIGHT);
    // ok/cancel label texts
    lang_text_draw_centered(45, 4, 128, 236, 224, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(45, 1, 128, 266, 224, FONT_NORMAL_BLACK_ON_DARK);
    // game speed
    lang_text_draw(45, 2, 112, 146, FONT_SMALL_PLAIN);
    text_draw_percentage(game.game_speed, 328, 146, FONT_SMALL_PLAIN);
    // scroll speed
    lang_text_draw(45, 3, 112, 182, FONT_SMALL_PLAIN);
    text_draw_percentage(g_settings.scroll_speed, 328, 182, FONT_SMALL_PLAIN);

    arrow_buttons_draw(/*{160, 40},*/ arrow_buttons, 4);
    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, {0, 0}, buttons, 2, &data.focus_button_id)
        || arrow_buttons_handle_mouse(m_dialog, /*{160, 40},*/ arrow_buttons, 4, 0)) {
        return;
    }

    if (input_go_back_requested(m, h)) {
        data.close_callback();
    }
}

static void button_ok(int param1, int param2) {
    data.close_callback();
}

static void button_cancel(int param1, int param2) {
    game.game_speed = data.original_game_speed;
    g_settings.scroll_speed = data.original_scroll_speed;
    data.close_callback();
}

static void arrow_button_game(int is_down, int param2) {
    if (is_down)
        game.decrease_game_speed();
    else {
        game.increase_game_speed();
    }
}

static void arrow_button_scroll(int is_down, int param2) {
    if (is_down)
        g_settings.decrease_scroll_speed();
    else {
        g_settings.increase_scroll_speed();
    }
}

void window_speed_options_show(void (*close_callback)(void)) {
    window_type window = {
        WINDOW_SPEED_OPTIONS,
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };
    init(close_callback);
    window_show(&window);
}
