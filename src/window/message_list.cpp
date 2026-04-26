#include "message_list.h"

#include "core/profiler.h"
#include "city/city_message.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "game/game.h"
#include "js/js_game.h"

ui::message_list_window g_message_list_window;

void __message_list_window_open_entry(int index) {
    int id = city_message_set_current(index);
    if (id < city_message_count()) {
        const city_message& msg = city_message_get(id);
        const xstring mm_msg = lang_get_message_id(msg.MM_text_id);
        city_message_mark_read(id);
        window_message_dialog_show_city_message(mm_msg, id, msg.year, msg.month, msg.param1, msg.param2, msg.MM_text_id, 0);
    }
}
ANK_FUNCTION_1(__message_list_window_open_entry)

void ui::message_list_window::show() {
    static window_type instance = {
        "window_message_list",
        [] (int flags) { g_message_list_window.draw_background(flags); },
        [] (int flags) { g_message_list_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_message_list_window.ui_handle_mouse(m); }
    };

    // Run each open: refresh list (script init) and button handlers; draw_background skips init when already inited.
    g_message_list_window.init();

    window_show(&instance);
}

void window_message_list_show(void) {
    ui::message_list_window::show();
}
