#pragma once

#include "content/vfs.h"

enum file_type {
    FILE_TYPE_SAVED_GAME = 0,
    FILE_TYPE_SCENARIO = 1
};

struct file_type_data {
    char extension[4];
    char last_loaded_file[MAX_FILE_NAME];
};

extern file_type_data saved_game_data;
extern file_type_data saved_game_data_expanded;
extern file_type_data map_file_data;

