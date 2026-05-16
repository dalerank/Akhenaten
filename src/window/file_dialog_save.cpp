#include "file_dialog_save.h"

#include "window/autoconfig_window.h"
#include "game/game.h"
#include "js/js_game.h"
#include "core/profiler.h"

void window_file_dialog_save_show(file_type type) {
    game.pending_save_type = (uint8_t)type;
    autoconfig_window::show("file_dialog_save");
}
ANK_FUNCTION_1(window_file_dialog_save_show)
