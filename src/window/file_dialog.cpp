#include "file_dialog.h"

#include <cassert>

#include "core/calc.h"
#include "core/encoding.h"
#include "core/string.h"
#include "content/dir.h"
#include "game/file_editor.h"
#include "graphics/graphics.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "graphics/text.h"
#include "input/input.h"
#include "content/vfs.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "widget/input_box.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/autoconfig_window.h"
#include "game/settings.h"
#include "io/manager.h"

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
// #define MAX_FILE_WINDOW_TEXT_WIDTH (18 * INPUT_BOX_BLOCK_SIZE)

static scrollable_list_ui_params ui_params = [] {
    scrollable_list_ui_params ret;
    //ret.pos = { 144, 120 };
    ret.blocks_x = 20;
    ret.blocks_y = NUM_FILES_IN_VIEW + 1;
    ret.draw_scrollbar_always = true;
    return ret;
}();

static input_box file_name_input = {144, 80, 20, 2, FONT_NORMAL_WHITE_ON_DARK};

struct file_dialog : public autoconfig_window_t<file_dialog> {
    time_millis message_not_exist_start_time;
    file_type type;
    file_dialog_type dialog_type;
    int focus_button_id;

    file_type_data* file_data;
    uint8_t typed_name[MAX_FILE_NAME];
    char selected_file[MAX_FILE_NAME];
    scroll_list_panel* panel = nullptr;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override { return 0; }
    virtual void init() override {}
};

file_dialog g_file_dialog;

file_type_data saved_game_data = {"sav"};
file_type_data saved_game_data_expanded = {"svx"};
file_type_data map_file_data = {"map"};

static void set_chosen_filename(const char* name) {
    auto& data = g_file_dialog;
    strcpy(data.selected_file, name);
    encoding_from_utf8(data.selected_file, data.typed_name, MAX_PLAYER_NAME);
}

static void clear_chosen_filename() {
    set_chosen_filename("");
}

static bool is_chosen_filename(int index) {
    auto& data = g_file_dialog;
    return data.panel->get_selected_entry_text(FILE_NO_EXT) == data.selected_file;
}

static bool is_valid_chosen_filename() {
    auto& data = g_file_dialog;
    if (strcmp(data.selected_file, "") == 0)
        return false;
    if (data.panel->get_entry_idx(data.selected_file) > -1)
        return true;
    return false;
}

static const char* get_chosen_filename(void) {
    auto& data = g_file_dialog;
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
    auto& data = g_file_dialog;
    data.type = type;
    data.file_data = type == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;

    // get last saved file name
    if (strlen(data.file_data->last_loaded_file) == 0) {
        set_chosen_filename((pcstr)lang_get_string(9, type == FILE_TYPE_SCENARIO ? 7 : 6));
    } else {
        encoding_from_utf8(data.file_data->last_loaded_file, data.typed_name, MAX_FILE_NAME);
    }

    data.dialog_type = dialog_type;
    data.message_not_exist_start_time = 0;

    // populate file list
    char folder_name[MAX_FILE_NAME] = "Save/";
    strcat(folder_name, (pcstr)g_settings.player_name);
    strcat(folder_name, "/");
    if (type == FILE_TYPE_SCENARIO) {
        data.panel->change_file_path("Maps/", map_file_data.extension);
    } else {
        if (data.dialog_type == FILE_DIALOG_LOAD) {
            data.panel->change_file_path(folder_name, data.file_data->extension);
            data.panel->append_files_with_extension(folder_name, saved_game_data_expanded.extension); // TODO?
        } else if (data.dialog_type == FILE_DIALOG_SAVE) {
            data.panel->change_file_path(folder_name, saved_game_data_expanded.extension);
        } else {
            assert(false);
        }
    }

    set_chosen_filename(data.file_data->last_loaded_file);
    input_box_start(&file_name_input, data.typed_name, MAX_FILE_NAME, 0);
}

