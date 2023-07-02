#include "io/playerdata/player_data.h"
#include <core/game_environment.h>
#include "new_career.h"

#include "graphics/image_groups.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"
#include "game/settings.h"
#include "graphics/boilerplate.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/property.h"
#include "scenario/scenario.h"
#include "widget/input_box.h"
#include "window/mission_next.h"
#include "player_selection.h"
#include "game/settings.h"

static void confirm_new_player_name(int param1, int param2);
static void button_back(int param1, int param2);

static image_button image_buttons[] = {
        {0,   2, 31, 20, IB_NORMAL, GROUP_MESSAGE_ICON,       8, button_back,   button_none, 0, 0, 1},
        {305, 0, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, confirm_new_player_name, button_none, 1, 0, 1}
};

static input_box player_name_input = {160, 208, 20, 2, FONT_NORMAL_WHITE_ON_DARK};

static uint8_t player_name[MAX_PLAYER_NAME] = {0};

static void init(void) {
    setting_clear_personal_savings();
    scenario_settings_init();
    string_copy(setting_player_name(), player_name, MAX_PLAYER_NAME);
    input_box_start(&player_name_input, player_name, MAX_PLAYER_NAME, 1);
}

static void draw_foreground(void) {
    graphics_set_to_dialog();
    outer_panel_draw(128, 160, 24, 8);
    lang_text_draw_centered(31, 0, 128, 172, 384, FONT_LARGE_BLACK_ON_LIGHT);
    lang_text_draw(13, 5, 352, 256, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(12, 0, 200, 256, FONT_NORMAL_BLACK_ON_LIGHT);
    input_box_draw(&player_name_input);

    image_buttons_draw(159, 249, image_buttons, 2);

    graphics_reset_dialog();
}

static void button_back(int param1, int param2) {
    input_box_stop(&player_name_input);
    window_go_back();
}
static void confirm_new_player_name(int param1, int param2) {
    input_box_stop(&player_name_input);
    setting_set_player_name(player_name);
    if (GAME_ENV == ENGINE_ENV_C3)
        window_mission_next_selection_show();
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        // in OG Pharaoh, creating a new player name automatically opens the
        // game selection menu; here we first go back to the player list instead
        player_data_new(player_name);
        window_go_back();
        window_player_selection_init();
    }
}

static void handle_input(const mouse *m, const hotkeys *h) {
    const mouse *m_dialog = mouse_in_dialog(m);
    if (input_box_handle_mouse(m_dialog, &player_name_input) ||
        image_buttons_handle_mouse(m_dialog, 159, 249, image_buttons, 2, 0))
        return;
    if (input_box_is_accepted(&player_name_input)) {
        confirm_new_player_name(0, 0);
        return;
    }
    if (input_go_back_requested(m, h))
        button_back(0, 0);
}
void window_new_career_show(void) {
    window_type window = {
            WINDOW_NEW_CAREER,
            window_draw_underlying_window,
            draw_foreground,
            handle_input
    };
    init();
    window_show(&window);
}
