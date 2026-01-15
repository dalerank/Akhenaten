#include "speed_options.h"

#include "game/settings.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "game/game.h"
#include "input/input.h"

speed_options_window g_speed_options_window;

void speed_options_window::close() {
    if (close_callback) {
        close_callback();
    }
    window_go_back();
}

void speed_options_window::init() {
    autoconfig_window::init();

    // Set up buttons
    ui["btn_ok"].onclick([this] {
        this->close();
    });

    ui["btn_cancel"].onclick([this] {
        game.game_speed = this->original_game_speed;
        g_settings.scroll_speed = this->original_scroll_speed;
        this->close();
    });

    // Set up arrow buttons for game speed
    ui["arrow_game_down"].onclick([this] (int, int) {
        game.decrease_game_speed();
    });

    ui["arrow_game_up"].onclick([this] (int, int) {
        game.increase_game_speed();
    });

    // Set up arrow buttons for scroll speed
    ui["arrow_scroll_down"].onclick([this] (int, int) {
        g_settings.decrease_scroll_speed();
    });

    ui["arrow_scroll_up"].onclick([this] (int, int) {
        g_settings.increase_scroll_speed();
    });
}

void speed_options_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    
    // Update dynamic text values
    ui["game_speed_value"].text_var("%d%%", game.game_speed);
    ui["scroll_speed_value"].text_var("%d%%", g_settings.scroll_speed);
    
    ui.end_widget();
}

int speed_options_window::ui_handle_mouse(const mouse *m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        close();
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

    g_speed_options_window.close_callback = cb;
    g_speed_options_window.original_game_speed = game.game_speed;
    g_speed_options_window.original_scroll_speed = g_settings.scroll_speed;
    g_speed_options_window.pos = screen_dialog_offset();
    g_speed_options_window.init();

    window_show(&window);
}

void window_speed_options_show(void (*close_callback)(void)) {
    speed_options_window::show(close_callback);
}
