#include "main_menu.h"

#include "core/string.h"
#include "core/game_environment.h"
#include "editor/editor.h"
#include "game/game.h"
#include "game/system.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/text.h"
#include "graphics/screen.h"
#include "graphics/window.h"
#include "sound/music.h"
#include "window/map_selection.h"
#include "window/config.h"
#include "window/file_dialog.h"
#include "window/new_career.h"
#include "window/player_selection.h"
#include "window/game_menu.h"
#include "window/plain_message_dialog.h"
#include "window/popup_dialog.h"
#include "records.h"

static void button_click(int type, int param2);

#define MAX_BUTTONS 6

static int focus_button_id;

#define BUTTONS_X 192
#define BUTTONS_Y 125
#define BUTTONS_WIDTH 256
#define BUTTONS_HEIGHT 25

static generic_button buttons[] = {
        {BUTTONS_X, BUTTONS_Y + 40 * 0, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 1, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 1, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 2, 0},
//        {BUTTONS_X, BUTTONS_Y + 40 * 2, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 3, 0},
//        {BUTTONS_X, BUTTONS_Y + 40 * 3, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 4, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 2, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 5, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 3, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 6, 0},
};

static void draw_version_string(void) {
    uint8_t version_string[100] = "Ramesses v";
    int version_prefix_length = string_length(version_string);
    int text_y = screen_height() - 30;

    string_copy(string_from_ascii(system_version()), version_string + version_prefix_length, 99);

    int text_width = text_get_width(version_string, FONT_SMALL_PLAIN);

    if (text_y <= 500 && (screen_width() - 640) / 2 < text_width + 18) {
        graphics_draw_rect(10, text_y, text_width + 14, 20, COLOR_BLACK);
        graphics_fill_rect(11, text_y + 1, text_width + 12, 18, COLOR_WHITE);
        text_draw(version_string, 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_BLACK);
    } else
        text_draw(version_string, 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_FONT_LIGHT_GRAY);
}
static void draw_background(void) {
    graphics_clear_screens();
    graphics_in_dialog();
    ImageDraw::img_generic(image_id_from_group(GROUP_MAIN_MENU_BACKGROUND), 0, 0);
    graphics_reset_dialog();
    if (window_is(WINDOW_MAIN_MENU))
        draw_version_string();
}
static void draw_foreground(void) {
    graphics_in_dialog();

    switch (GAME_ENV) {
        case ENGINE_ENV_C3: {
            int groups[6][2] = {
                    {30, 1},
                    {30, 2},
                    {30, 3},
                    {9,  8},
                    {2,  0},
                    {30, 5},
            };
            for (int i = 0; i < MAX_BUTTONS; i++) {
                large_label_draw(buttons[i].x, buttons[i].y, buttons[i].width / 16, focus_button_id == i + 1 ? 1 : 0);
                lang_text_draw_centered(groups[i][0], groups[i][1], BUTTONS_X, BUTTONS_Y + 40 * i + 6, BUTTONS_WIDTH,
                                        FONT_NORMAL_BLACK_ON_DARK);
            }
            break;
        }
        case ENGINE_ENV_PHARAOH: {
            int groups[6][2] = {
                    {30, 0},
                    {30, 5}, //{1, 3},
//                    {30, 3},
//                    {9,  8},
                    {2,  0},
                    {30, 4},
            };
            for (int i = 0; i < 4; i++) {
                large_label_draw(buttons[i].x, buttons[i].y, buttons[i].width / 16, focus_button_id == i + 1 ? 1 : 0);
                lang_text_draw_centered(groups[i][0], groups[i][1], BUTTONS_X, BUTTONS_Y + 40 * i + 6, BUTTONS_WIDTH,
                                        FONT_NORMAL_BLACK_ON_LIGHT);
            }
            break;
        }
    }

    graphics_reset_dialog();
}

static void confirm_exit(bool accepted) {
    if (accepted)
        system_exit();
}
static void button_click(int type, int param2) {
    switch (type) {
        case 1:
            switch (GAME_ENV) {
                case ENGINE_ENV_C3:
                    window_new_career_show();
                    break;
                case ENGINE_ENV_PHARAOH:
                    window_player_selection_show();
                    break;
            }
            break;
        case 2:
            switch (GAME_ENV) {
                case ENGINE_ENV_C3:
                    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
                    break;
                case ENGINE_ENV_PHARAOH:
                    window_records_show(); // TODO
                    break;
            }
            break;
        case 3:
            window_map_selection_show(MAP_SELECTION_CUSTOM);
            break;
        case 4:
            if (!editor_is_present() || !game_init_editor())
                window_plain_message_dialog_show(TR_NO_EDITOR_TITLE, TR_NO_EDITOR_MESSAGE);
            else
                sound_music_play_editor();
            break;
        case 5:
            window_config_show();
            break;
        case 6:
            window_popup_dialog_show(POPUP_DIALOG_QUIT, confirm_exit, 2);
            break;
    }
}

static void handle_input(const mouse *m, const hotkeys *h) {
    const mouse *m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons, MAX_BUTTONS, &focus_button_id))
        return;
    if (h->escape_pressed)
        hotkey_handle_escape();

    if (h->load_file)
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);

}
void window_main_menu_show(int restart_music) {
    if (restart_music)
        sound_music_play_intro();
    window_type window = {
            WINDOW_MAIN_MENU,
            draw_background,
            draw_foreground,
            handle_input
    };
    window_show(&window);
}
