#pragma once

#include "content/vfs.h"

enum file_type {
    FILE_TYPE_SAVED_GAME = 0,
    FILE_TYPE_SCENARIO = 1
};

struct file_type_data {
    char extension[4];
    vfs::path last_loaded_file;
};

extern file_type_data saved_game_data;
extern file_type_data saved_game_data_expanded;
extern file_type_data map_file_data;

file_type_data *file_data_for_file_type(file_type t);
void window_file_dialog_load_show(int type);