static void draw_foreground(int) {
    auto& data = g_file_dialog;
    graphics_set_to_dialog();
    uint8_t file[MAX_FILE_NAME] = {0};

    outer_panel_draw(vec2i{128, 40}, 24, 21);
    input_box_draw(&file_name_input);

    // title
    if (data.message_not_exist_start_time
        && time_get_millis() - data.message_not_exist_start_time < NOT_EXIST_MESSAGE_TIMEOUT) {
        lang_text_draw_centered(43, 2, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    } else if (data.dialog_type == FILE_DIALOG_DELETE) {
        lang_text_draw_centered(43, 6, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    } else {
        int text_id = data.dialog_type + (data.type == FILE_TYPE_SCENARIO ? 3 : 0);
        lang_text_draw_centered(43, text_id, 160, 50, 304, FONT_LARGE_BLACK_ON_LIGHT);
    }
    lang_text_draw(43, 5, 224, 342, FONT_NORMAL_BLACK_ON_LIGHT);

    data.panel->ui_params.pos = { 144, 120 };
    data.panel->draw();

    image_buttons_draw({0, 0}, image_buttons, 2);

    //    uint8_t txt[200];
    //    auto v = get_file_version();
    //    draw_debug_line(txt, 150, 110, 0, "", v->minor, COLOR_FONT_YELLOW);
    //    draw_debug_line(txt, 200, 110, 0, "", v->major, COLOR_FONT_YELLOW);

    graphics_reset_dialog();
}

static void button_ok_cancel(int is_ok, int param2) {
    auto& data = g_file_dialog;
    if (!is_ok) {
        input_box_stop(&file_name_input);
        window_go_back();
        return;
    }

    bstring256 filename(get_chosen_filename(), ".", saved_game_data.extension);
    bstring256 full = fullpath_saves(filename);

    if (data.dialog_type == FILE_DIALOG_LOAD) {
        if (!vfs::file_exists(full)) {
            filename = bstring256(get_chosen_filename(), ".", saved_game_data_expanded.extension);
            full = fullpath_saves(filename);
        }

        if (!vfs::file_exists(full)) {
            data.message_not_exist_start_time = time_get_millis();
            return;
        }
    }

    if (data.dialog_type != FILE_DIALOG_SAVE && !vfs::file_exists(full)) {
        data.message_not_exist_start_time = time_get_millis();
        return;
    }

    if (data.dialog_type == FILE_DIALOG_LOAD) {
        if (data.type == FILE_TYPE_SAVED_GAME) {
            if (GamestateIO::load_savegame(full)) {
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
            if (vfs::file_has_extension(full, saved_game_data.extension)) {
                vfs::file_change_extension(full, saved_game_data_expanded.extension);
            }

            if (!vfs::file_has_extension(full, saved_game_data_expanded.extension)) {
                vfs::file_append_extension(full, saved_game_data_expanded.extension);
            }

            GamestateIO::write_savegame(full);
            window_city_show();
        } else if (data.type == FILE_TYPE_SCENARIO) {
            if (!vfs::file_has_extension(full, map_file_data.extension)) {
                vfs::file_append_extension(full, map_file_data.extension);
            }

            game_file_editor_write_scenario(full);
            window_editor_map_show();
        }
    } else if (data.dialog_type == FILE_DIALOG_DELETE) {
        if (GamestateIO::delete_savegame(filename)) {
            vfs::dir_find_files_with_extension(".", data.file_data->extension);
            vfs::dir_append_files_with_extension(".", saved_game_data_expanded.extension);

            data.panel->clamp_scrollbar_position();
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
    auto& data = g_file_dialog;
    if (index >= data.panel->get_total_entries()) {
        return clear_chosen_filename();
    }

    xstring entry = data.panel->get_selected_entry_text(FILE_NO_EXT);
    set_chosen_filename(entry.c_str());
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
    if (g_file_dialog.dialog_type != FILE_DIALOG_DELETE)
        button_ok_cancel(1, 0);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_file_dialog;
    if (input_go_back_requested(m, h)) {
        input_box_stop(&file_name_input);
        window_go_back();
    }

    if (input_box_is_accepted(&file_name_input)) {
        button_ok_cancel(1, 0);
        return;
    }

    mouse m_buttons = *mouse_in_dialog(m);
    if (image_buttons_handle_mouse(&m_buttons, { 0, 0 }, image_buttons, 2, 0)) {
        return;
    }

    mouse m_dialog = *mouse_in_dialog(m);
    m_dialog.x -= 140;
    m_dialog.y -= 120;
    if (input_box_handle_mouse(&m_dialog, &file_name_input)
        || data.panel->input_handle(&m_dialog)) {
        return;
    }
}

void window_file_dialog_show(file_type type, file_dialog_type dialog_type) {
    if (!g_file_dialog.panel) {
        g_file_dialog.panel = new scroll_list_panel(NUM_FILES_IN_VIEW,
                                                    button_select_file,
                                                    button_none,
                                                    button_double_click,
                                                    button_none,
                                                    ui_params,
                                                    true,
                                                    "Save/",
                                                    "folders");
    }

    static window_type window = {
        WINDOW_FILE_DIALOG,
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };

    init(type, dialog_type);
    window_show(&window);
}
