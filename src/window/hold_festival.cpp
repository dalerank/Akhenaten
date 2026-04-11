#include "hold_festival.h"

#include "core/profiler.h"
#include "city/city.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/window_city.h"
#include "widget/widget_sidebar.h"
#include "game/game.h"
#include "js/js_game.h"

ui::hold_festival_window g_hold_festival_window;

void __hold_festival_window_show(bool bg, js_helpers::js_function_ref cb) {
    ui::hold_festival_window::show(bg, [cb] {
        if (!cb.empty()) {
            js_call_function(cb.ref);
        }
    });
}
ANK_FUNCTION_2(__hold_festival_window_show)

void __hold_festival_window_ok() {
    if (!g_city.finance.is_out_of_money()) {
        g_city.festival.schedule();
    }
    g_hold_festival_window.close();
}
ANK_FUNCTION(__hold_festival_window_ok)

void __hold_festival_window_cancel() {
    g_hold_festival_window.close();
}
ANK_FUNCTION(__hold_festival_window_cancel)

bool __hold_festival_window_has_background() {
    return g_hold_festival_window.background;
}
ANK_FUNCTION(__hold_festival_window_has_background)

void ui::hold_festival_window::close() {
    if (callback) {
        callback();
    }

    window_go_back();
}

void ui::hold_festival_window::show(bool bg, std::function<void()> cb) {
    static window_type window = {
        "window_hold_festival",
        [] (int flags) { g_hold_festival_window.draw_background(flags); },
        [] (int flags) { g_hold_festival_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_hold_festival_window.ui_handle_mouse(m); },
    };

    g_hold_festival_window.callback = cb;
    g_hold_festival_window.background = bg;
    g_hold_festival_window.init();
    window_show(&window);
}
