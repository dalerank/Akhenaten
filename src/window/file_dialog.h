#pragma once

#include "file_dialog_common.h"
#include "file_dialog_save.h"
#include "file_dialog_load.h"
#include "file_dialog_delete.h"

void window_file_dialog_save_show(file_type type);
void window_file_dialog_load_show(file_type type);
void window_file_dialog_delete_show(file_type type);
