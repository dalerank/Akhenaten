#include "game_menu.h"
#include "window_city.h"
#include "file_dialog.h"
#include "message_dialog.h"
#include "player_selection.h"
#include "scenario_selection.h"

#include "game/mission.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "io/manager.h"
#include "game/player_data.h"
#include "game/game.h"

static void button_click(int param1, int param2);

#define BUTTONS_X 185
#define BUTTONS_Y 130
#define BUTTON_SPACING_Y 40
#define BUTTON_WIDTH 270

static generic_button buttons[] = {
  {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 0, BUTTON_WIDTH, 25, button_click, button_none, 0, 0}, // resume mission
  //        {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 0, BUTTON_WIDTH, 25, button_click, button_none, 5, 0}, // begin
  //        history

  {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 1, BUTTON_WIDTH, 25, button_click, button_none, 1, 0}, // choose mission
  {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 2, BUTTON_WIDTH, 25, button_click, button_none, 2, 0}, // load saves
  {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 3, BUTTON_WIDTH, 25, button_click, button_none, 3, 0}, // custom missions
  {BUTTONS_X, BUTTONS_Y + BUTTON_SPACING_Y * 4, BUTTON_WIDTH, 25, button_click, button_none, 4, 0}, // back
};

static struct {
    int focus_button_id;

    bool to_begin_history;
    bool has_saved_games;
    const char* last_autosave;

    uint8_t player_name[256];
    uint8_t player_name_title[256];
} data;

static void init() {
    string_copy(g_settings.player_name, data.player_name, MAX_PLAYER_NAME);
    text_tag_substitution tags[] = {{"[player_name]", data.player_name}};
    text_fill_in_tags(lang_get_string(293, 5), data.player_name_title, tags, 1);

    player_data_load(data.player_name);

    data.last_autosave = player_get_last_autosave();
    if (strcmp(data.last_autosave, "") == 0 || !vfs::file_exists(data.last_autosave)) {
        data.to_begin_history = true;
    } else {
        data.to_begin_history = false;
    }
    // in OG pharaoh, the "load save" button doesn't appear if there are no saves
    data.has_saved_games = true;
}

static void draw_background(int) {
    painter ctx = game.painter();
    graphics_clear_screen();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_GAME_MENU));
    graphics_set_to_dialog();
    graphics_reset_dialog();
}
static void draw_foreground(int) {
    graphics_set_to_dialog();
    outer_panel_draw(vec2i{128, 56}, 24, 19);

    // title
    text_draw_centered(data.player_name_title, 170, 80, 304, FONT_LARGE_BLACK_ON_LIGHT, 0);

    // buttons
    for (int i = 0; i < 5; i++)
        button_border_draw(
          buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, data.focus_button_id == i + 1 ? 1 : 0);

    // begin / resume family history
    if (data.to_begin_history)
        lang_text_draw_centered(293, 7, buttons[0].x, buttons[0].y + 6, buttons[0].width, FONT_NORMAL_BLACK_ON_LIGHT);
    else
        lang_text_draw_centered(293, 0, buttons[0].x, buttons[0].y + 6, buttons[0].width, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_centered(293, 6, buttons[1].x, buttons[1].y + 6, buttons[1].width, FONT_NORMAL_BLACK_ON_LIGHT); // explore history
    lang_text_draw_centered(293, 2, buttons[2].x, buttons[2].y + 6, buttons[2].width, FONT_NORMAL_BLACK_ON_LIGHT); // load save
    lang_text_draw_centered(293, 3, buttons[3].x, buttons[3].y + 6, buttons[3].width, FONT_NORMAL_BLACK_ON_LIGHT); // custom missions
    lang_text_draw_centered(293, 4, buttons[4].x, buttons[4].y + 6, buttons[4].width, FONT_NORMAL_BLACK_ON_LIGHT); // back
}

static void button_click(int param1, int param2) {
    switch (param1) {
    case 0: // begin / resume family history
        if (data.to_begin_history) {
            GamestateIO::load_mission(SCENARIO_NUBT, true);
        } else {
            if (GamestateIO::load_savegame(data.last_autosave)) {
                graphics_reset_dialog();
                return window_city_show();
            } else {
                // save load failed
                return;
            }
        }
        break;
    case 1: // choose mission
        graphics_reset_dialog();
        window_scenario_selection_show(MAP_SELECTION_CAMPAIGN);
        break;
    case 2: // load save
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
        break;
    case 3: // custom mission
        window_scenario_selection_show(MAP_SELECTION_CUSTOM);
        break;
    case 4: // back
        window_player_selection_init();
        window_player_selection_show();
        break;
    }
}
static void handle_input(const mouse* m, const hotkeys* h) {
    if (input_go_back_requested(m, h)) {
        window_player_selection_init();
        window_player_selection_show();
    }
    const mouse* m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, {0, 0}, buttons, (int)std::size(buttons), &data.focus_button_id)) {
        return;
    }
}

void window_game_menu_show(void) {
    static window_type window = {
        WINDOW_GAME_SELECTION,
        draw_background,
        draw_foreground,
        handle_input
    };
    init();
    window_show(&window);
}