#include "file_dialog_delete.h"

#include "window/autoconfig_window.h"
#include "game/game.h"
#include "js/js_game.h"
#include "core/profiler.h"

void window_file_dialog_delete_show(int type) {
    game.pending_delete_type = (uint8_t)(file_type)type;
    autoconfig_window::show("file_dialog_delete");
}
ANK_FUNCTION_1(window_file_dialog_delete_show)
