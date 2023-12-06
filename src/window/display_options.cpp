#include "display_options.h"

#include "core/app.h"
#include "game/settings.h"
#include "game/system.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/window.h"
#include "input/input.h"

static void button_fullscreen(int param1, int param2);
static void button_set_resolution(int id, int param2);
static void button_cancel(int param1, int param2);

static generic_button buttons[] = {
  {128, 136, 224, 20, button_fullscreen, button_none, 1, 0},
  {128, 160, 224, 20, button_set_resolution, button_none, 1, 0},
  {128, 184, 224, 20, button_set_resolution, button_none, 2, 0},
  {128, 208, 224, 20, button_set_resolution, button_none, 3, 0},
  {128, 232, 224, 20, button_cancel, button_none, 1, 0},
};

struct display_options_data_t {
    int focus_button_id;
    void (*close_callback)(void);
};

display_options_data_t g_display_options_data;

static void init(void (*close_callback)(void)) {
    g_display_options_data.focus_button_id = 0;
    g_display_options_data.close_callback = close_callback;
}

static void draw_foreground(void) {
    auto& data = g_display_options_data;
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{96, 80}, 18, 12);

    label_draw(128, 136, 14, data.focus_button_id == 1 ? 1 : 2);
    label_draw(128, 160, 14, data.focus_button_id == 2 ? 1 : 2);
    label_draw(128, 184, 14, data.focus_button_id == 3 ? 1 : 2);
    label_draw(128, 208, 14, data.focus_button_id == 4 ? 1 : 2);
    label_draw(128, 232, 14, data.focus_button_id == 5 ? 1 : 2);

    lang_text_draw_centered(42, 0, 128, 94, 224, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw_centered(42, g_settings.is_fullscreen() ? 2 : 1, 128, 140, 224, FONT_NORMAL_BLACK_ON_DARK);

    lang_text_draw_centered(42, 3, 128, 164, 224, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(42, 4, 128, 188, 224, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(42, 5, 128, 212, 224, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(42, 6, 128, 236, 224, FONT_NORMAL_BLACK_ON_DARK);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(mouse_in_dialog(m), 0, 0, buttons, 5, &g_display_options_data.focus_button_id))
        return;

    if (input_go_back_requested(m, h)) {
        g_display_options_data.close_callback();
    }
}

static void button_fullscreen(int param1, int param2) {
    app_fullscreen(!g_settings.is_fullscreen());
    g_display_options_data.close_callback();
}

static void button_set_resolution(int id, int param2) {
    switch (id) {
    case 1:
        app_window_resize({640, 480});
        break;
    case 2:
        app_window_resize({800, 600});
        break;
    case 3:
        app_window_resize({1024, 768});
        break;
    }
    g_display_options_data.close_callback();
}

static void button_cancel(int param1, int param2) {
    g_display_options_data.close_callback();
}

void window_display_options_show(void (*close_callback)(void)) {
    window_type window = {WINDOW_DISPLAY_OPTIONS, window_draw_underlying_window, draw_foreground, handle_input};
    init(close_callback);
    window_show(&window);
}
