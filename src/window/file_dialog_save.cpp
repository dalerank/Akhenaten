#include "file_dialog_save.h"

#include "file_dialog_common.h"
#include "core/profiler.h"
#include "window/autoconfig_window.h"
#include "game/settings.h"
#include "content/vfs.h"
#include "io/gamestate/boilerplate.h"
#include "game/file_editor.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "js/js_game.h"
#include "core/bstring.h"
#include "core/log.h"

#include <cstdio>
#include <cstring>

static file_type g_file_dialog_save_pending_type = FILE_TYPE_SAVED_GAME;

void window_file_dialog_save_show(file_type type) {
    g_file_dialog_save_pending_type = type;
    autoconfig_window::show("file_dialog_save");
}

static file_type_data *file_data_for_pending_type() {
    return g_file_dialog_save_pending_type == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;
}

int __file_dialog_save_get_pending_type() {
    return (int)g_file_dialog_save_pending_type;
} ANK_FUNCTION(__file_dialog_save_get_pending_type)

static char g_file_dialog_dir_buf[MAX_FILE_NAME];

pcstr __file_dialog_save_get_files_dir_utf8() {
    if (g_file_dialog_save_pending_type == FILE_TYPE_SCENARIO) {
        return "Maps/";
    }
    snprintf(g_file_dialog_dir_buf, sizeof(g_file_dialog_dir_buf), "Save/%s/", g_settings.player_name.c_str());
    return g_file_dialog_dir_buf;
} ANK_FUNCTION(__file_dialog_save_get_files_dir_utf8)

pcstr __file_dialog_save_get_files_ext_utf8() {
    return g_file_dialog_save_pending_type == FILE_TYPE_SCENARIO
        ? map_file_data.extension
        : saved_game_data_expanded.extension;
} ANK_FUNCTION(__file_dialog_save_get_files_ext_utf8)

pcstr __file_dialog_save_get_initial_filename_utf8() {
    file_type_data *fd = file_data_for_pending_type();
    if (strlen(fd->last_loaded_file) == 0) {
        return g_file_dialog_save_pending_type == FILE_TYPE_SCENARIO ? "scenario" : "savegame";
    }
    return fd->last_loaded_file;
} ANK_FUNCTION(__file_dialog_save_get_initial_filename_utf8)

void __file_dialog_save_commit(pcstr base_name_utf8) {
    if (!base_name_utf8 || !*base_name_utf8) {
        return;
    }

    file_type type = g_file_dialog_save_pending_type;
    file_type_data *file_data = file_data_for_pending_type();

    bstring256 filename(base_name_utf8, ".", saved_game_data_expanded.extension);

    vfs::path full = fullpath_saves(filename);

    if (type == FILE_TYPE_SAVED_GAME) {
        GamestateIO::write_savegame(full.c_str());
        window_city_show();
    } else if (type == FILE_TYPE_SCENARIO) {
        const bool has_map = vfs::file_has_extension(full.c_str(), map_file_data.extension);
        if (!has_map) {
            vfs::file_append_extension(full.data(), map_file_data.extension);
        }

        game_file_editor_write_scenario(full.c_str());
        window_editor_map_show();
    }

    file_data->last_loaded_file = base_name_utf8;
} ANK_FUNCTION_1(__file_dialog_save_commit)
