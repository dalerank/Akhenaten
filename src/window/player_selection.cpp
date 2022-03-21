#include "player_selection.h"

#include "core/calc.h"
#include "core/dir.h"
#include "core/encoding.h"
#include "core/file.h"
#include "core/image_group.h"
#include "core/lang.h"
#include "core/string.h"
#include "core/time.h"
#include "game/file.h"
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
#include "widget/input_box.h"
#include "window/city.h"
#include "window/editor/map.h"
#include "window/new_career.h"
#include "window/game_menu.h"
#include "popup_dialog.h"

#include <string.h>
#include <game/settings.h>
#include <core/game_environment.h>

#define NUM_FILES_IN_VIEW 12
#define MAX_FILE_WINDOW_TEXT_WIDTH (18 * INPUT_BOX_BLOCK_SIZE)

static const time_millis NOT_EXIST_MESSAGE_TIMEOUT = 500;

static void button_click(int param1, int param2);
static void button_select_file(int index, int param2);
static void on_scroll(void);

#define LIST_Y 100

static generic_button buttons[] = {
        {160, LIST_Y + 16 * 0,  288, 16, button_select_file, button_none, 0,  0},
        {160, LIST_Y + 16 * 1,  288, 16, button_select_file, button_none, 1,  0},
        {160, LIST_Y + 16 * 2,  288, 16, button_select_file, button_none, 2,  0},
        {160, LIST_Y + 16 * 3,  288, 16, button_select_file, button_none, 3,  0},
        {160, LIST_Y + 16 * 4,  288, 16, button_select_file, button_none, 4,  0},
        {160, LIST_Y + 16 * 5,  288, 16, button_select_file, button_none, 5,  0},
        {160, LIST_Y + 16 * 6,  288, 16, button_select_file, button_none, 6,  0},
        {160, LIST_Y + 16 * 7,  288, 16, button_select_file, button_none, 7,  0},
        {160, LIST_Y + 16 * 8,  288, 16, button_select_file, button_none, 8,  0},
        {160, LIST_Y + 16 * 9,  288, 16, button_select_file, button_none, 9,  0},
        {160, LIST_Y + 16 * 10, 288, 16, button_select_file, button_none, 10, 0},
        {160, LIST_Y + 16 * 11, 288, 16, button_select_file, button_none, 11, 0},

        {144, 306, 126, 25, button_click, button_none, 0, 0},
        {274, 306, 126, 25, button_click, button_none, 1, 0},
        {406, 306, 86, 25, button_click, button_none, 2, 0},
        {192, 336, 256, 25, button_click, button_none, 3, 0},
};

static scrollbar_type scrollbar = {464, LIST_Y - 8, 208, on_scroll};

static struct {
    int focus_button_id;
    const dir_listing *file_list;

    uint8_t selected_player[MAX_PLAYER_NAME];
    char selected_player_utf8[MAX_PLAYER_NAME];
} data;

static int double_click = false;

static void clear_selectd_name() {
    strcpy(data.selected_player_utf8, "");
    encoding_from_utf8(data.selected_player_utf8, data.selected_player, MAX_PLAYER_NAME);
}
static void select_name_slot(int index) {
    if (index == -1 || index > data.file_list->num_files)
        clear_selectd_name();
    else {
        strcpy(data.selected_player_utf8, data.file_list->files[scrollbar.scroll_position + index]);
        encoding_from_utf8(data.selected_player_utf8, data.selected_player, MAX_PLAYER_NAME);
    }
}
static bool is_selected_name(int index) {
    return strcmp(data.file_list->files[scrollbar.scroll_position + index], data.selected_player_utf8) == 0;
}
static bool is_valid_selected_player() {
    if (strcmp(data.selected_player_utf8, "") == 0)
        return false;
    for (int i = 0; i < data.file_list->num_files; ++i) {
        if (strcmp(data.selected_player_utf8, data.file_list->files[i]) == 0)
            return true;
    }
    return false;
}

void window_player_selection_init() {
    data.file_list = dir_find_all_subdirectories("Save/");

    string_copy(setting_player_name(), data.selected_player, MAX_PLAYER_NAME);
    encoding_to_utf8(data.selected_player, data.selected_player_utf8, MAX_PLAYER_NAME, 0);

    scrollbar_init(&scrollbar, 0, data.file_list->num_files - NUM_FILES_IN_VIEW);
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
    inner_panel_draw(144, LIST_Y - 8, 20, 13);

    // title
    lang_text_draw_centered(292, 3, 160, 60, 304, FONT_LARGE_BLACK_ON_LIGHT);

    // family names
    uint8_t list_name[FILE_NAME_MAX];
    for (int i = 0; i < NUM_FILES_IN_VIEW; i++) {
        encoding_from_utf8(data.file_list->files[scrollbar.scroll_position + i], list_name, FILE_NAME_MAX);
        font_t font = FONT_NORMAL_BLACK_ON_DARK;
        if (is_selected_name(i))
            font = FONT_NORMAL_WHITE_ON_DARK;
        else if (data.focus_button_id == i + 1)
            font = FONT_NORMAL_YELLOW;
        text_ellipsize(list_name, font, MAX_FILE_WINDOW_TEXT_WIDTH);
        text_draw(list_name, 160, LIST_Y + 2 + (16 * i), font, 0);
    }

    // buttons
    for (int i = NUM_FILES_IN_VIEW; i < NUM_FILES_IN_VIEW + 4; i++) {
        button_border_draw(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height,data.focus_button_id == i + 1 ? 1 : 0);
        if (i - NUM_FILES_IN_VIEW < 3)
            lang_text_draw_centered(292, i - NUM_FILES_IN_VIEW, buttons[i].x, buttons[i].y + 6, buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
        else
            lang_text_draw_centered(292, 4, buttons[i].x, buttons[i].y + 6, buttons[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    scrollbar_draw(&scrollbar);

    graphics_reset_dialog();
}

static void confirm_nothing(bool accepted) {
}
static void confirm_delete_player(bool accepted) {
    if (accepted)
        player_data_delete(data.selected_player);
}
static void button_select_file(int index, int param2) {
    if (index < data.file_list->num_files) {
        select_name_slot(index);
        setting_set_player_name(data.selected_player);
        if (double_click) {
            double_click = false;
            button_click(2, 0);
        }
    }
    else
        clear_selectd_name();
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
            window_go_back();
            break;
    }
}

static void on_scroll(void) {
//    data.message_not_exist_start_time = 0;
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (input_go_back_requested(m, h))
        window_go_back();
    double_click = m->left.double_click;

    const mouse *m_dialog = mouse_in_dialog(m);
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons, NUM_FILES_IN_VIEW + 4, &data.focus_button_id))
        return;
    if (scrollbar_handle_mouse(&scrollbar, m_dialog))
        return;
}

void window_player_selection_show(void) {
    window_type window = {
            WINDOW_FAMILY_SELECTION,
            draw_background,
            draw_foreground,
            handle_input
    };
    window_player_selection_init();
    window_show(&window);
}