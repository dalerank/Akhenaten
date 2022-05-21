#include "file_dialog.h"

#include "core/calc.h"
#include "io/dir.h"
#include "core/encoding.h"
#include "io/file.h"
#include "graphics/image_groups.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"
#include "core/time.h"
#include "core/game_environment.h"
#include "io/gamestate/boilerplate.h"
#include "game/file_editor.h"
#include "graphics/elements/generic_button.h"
#include "graphics/boilerplate.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "widget/input_box.h"
#include "window/city.h"
#include "window/editor/map.h"

#include <string.h>
#include <game/settings.h>
#include "graphics/elements/scroll_list_panel.h"
#include "io/gamestate/manager.h"

static const time_millis NOT_EXIST_MESSAGE_TIMEOUT = 500;

static void button_ok_cancel(int is_ok, int param2);
static void button_select_file(int index, int param2);
static void button_double_click(int param1, int param2);
static void on_scroll(void);

static image_button image_buttons[] = {
        {344, 335, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 0, button_ok_cancel, button_none, 1, 0, 1},
        {392, 335, 39, 26, IB_NORMAL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 4, button_ok_cancel, button_none, 0, 0, 1},
};

#define NUM_FILES_IN_VIEW 12
//#define MAX_FILE_WINDOW_TEXT_WIDTH (18 * INPUT_BOX_BLOCK_SIZE)

static scrollable_list_ui_params ui_params = {
        .x = 144,
        .y = 120,
        .blocks_x = 20,
        .blocks_y = NUM_FILES_IN_VIEW + 1,
        .draw_scrollbar_always = true
};
static scroll_list_panel *panel = new scroll_list_panel(NUM_FILES_IN_VIEW, button_select_file, button_none, button_double_click, button_none,
                                                        ui_params, true, "Save/", "folders");

static input_box file_name_input = {144, 80, 20, 2, FONT_NORMAL_WHITE_ON_DARK};

typedef struct {
    char extension[4];
    char last_loaded_file[MAX_FILE_NAME];
} file_type_data;

static struct {
    time_millis message_not_exist_start_time;
    file_type type;
    file_dialog_type dialog_type;
    int focus_button_id;

    file_type_data *file_data;
    uint8_t typed_name[MAX_FILE_NAME];
    char selected_file[MAX_FILE_NAME];
} data;

static file_type_data saved_game_data = {"sav"};
static file_type_data saved_game_data_expanded = {"svx"};
static file_type_data map_file_data = {"map"};

static void set_chosen_filename(const char *name) {
    strcpy(data.selected_file, name);
    encoding_from_utf8(data.selected_file, data.typed_name, MAX_PLAYER_NAME);
}
static void clear_chosen_filename() {
    set_chosen_filename("");
}
static bool is_chosen_filename(int index) {
    return strcmp(data.selected_file, panel->get_selected_entry_text(FILE_NO_EXT)) == 0;
}
static bool is_valid_chosen_filename() {
    if (strcmp(data.selected_file, "") == 0)
        return false;
    if (panel->get_entry_idx(data.selected_file) > -1)
        return true;
    return false;
}
static const char *get_chosen_filename(void) {
    // Check if we should work with the selected file
    uint8_t selected_name[MAX_FILE_NAME];
    encoding_from_utf8(data.selected_file, selected_name, MAX_FILE_NAME);

    if (string_equals(selected_name, data.typed_name, 1)) {
        // user has not modified the string after selecting it: use filename
        return data.selected_file;
    }

    // We should use the typed name, which needs to be converted to UTF-8...
    static char typed_file[MAX_FILE_NAME];
    encoding_to_utf8(data.typed_name, typed_file, MAX_FILE_NAME, encoding_system_uses_decomposed());
    return typed_file;
}

static void init(file_type type, file_dialog_type dialog_type) {
    data.type = type;
    data.file_data = type == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;

    // get last saved file name
    if (strlen(data.file_data->last_loaded_file) == 0) {
        set_chosen_filename((const char*)lang_get_string(9, type == FILE_TYPE_SCENARIO ? 7 : 6));
//        string_copy(lang_get_string(9, type == FILE_TYPE_SCENARIO ? 7 : 6), data.typed_name, FILE_NAME_MAX);
//        encoding_to_utf8(data.typed_name, data.file_data->last_loaded_file, FILE_NAME_MAX, 0);
    } else
        encoding_from_utf8(data.file_data->last_loaded_file, data.typed_name, MAX_FILE_NAME);

    data.dialog_type = dialog_type;
    data.message_not_exist_start_time = 0;

    // populate file list
    switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH:
            char folder_name[MAX_FILE_NAME] = "Save/";
            strcat(folder_name, setting_player_name_utf8());
            strcat(folder_name, "/");
            if (type == FILE_TYPE_SCENARIO)
                panel->change_file_path("Maps/", map_file_data.extension);
            else if (data.dialog_type != FILE_DIALOG_SAVE) {
                panel->change_file_path(folder_name, data.file_data->extension);
//                data.file_list = dir_append_files_with_extension(saved_game_data_expanded.extension); // TODO?
            } else
                panel->change_file_path(folder_name, saved_game_data_expanded.extension);
            break;
    }

    set_chosen_filename(data.file_data->last_loaded_file);
    input_box_start(&file_name_input, data.typed_name, MAX_FILE_NAME, 0);
}

