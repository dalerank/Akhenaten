#include "game_menu.h"
#include "message_dialog.h"

#include <graphics/window.h>
#include <graphics/graphics.h>
#include <graphics/image.h>
#include <graphics/panel.h>
#include <input/input.h>
#include <graphics/generic_button.h>
#include <graphics/lang_text.h>
#include <core/lang.h>
#include <game/settings.h>
#include <graphics/text.h>

static void button_click(int param1, int param2);

#define BUTTONS_X 185
#define BUTTONS_Y 130
#define BUTTON_SPACING_Y 40
#define BUTTON_WIDTH 270

static generic_button buttons[] = {
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 0, BUTTON_WIDTH, 25, button_click, button_none, 0, 0}, // resume mission
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 1, BUTTON_WIDTH, 25, button_click, button_none, 1, 0}, // choose mission
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 2, BUTTON_WIDTH, 25, button_click, button_none, 2, 0}, // load saves
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 3, BUTTON_WIDTH, 25, button_click, button_none, 3, 0}, // custom missions
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 4, BUTTON_WIDTH, 25, button_click, button_none, 4, 0}, // back

        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 0, BUTTON_WIDTH, 25, button_click, button_none, 4, 0}, // explore history
        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 0, BUTTON_WIDTH, 25, button_click, button_none, 4, 0}, // begin history
};

static struct {
    int focus_button_id;

    bool to_begin_history;
    bool has_saved_games;
} data;

static void init() {
    data.to_begin_history = true;
    data.has_saved_games = false;
}

static void draw_background() {
    graphics_clear_screens();
    graphics_in_dialog();
    ImageDraw::img_generic(image_id_from_group(GROUP_GAME_MENU), 0, 0);
    graphics_reset_dialog();
}

static void draw_foreground() {
    graphics_in_dialog();
    outer_panel_draw(128, 56, 24, 19);

    // title
    uint8_t player_name_title[256];
    text_tag_substitution tags[] = {
        {"[player_name]", setting_player_name()}
    };
    text_fill_in_tags(lang_get_string(293, 5), player_name_title, tags, 1);
    text_draw_centered(player_name_title, 170, 80, 304, FONT_LARGE_BLACK_ON_LIGHT, 0);

    // buttons
    for (int i = 0; i < 5; i++) {
        button_border_draw(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, data.focus_button_id == i + 1 ? 1 : 0);
        lang_text_draw_centered(293, i, buttons[i].x, buttons[i].y + 6, buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

static void button_click(int param1, int param2) {
    switch (param1) {
        case 0: // resume mission
            break;
        case 1: // choose mission
            break;
        case 2: // load save
            break;
        case 3: // custom mission
            break;
        case 4: // back
            window_go_back();
            break;
        case 5: // explore history (?)
            break;
        case 6: // begin family history
            break;
    }
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (input_go_back_requested(m, h))
        window_go_back();
    const mouse *m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons, 7, &data.focus_button_id))
        return;
}

void window_game_menu_show(void) {
    window_type window = {
            WINDOW_FAMILY_SELECTION,
            draw_background,
            draw_foreground,
            handle_input
    };
    init();
    window_show(&window);
}