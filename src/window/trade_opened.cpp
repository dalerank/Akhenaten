#include "trade_opened.h"

#include "empire/empire.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/window_advisors.h"
#include "window/window_empire.h"
#include "city/constants.h"

static void button_advisor(int advisor, int param2);
static void button_close(int param1, int param2);

static image_button image_buttons[] = {
  {92, 248, 28, 28, IB_NORMAL, GROUP_MESSAGE_ADVISOR_BUTTONS, 12, button_advisor, button_none, ADVISOR_TRADE, 0, 1},
  {522, 252, 24, 24, IB_NORMAL, GROUP_CONTEXT_ICONS, 4, button_close, button_none, 0, 0, 1},
};

static int selected_city;

static void draw_background(int) {
    window_draw_underlying_window(UiFlags_None);
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{80, 64}, 30, 14);
    lang_text_draw_centered(142, 0, 80, 80, 480, FONT_LARGE_BLACK_ON_LIGHT);
    if (g_empire.city(selected_city)->is_sea_trade) {
        lang_text_draw_multiline(142, 1, vec2i{112, 120}, 416, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_multiline(142, 3, vec2i{112, 184}, 416, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_multiline(142, 1, vec2i{112, 152}, 416, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    lang_text_draw(142, 2, 128, 256, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

static void draw_foreground(int) {
    graphics_set_to_dialog();
    image_buttons_draw({0, 0}, image_buttons, 2);
    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (image_buttons_handle_mouse(mouse_in_dialog(m), {0, 0}, image_buttons, 2, 0))
        return;
    if (input_go_back_requested(m, h))
        window_empire_show();
}

static void button_advisor(int advisor, int param2) {
    window_advisors_show_advisor((e_advisor)advisor);
}

static void button_close(int param1, int param2) {
    window_empire_show();
}

void window_trade_opened_show(int city) {
    window_type window = {
        WINDOW_TRADE_OPENED,
        draw_background,
        draw_foreground, 
        handle_input
    };
    selected_city = city;
    window_show(&window);
}
