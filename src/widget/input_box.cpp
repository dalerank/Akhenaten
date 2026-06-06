#include "input_box.h"

#include "core/encoding.h"
#include "core/string.h"

#include <cstring>
#include "graphics/elements/ui.h"
#include "input/keyboard.h"
#include "graphics/screen.h"
#include "graphics/text.h"

using namespace ui::opt;

void input_box_start(input_box* box, uint8_t* text, int length, int allow_punctuation) {
    box->text = text;
    box->max_length = length;
    box->allow_punctuation = allow_punctuation;
    int text_width = (box->width_blocks - 2) * INPUT_BOX_BLOCK_SIZE;
    g_keyboard.start_capture(text, length, allow_punctuation, text_width, box->font, box->multiline);
    g_keyboard.set_input_rect(box->x, box->y, box->width_blocks * INPUT_BOX_BLOCK_SIZE, box->height_blocks * INPUT_BOX_BLOCK_SIZE);
}

void input_box_pause(input_box* box) {
    g_keyboard.pause_capture();
}

void input_box_resume(input_box* box) {
    g_keyboard.resume_capture();
}

void input_box_stop(input_box* box) {
    box->text = 0;
    g_keyboard.stop_capture();
    g_keyboard.set_input_rect(0, 0, 0, 0);
}

void input_box_refresh_text(input_box* box) {
    g_keyboard.refresh();
}

int input_box_is_accepted(input_box* box) {
    return g_keyboard.input_is_accepted();
}

static int is_mouse_inside_input(const mouse* m, const input_box* box) {
    return m->x >= box->x && m->x < box->x + box->width_blocks * INPUT_BOX_BLOCK_SIZE && m->y >= box->y
           && m->y < box->y + box->height_blocks * INPUT_BOX_BLOCK_SIZE;
}

void input_box_draw(const input_box* box) {
    const vec2i base = g_screen.dialog_offset;
    const int text_x = box->x + 16;
    const int text_y = box->y + 10;
    const vec2i panel_px = {box->width_blocks * INPUT_BOX_BLOCK_SIZE, box->height_blocks * INPUT_BOX_BLOCK_SIZE};

    ui::push(ui::cmd_t::panel_inner, Pos{base + vec2i{box->x, box->y}}, Size{vec2i{box->width_blocks, box->height_blocks}});

    if (box->multiline) {
        const int box_width_px = (box->width_blocks - 2) * INPUT_BOX_BLOCK_SIZE;
        char utf8_buf[8192];
        encoding_to_utf8(box->text, utf8_buf, (int)sizeof(utf8_buf), encoding_system_uses_decomposed());
        const vec2i text_origin = base + vec2i{text_x, text_y - 3};
        ui::push(ui::cmd_t::clip_set, Pos{base + vec2i{box->x, box->y}}, Size{panel_px});
        ui::push(ui::cmd_t::text_multiline, Pos{text_origin}, BoxWidth{box_width_px}, Font{box->font}, TextColor{0},
          Caption{utf8_buf});
        ui::push(ui::cmd_t::clip_reset);

        const int caret_here = g_keyboard.is_capturing_buffer(box->text);
        if (caret_here) {
            uint8_t prefix_internal[8192];
            int ci = g_keyboard.get_cursor_abs_offset();
            const int text_len = string_length(box->text);
            if (ci > text_len) {
                ci = text_len;
            }
            memcpy(prefix_internal, box->text, ci);
            prefix_internal[ci] = 0;
            char prefix_utf8[8192];
            encoding_to_utf8(prefix_internal, prefix_utf8, (int)sizeof(prefix_utf8), encoding_system_uses_decomposed());
            const int cursor_utf8_byte = (int)strlen(prefix_utf8);

            vec2i caret_screen;
            text_multiline_cursor_screen_pos(utf8_buf, cursor_utf8_byte, text_origin, box_width_px, box->font, &caret_screen);
            text_draw_cursor(0, 0, g_keyboard.is_insert(), caret_screen);
        }
    } else {
        const int caret_here = g_keyboard.is_capturing_buffer(box->text);
        if (caret_here) {
            ui::cursor_capture(g_keyboard.get_cursor_position(), g_keyboard.get_offset_start(), g_keyboard.get_offset_end());
        }
        ui::push(ui::cmd_t::text_colored, Pos{base + vec2i{text_x, text_y - 3}}, Font{box->font}, TextColor{0}, BoxWidth{0},
          Caption{(pcstr)box->text});
        if (caret_here) {
            text_draw_cursor(text_x, text_y + 1, g_keyboard.is_insert(), base + vec2i{text_x, text_y + 1});
            ui::cursor_consume();
        }
    }
}

int input_box_handle_mouse(const mouse* m, const input_box* box) {
    if (!m->left.went_up)
        return 0;

    int selected = is_mouse_inside_input(m, box);
    if (selected) {
        const int text_width = (box->width_blocks - 2) * INPUT_BOX_BLOCK_SIZE;
        g_keyboard.stop_capture();
        g_keyboard.start_capture(
          box->text, box->max_length, box->allow_punctuation, text_width, box->font, box->multiline);
        if (box->host_input) {
            ui::set_active_text_input(static_cast<ui::einput*>(box->host_input));
        }
        g_keyboard.show_virtual(box->text, box->max_length);
    } else {
        g_keyboard.hide_virtual();
    }
    return selected;
}
