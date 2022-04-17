#include "player_selection.h"

#include "core/calc.h"
#include "core/dir.h"
#include "core/encoding.h"
#include "core/file.h"
#include "core/image_group.h"
#include "core/lang.h"
#include "core/string.h"
#include "core/time.h"
#include "game/gamestate/file.h"
#include "game/file_editor.h"
#include "game/player_data.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
//#include "widget/input_box.h"
#include "window/city.h"
#include "window/editor/map.h"
#include "window/new_career.h"
#include "window/game_menu.h"
#include "popup_dialog.h"
#include "main_menu.h"

#include <string.h>
#include <game/settings.h>
#include <core/game_environment.h>
#include <graphics/scroll_list_panel.h>

static const time_millis NOT_EXIST_MESSAGE_TIMEOUT = 500;

static void button_click(int param1, int param2);
static void button_select_file(int index, int param2);
static void button_double_click(int param1, int param2);

static generic_button buttons[] = {
        {144, 306, 126, 25, button_click, button_none, 0, 0},
        {274, 306, 126, 25, button_click, button_none, 1, 0},
        {406, 306, 86, 25, button_click, button_none, 2, 0},
        {192, 336, 256, 25, button_click, button_none, 3, 0},
};

#define NUM_FILES_IN_VIEW 12
#define MAX_FILE_WINDOW_TEXT_WIDTH (18 * INPUT_BOX_BLOCK_SIZE)

static scrollable_list_ui_params ui_params = {
        .x = 144,
        .y = 92,
        .blocks_x = 20,
        .blocks_y = NUM_FILES_IN_VIEW + 1,
        .draw_scrollbar_always = true
};
static scroll_list_panel *panel = new scroll_list_panel(NUM_FILES_IN_VIEW, button_select_file, button_none, button_double_click, button_none,
                                                        ui_params, true, "Save/", "folders");

static struct {
    int focus_button_id;

    uint8_t selected_player[MAX_PLAYER_NAME];
    char selected_player_utf8[MAX_PLAYER_NAME];
} data;

static void set_name(const char *name) {
    strcpy(data.selected_player_utf8, name);
    encoding_from_utf8(data.selected_player_utf8, data.selected_player, MAX_PLAYER_NAME);
}
static void clear_selectd_name() {
    set_name("");
}
static bool is_selected_name(int index) {
    return strcmp(data.selected_player_utf8, panel->get_selected_entry_text(FILE_NO_EXT)) == 0;
}
static bool is_valid_selected_player() {
    if (strcmp(data.selected_player_utf8, "") == 0)
        return false;
    if (panel->get_entry_idx(data.selected_player_utf8) > -1)
        return true;
    return false;
}

void window_player_selection_init() {
    panel->refresh_file_finder();

    string_copy(setting_player_name(), data.selected_player, MAX_PLAYER_NAME);
    encoding_to_utf8(data.selected_player, data.selected_player_utf8, MAX_PLAYER_NAME, 0);

    panel->select(data.selected_player_utf8);
}

static void draw_background(void) {
    graphics_clear_screens();
    graphics_in_dialog();
    ImageDraw::img_generic(image_id_from_group(GROUP_PLAYER_SELECTION), 0, 0);
    graphics_reset_dialog();
}
static void draw_foreground(void) {
    graphics_in_dialog();

    outer_panel_draw(128, 40, 24, 21);

    // title
    lang_text_draw_centered(292, 3, 160, 60, 304, FONT_LARGE_BLACK_ON_LIGHT);

    // family names
    panel->draw();

    // buttons
    for (int i = 0; i < 4; i++) {
        button_border_draw(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height,data.focus_button_id == i + 1 ? 1 : 0);
        if (i < 3)
            lang_text_draw_centered(292, i, buttons[i].x, buttons[i].y + 6, buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
        else
            lang_text_draw_centered(292, 4, buttons[i].x, buttons[i].y + 6, buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    graphics_reset_dialog();
}

static void confirm_nothing(bool accepted) {
}
static void confirm_delete_player(bool accepted) {
    if (accepted)
        player_data_delete(data.selected_player);
}
static void button_select_file(int index, int param2) {
    if (index >= panel->get_total_entries())
        return clear_selectd_name();
    set_name(panel->get_selected_entry_text(FILE_NO_EXT));
    setting_set_player_name(data.selected_player);
}
static void button_double_click(int index, int param2) {
    button_click(2, 0);
}
static void button_click(int param1, int param2) {
    switch (param1) {
        case 0: // new player
            window_new_career_show();
            break;
        case 1: // delete player
            if (!is_valid_selected_player())
                window_popup_dialog_show(POPUP_DIALOG_NO_DYNASTY, confirm_nothing, 1);
            else
                window_popup_dialog_show(POPUP_DIALOG_DELETE_DYNASTY, confirm_delete_player, 2);
            break;
        case 2: // proceed with selected player
            if (!is_valid_selected_player())
                window_popup_dialog_show(POPUP_DIALOG_NO_DYNASTY, confirm_nothing, 1);
            else
                window_game_menu_show();
            break;
        case 3: // back to main menu
            window_main_menu_show(false);
            break;
    }
}

static void on_scroll(void) {
//    data.message_not_exist_start_time = 0;
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (input_go_back_requested(m, h))
        window_main_menu_show(false);

    const mouse *m_dialog = mouse_in_dialog(m);
    if (panel->input_handle(m_dialog))
        return;
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons, 4, &data.focus_button_id))
        return;
}

void window_player_selection_show(void) {
    window_type window = {
            WINDOW_PLAYER_SELECTION,
            draw_background,
            draw_foreground,
            handle_input
    };
    window_player_selection_init();
    window_show(&window);
}