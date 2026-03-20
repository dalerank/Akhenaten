#include "file_dialog_load.h"

#include "file_dialog_common.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/encoding.h"
#include "core/string.h"
#include "content/dir.h"
#include "game/file_editor.h"
#include "graphics/graphics.h"
#include "graphics/elements/scroll_list_panel.h"
#include "graphics/elements/ui.h"
#include "graphics/elements/generic_button.h"
#include "graphics/screen.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "graphics/text.h"
#include "input/input.h"
#include "content/vfs.h"
#include "io/gamestate/boilerplate.h"
#include "widget/input_box.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/autoconfig_window.h"
#include "game/settings.h"
#include "game/game.h"
#include "game/game_config.h"
#include "io/manager.h"
#include "js/js_game.h"

#include <cstring>

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

static scrollable_list_ui_params ui_params = [] {
    scrollable_list_ui_params ret;
    ret.blocks_x = 20;
    ret.blocks_y = NUM_FILES_IN_VIEW + 1;
    ret.draw_scrollbar_always = true;
    return ret;
}();

static input_box file_name_input = {144, 80, 20, 2, FONT_NORMAL_WHITE_ON_DARK};

struct file_dialog_load : public autoconfig_window_t<file_dialog_load> {
    time_millis message_not_exist_start_time;
    file_type type;
    int focus_button_id;

    file_type_data* file_data;
    uint8_t typed_name[MAX_FILE_NAME];
    char selected_file[MAX_FILE_NAME];
    scrollable_list * panel = nullptr;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override { return 0; }
    virtual void init() override {}
};

file_dialog_load g_file_dialog_load;

/** UTF-8: last path segment, then strip one extension (matches list FILE_NO_EXT entries). */
static void utf8_basename_strip_extension(pcstr src, char* out, size_t out_sz) {
    out[0] = '\0';
    if (!src || !*src || out_sz == 0) {
        return;
    }
    pcstr s = src;
    pcstr slash = strrchr(s, '/');
    if (!slash) {
        slash = strrchr(s, '\\');
    }
    s = slash ? slash + 1 : s;
    strncpy(out, s, out_sz - 1);
    out[out_sz - 1] = '\0';
    vfs::file_remove_extension(out);
}

/** Basename for load dialog: persisted last_loaded_file, else session / last written save path. */
static void resolve_load_dialog_basename_utf8(file_type type, char* out, size_t out_sz) {
    out[0] = '\0';
    file_type_data* fd = type == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;

    if (strlen(fd->last_loaded_file) > 0) {
        utf8_basename_strip_extension(fd->last_loaded_file, out, out_sz);
        if (out[0]) {
            return;
        }
    }

    if (type == FILE_TYPE_SAVED_GAME) {
        if (game.session.last_loaded == e_session_save && !game.session.last_loaded_mission.empty()) {
            utf8_basename_strip_extension(game.session.last_loaded_mission.c_str(), out, out_sz);
            if (out[0]) {
                return;
            }
        }
        const xstring last_write = game_features::gameopt_last_save_filename.to_string();
        if (!last_write.empty()) {
            utf8_basename_strip_extension(last_write.c_str(), out, out_sz);
        }
    } else {
        if (game.session.last_loaded == e_session_custom_map && !game.session.last_loaded_mission.empty()) {
            utf8_basename_strip_extension(game.session.last_loaded_mission.c_str(), out, out_sz);
        }
    }
}

static void set_chosen_filename(const char* name) {
    auto& data = g_file_dialog_load;
    if (!name) {
        name = "";
    }
    strncpy(data.selected_file, name, MAX_FILE_NAME - 1);
    data.selected_file[MAX_FILE_NAME - 1] = '\0';
    encoding_from_utf8(data.selected_file, data.typed_name, MAX_FILE_NAME);
}

static void clear_chosen_filename() {
    set_chosen_filename("");
}

static bool is_chosen_filename(int index) {
    auto& data = g_file_dialog_load;
    return string_compare_case_insensitive(
               data.panel->get_selected_entry_text(FILE_NO_EXT).c_str(),
               data.selected_file) == 0;
}

static bool is_valid_chosen_filename() {
    auto& data = g_file_dialog_load;
    if (strcmp(data.selected_file, "") == 0)
        return false;
    if (data.panel->get_entry_idx(data.selected_file) > -1)
        return true;
    return false;
}

