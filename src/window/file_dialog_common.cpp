#include "file_dialog_common.h"

#include "js/js_game.h"

file_type_data saved_game_data = {"sav"};
file_type_data saved_game_data_expanded = {"svx"};
file_type_data map_file_data = {"map"};

file_type_data *file_data_for_file_type(file_type t) {
    return t == FILE_TYPE_SCENARIO ? &map_file_data : &saved_game_data;
}

void __set_last_loaded_utf8(int type, pcstr basename) {
    if (!basename) {
        return;
    }
    file_type_data *fdata = file_data_for_file_type((file_type)type);
    fdata->last_loaded_file = basename;
}
ANK_FUNCTION_2(__set_last_loaded_utf8)
