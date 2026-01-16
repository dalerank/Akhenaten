#include "speed_options.h"

#include "game/settings.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "game/game.h"
#include "input/input.h"

#include "js/js_events.h"
#include "graphics/elements/ui_js.h"

speed_options_window g_speed_options_window;

struct speed_options_window_draw { vec2i pos; };
struct speed_options_window_init { vec2i pos; };
struct speed_options_window_cancel { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(speed_options_window_draw, pos);
ANK_REGISTER_STRUCT_WRITER(speed_options_window_init, pos);
ANK_REGISTER_STRUCT_WRITER(speed_options_window_cancel, pos);

void speed_options_window::init() {
    autoconfig_window::init();
    ui.event(speed_options_window_init{ pos });
}

void speed_options_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.event(speed_options_window_draw{ pos });
    ui.end_widget();
}

int speed_options_window::ui_handle_mouse(const mouse *m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        ui.event(speed_options_window_cancel{ pos });
    }

    return result;
}

int speed_options_window::handle_mouse(const mouse *m) {
    return 0;
}

void speed_options_window::show(close_callback_t cb) {
    static window_type window = {
        WINDOW_SPEED_OPTIONS,
        window_draw_underlying_window,
        [] (int flags) { g_speed_options_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_speed_options_window.ui_handle_mouse(m); }
    };

    g_speed_options_window.init();

    window_show(&window);
}