static const char* get_chosen_filename(void) {
    auto& data = g_file_dialog_load;
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

static void init(file_type type) {
    auto& data = g_file_dialog_load;
    data.type = type;
    data.file_data = type == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;

    char hint[MAX_FILE_NAME];
    resolve_load_dialog_basename_utf8(type, hint, sizeof(hint));
    set_chosen_filename(hint[0] ? hint : "");

    data.message_not_exist_start_time = 0;

    // populate file list
    char folder_name[MAX_FILE_NAME] = "Save/";
    strcat(folder_name, (pcstr)g_settings.player_name);
    strcat(folder_name, "/");
    if (type == FILE_TYPE_SCENARIO) {
        data.panel->change_file_path("Maps/", map_file_data.extension);
    } else {
        data.panel->change_file_path(folder_name, data.file_data->extension);
        data.panel->append_files_with_extension(folder_name, saved_game_data_expanded.extension);
    }

    // Highlight list row for last_loaded_file (only input text was set before; list had no selection)
    if (strlen(data.selected_file) > 0 && data.panel->has_entry(data.selected_file)) {
        data.panel->select(data.selected_file);
        data.panel->scroll_to_entry(data.panel->get_selected_entry_idx());
    } else {
        data.panel->unselect();
    }

    input_box_start(&file_name_input, data.typed_name, MAX_FILE_NAME, 0);
}

static const vec2i list_pos = {144, 120};

static void draw_foreground(int) {
    auto& data = g_file_dialog_load;

    data.panel->ui_params.pos = list_pos;
    ui::begin_widget(screen_dialog_offset());
    ui::panel(vec2i{128, 40}, vec2i{24, 21}, UiFlags_PanelOuter);
    if (data.message_not_exist_start_time
        && time_get_millis() - data.message_not_exist_start_time < NOT_EXIST_MESSAGE_TIMEOUT) {
        ui::label(43, 2, vec2i{160, 50}, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_AlignCentered, 304);
    } else {
        int text_id = 1 + (data.type == FILE_TYPE_SCENARIO ? 3 : 0);
        ui::label(43, text_id, vec2i{160, 50}, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_AlignCentered, 304);
    }
    ui::label(43, 5, vec2i{224, 342}, FONT_NORMAL_BLACK_ON_LIGHT);

    {
        ui::begin_widget(list_pos, true);
        data.panel->draw();
        ui::end_widget();
    }
    ui::end_widget();

    ui::flush_commands();

    graphics_set_to_dialog();
    input_box_draw(&file_name_input);
    image_buttons_draw({0, 0}, image_buttons, 2);
    graphics_reset_dialog();
}

static void button_ok_cancel(int is_ok, int param2) {
    auto& data = g_file_dialog_load;
    if (!is_ok) {
        input_box_stop(&file_name_input);
        window_go_back();
        return;
    }

    bstring256 filename(get_chosen_filename(), ".", saved_game_data.extension);
    bstring256 full = fullpath_saves(filename);

    if (!vfs::file_exists(full)) {
        filename = bstring256(get_chosen_filename(), ".", saved_game_data_expanded.extension);
        full = fullpath_saves(filename);
    }

    if (!vfs::file_exists(full)) {
        data.message_not_exist_start_time = time_get_millis();
        return;
    }

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

    strncpy(data.file_data->last_loaded_file, get_chosen_filename(), MAX_FILE_NAME - 1);
    data.file_data->last_loaded_file[MAX_FILE_NAME - 1] = '\0';
}

static void button_select_file(int index, int param2) {
    auto& data = g_file_dialog_load;
    if (index >= data.panel->items_count()) {
        return clear_chosen_filename();
    }

    xstring entry = data.panel->get_selected_entry_text(FILE_NO_EXT);
    set_chosen_filename(entry.c_str());
    input_box_refresh_text(&file_name_input);
    data.message_not_exist_start_time = 0;
}

static void button_double_click(int param1, int param2) {
    button_ok_cancel(1, 0);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_file_dialog_load;
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
    if (input_box_handle_mouse(&m_dialog, &file_name_input)
        || data.panel->input_handle(&m_dialog)) {
        return;
    }
}

void window_file_dialog_load_show(int type) {
    if (!g_file_dialog_load.panel) {
        ui_params.use_file_finder = true;
        ui_params.view_items = NUM_FILES_IN_VIEW;
        ui_params.files_dir = "Save/";
        ui_params.file_ext = "folders";
        g_file_dialog_load.panel = new scrollable_list(button_select_file,
                                                  button_none,
                                                  button_double_click,
                                                  button_none,
                                                  ui_params);
    }

    static window_type window = {
        "window_file_dialog",
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };

    init((file_type)type);
    window_show(&window);
}
ANK_FUNCTION_1(window_file_dialog_load_show)

