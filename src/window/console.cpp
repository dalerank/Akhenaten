#include "window/console.h"

#include "city/city_warnings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "core/string.h"
#include "core/log.h"
#include "core/profiler.h"
#include "widget/debug_console.h"
#include "graphics/graphics.h"
#include "building/construction/build_planner.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/ui.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/window_city.h"
#include "widget/input_box.h"

#include "js/js_game.h"

static void send_command(int param1, int param2);
static void button_back(int param1, int param2);

static image_button image_buttons[] = {
    {0, 2, 31, 20, IB_NORMAL, PACK_GENERAL, 90, 8, button_back, button_none, 0, 0, 1},
    {305, 0, 27, 27, IB_NORMAL, PACK_GENERAL, 193, 4, send_command, button_none, 1, 0, 1}
};

static input_box command_input = {160, 208, 20, 2, FONT_NORMAL_WHITE_ON_DARK};

static bstring64 command = "";

static void init(void) {
    input_box_start(&command_input, (uint8_t*)command, command.capacity, 1);
}

static void draw_foreground(int) {
    const vec2i base = g_screen.dialog_offset;
    ui::panel_abs(base + vec2i{128, 160}, {24, 8});
    ui::text_centered_abs("Console", base + vec2i{128, 172}, 384, FONT_LARGE_BLACK_ON_LIGHT);
    ui::text_abs(ui::str(13, 5), base + vec2i{352, 256}, FONT_NORMAL_BLACK_ON_LIGHT);
    ui::text_abs(ui::str(12, 0), base + vec2i{200, 256}, FONT_NORMAL_BLACK_ON_LIGHT);
    input_box_draw(&command_input);

    image_buttons_push_commands(base + vec2i{159, 249}, image_buttons, 2);
}

static void handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = m->in_dialog();
    if (input_box_handle_mouse(m_dialog, &command_input) || image_buttons_handle_mouse(m_dialog, {159, 249}, image_buttons, 2, 0)) {
        return;
    }
   
    if (input_box_is_accepted(&command_input)) {
        send_command(0, 0);
        return;
    }

    if (input_go_back_requested(m, h)) {
        button_back(0, 0);
    }
}

static void button_back(int param1, int param2) {
    input_box_stop(&command_input);
    window_go_back();
}

static void send_command(int param1, int param2) {
    xstring command_copy;
    command_copy = (pcstr)command_input.text;
    button_back(0, 0);
    logs::info("Command received: %s", command_copy.c_str());
    events::emit(event_city_warning{ command_copy });
    run_debug_command(command_copy.c_str());
}

void window_console_show() {
    static window_type window = {
        "window_file_dialog",
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };

    init();
    window_show(&window);
}

void window_show_cheat_console(bool) {
    g_city_planner.reset();
    window_city_show();
    window_console_show();
}
ANK_FUNCTION_1(window_show_cheat_console)