static void draw_foreground(void) {
    graphics_in_dialog();
    uint8_t file[MAX_FILE_NAME];

    outer_panel_draw(128, 40, 24, 21);
    input_box_draw(&file_name_input);

    // title
    if (data.message_not_exist_start_time &&
        time_get_millis() - data.message_not_exist_start_time < NOT_EXIST_MESSAGE_TIMEOUT)
        lang_text_draw_centered(43, 2, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    else if (data.dialog_type == FILE_DIALOG_DELETE)
        lang_text_draw_centered(43, 6, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    else {
        int text_id = data.dialog_type + (data.type == FILE_TYPE_SCENARIO ? 3 : 0);
        lang_text_draw_centered(43, text_id, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    }
    lang_text_draw(43, 5, 224, 342, FONT_NORMAL_BLACK_ON_LIGHT);

    panel->draw();

    image_buttons_draw(0, 0, image_buttons, 2);

//    uint8_t txt[200];
//    auto v = get_file_version();
//    draw_debug_line(txt, 150, 110, 0, "", v->minor, COLOR_FONT_YELLOW);
//    draw_debug_line(txt, 200, 110, 0, "", v->major, COLOR_FONT_YELLOW);

    graphics_reset_dialog();
}

static void button_ok_cancel(int is_ok, int param2) {
    if (!is_ok) {
        input_box_stop(&file_name_input);
        window_go_back();
        return;
    }

    char filename[MAX_FILE_NAME] = "";
    strcat(filename, get_chosen_filename());
    strcat(filename, ".sav");
    char full[MAX_FILE_NAME] = "";
    fullpath_saves(full, filename);

    if (data.dialog_type != FILE_DIALOG_SAVE && !file_exists(full, NOT_LOCALIZED)) {
        data.message_not_exist_start_time = time_get_millis();
        return;
    }
    if (data.dialog_type == FILE_DIALOG_LOAD) {
        if (data.type == FILE_TYPE_SAVED_GAME) {
            if (GamestateIO::load_savegame(filename)) {
                input_box_stop(&file_name_input);
                window_city_show();
            } else {
                data.message_not_exist_start_time = time_get_millis();
                return;
            }
        } else if (data.type == FILE_TYPE_SCENARIO) {
            if (game_file_editor_load_scenario(full)) {
                input_box_stop(&file_name_input);
                window_editor_map_show();
            } else {
                data.message_not_exist_start_time = time_get_millis();
                return;
            }
        }
    } else if (data.dialog_type == FILE_DIALOG_SAVE) {
        input_box_stop(&file_name_input);
        if (data.type == FILE_TYPE_SAVED_GAME) {
            if (!file_has_extension(full, saved_game_data_expanded.extension))
                file_append_extension(full, saved_game_data_expanded.extension);
            GamestateIO::write_savegame(filename);
            window_city_show();
        } else if (data.type == FILE_TYPE_SCENARIO) {
            if (!file_has_extension(full, map_file_data.extension))
                file_append_extension(full, map_file_data.extension);

            game_file_editor_write_scenario(full);
            window_editor_map_show();
        }
    } else if (data.dialog_type == FILE_DIALOG_DELETE) {
        if (GamestateIO::delete_savegame(filename)) {
            dir_find_files_with_extension(".", data.file_data->extension);
            dir_append_files_with_extension(saved_game_data_expanded.extension);

            panel->clamp_scrollbar_position();
//            if (scrollbar.scroll_position + NUM_FILES_IN_VIEW >= data.file_list->num_files)
//                --scrollbar.scroll_position;
//
//            if (scrollbar.scroll_position < 0)
//                scrollbar.scroll_position = 0;

        }
    }

    strncpy(data.file_data->last_loaded_file, get_chosen_filename(), MAX_FILE_NAME - 1);
}
static void button_select_file(int index, int param2) {
    if (index >= panel->get_total_entries())
        return clear_chosen_filename();
    set_chosen_filename(panel->get_selected_entry_text(FILE_NO_EXT));
//    setting_set_player_name(data.selected_player);
    input_box_refresh_text(&file_name_input);
    data.message_not_exist_start_time = 0;
//    read_file_version(panel->get_selected_entry_text(FILE_FULL_PATH), 4);



//    if (index < data.file_list->num_files) {
//        strncpy(data.selected_file, data.file_list->files[scrollbar.scroll_position + index], FILE_NAME_MAX - 1);
//        encoding_from_utf8(data.selected_file, data.typed_name, FILE_NAME_MAX);
//        input_box_refresh_text(&file_name_input);
//        data.message_not_exist_start_time = 0;
//    }
//    if (data.dialog_type != FILE_DIALOG_DELETE && double_click) {
//        double_click = false;
//        button_ok_cancel(1, 0);
//    }
}
static void button_double_click(int param1, int param2) {
    if (data.dialog_type != FILE_DIALOG_DELETE)
        button_ok_cancel(1, 0);
}

static void handle_input(const mouse *m, const hotkeys *h) {
    if (input_go_back_requested(m, h)) {
        input_box_stop(&file_name_input);
        window_go_back();
    }
    if (input_box_is_accepted(&file_name_input)) {
        button_ok_cancel(1, 0);
        return;
    }
    const mouse *m_dialog = mouse_in_dialog(m);
    if (input_box_handle_mouse(m_dialog, &file_name_input) ||
        panel->input_handle(m_dialog) ||
        image_buttons_handle_mouse(m_dialog, 0, 0, image_buttons, 2, 0))
        return;
}
void window_file_dialog_show(file_type type, file_dialog_type dialog_type) {
    window_type window = {
            WINDOW_FILE_DIALOG,
            window_draw_underlying_window,
            draw_foreground,
            handle_input
    };
    init(type, dialog_type);
    window_show(&window);
}
