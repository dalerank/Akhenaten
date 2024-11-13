#include "victory_dialog.h"

#include "city/city.h"
#include "city/victory.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "window/window_city.h"

static void button_accept(int param1, int param2);
static void button_continue_governing(int months, int param2);

static generic_button victory_buttons[] = {
  {32, 112, 480, 20, button_accept, button_none, 0, 0},
  {32, 144, 480, 20, button_continue_governing, button_none, 24, 0},
  {32, 176, 480, 20, button_continue_governing, button_none, 60, 0},
};

static int focus_button_id = 0;

static void draw_background(int) {
    window_draw_underlying_window(UiFlags_None);
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{48, 128}, 34, 15);
    if (scenario_campaign_rank() < 10 || scenario_is_custom()) {
        lang_text_draw_centered(62, 0, 48, 144, 544, FONT_LARGE_BLACK_ON_LIGHT);
        lang_text_draw_centered(62, 2, 48, 175, 544, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_centered(32, scenario_campaign_rank() + 1, 48, 194, 544, FONT_LARGE_BLACK_ON_LIGHT);
    } else {
        text_draw_centered(city_player_name(), 48, 144, 512, FONT_LARGE_BLACK_ON_LIGHT, 0);
        lang_text_draw_multiline(62, 26, vec2i{64, 175}, 480, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    graphics_reset_dialog();
}

static void draw_foreground(int) {
    graphics_set_to_dialog();

    if (g_city.victory_state.state == e_victory_state_won) {
        large_label_draw(80, 240, 30, focus_button_id == 1);
        if (scenario_campaign_rank() < 10 || scenario_is_custom())
            lang_text_draw_centered(62, 3, 80, 246, 480, FONT_NORMAL_BLACK_ON_DARK);
        else {
            lang_text_draw_centered(62, 27, 80, 246, 480, FONT_NORMAL_BLACK_ON_DARK);
        }
        if (scenario_campaign_rank() >= 2 || scenario_is_custom()) {
            // Continue for 2/5 years
            large_label_draw(80, 272, 30, focus_button_id == 2);
            lang_text_draw_centered(62, 4, 80, 278, 480, FONT_NORMAL_BLACK_ON_DARK);

            large_label_draw(80, 304, 30, focus_button_id == 3);
            lang_text_draw_centered(62, 5, 80, 310, 480, FONT_NORMAL_BLACK_ON_DARK);
        }
    } else {
        // lost
        large_label_draw(80, 224, 30, focus_button_id == 1);
        lang_text_draw_centered(62, 6, 80, 230, 480, FONT_NORMAL_BLACK_ON_DARK);
    }
    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    int num_buttons;
    if (scenario_campaign_rank() >= 2 || scenario_is_custom())
        num_buttons = 3;
    else {
        num_buttons = 1;
    }
    generic_buttons_handle_mouse(mouse_in_dialog(m), {48, 128}, victory_buttons, num_buttons, &focus_button_id);
}

static void button_accept(int param1, int param2) {
    window_city_show();
}

static void button_continue_governing(int months, int param2) {
    g_city.victory_state.continue_governing(months);
    window_city_show();
    g_city.victory_state.reset();
    g_sound.music_update(/*force*/true);
}

void window_victory_dialog_show(void) {
    window_type window = {
        WINDOW_VICTORY_DIALOG,
        draw_background,
        draw_foreground,
        handle_input
    };
    window_show(&window);
}
