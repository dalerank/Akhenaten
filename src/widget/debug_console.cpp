#include "graphics/boilerplate.h"

#include "graphics/screen.h"
#include "graphics/text.h"
#include "core/bstring.h"

static int log_history_index = 0;
static bstring256 log_history_buf[40];

void debug_append_console_message(const char *msg) {
    log_history_buf[log_history_index] = msg;
    log_history_index++;
    log_history_index %= 40;
}

void debug_console_window_init() {
}

void debug_console_window_draw() {
    int i = 0;
    int y_offset = 0;
    graphics_fill_rect(0, 0, screen_width(), 40 * 12, 0x800055ff);

    for (; i < 40; i++) {
        text_draw(log_history_buf[(i + log_history_index)%40], 5, y_offset, FONT_NORMAL_WHITE_ON_DARK, COLOR_FONT_LIGHT_GRAY);
        y_offset += 12;
    }
}
