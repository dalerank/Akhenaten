#include <core/game_environment.h>
#include <scenario/events.h>
#include "message_list.h"

#include "city/message.h"
#include "core/calc.h"
#include "core/image_group.h"
#include "core/lang.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/city.h"
#include "window/message_dialog.h"

#define MAX_MESSAGES 10

static void button_help(int param1, int param2);
static void button_close(int param1, int param2);
static void button_message(int param1, int param2);
static void button_delete(int param1, int param2);
static void on_scroll(void);

static image_button image_button_help = {
        0, 0, 27, 27, IB_NORMAL, GROUP_CONTEXT_ICONS, 0, button_help, button_none, 0, 0, 1
};
static image_button image_button_close = {
        0, 0, 24, 24, IB_NORMAL, GROUP_CONTEXT_ICONS, 4, button_close, button_none, 0, 0, 1
};
static generic_button generic_buttons_messages[] = {
        {0, 0,   412, 18, button_message, button_delete, 0, 0},
        {0, 20,  412, 18, button_message, button_delete, 1, 0},
        {0, 40,  412, 18, button_message, button_delete, 2, 0},
        {0, 60,  412, 18, button_message, button_delete, 3, 0},
        {0, 80,  412, 18, button_message, button_delete, 4, 0},
        {0, 100, 412, 18, button_message, button_delete, 5, 0},
        {0, 120, 412, 18, button_message, button_delete, 6, 0},
        {0, 140, 412, 18, button_message, button_delete, 7, 0},
        {0, 160, 412, 18, button_message, button_delete, 8, 0},
        {0, 180, 412, 18, button_message, button_delete, 9, 0},
};

static scrollbar_type scrollbar = {432, 112, 208, on_scroll};

static struct {
    int width_blocks;
    int height_blocks;
    int x_text;
    int y_text;
    int text_width_blocks;
    int text_height_blocks;

    int focus_button_id;
} data;

static void init(void) {
    city_message_sort_and_compact();
    scrollbar_init(&scrollbar, city_message_scroll_position(), city_message_count() - MAX_MESSAGES);
}

static void draw_background(void) {
    window_city_draw_all();

    graphics_in_dialog();
    data.width_blocks = 30;
    data.height_blocks = 22;
    data.x_text = 16;
    data.y_text = 112;
    data.text_width_blocks = data.width_blocks - 4;
    data.text_height_blocks = data.height_blocks - 9;

    outer_panel_draw(0, 32, data.width_blocks, data.height_blocks);
    lang_text_draw_centered(63, 0, 0, 48, 16 * data.width_blocks, FONT_LARGE_BLACK);
    inner_panel_draw(data.x_text, data.y_text, data.text_width_blocks, data.text_height_blocks);

    if (city_message_count() > 0) {
        lang_text_draw(63, 2, data.x_text + 42, data.y_text - 12, FONT_SMALL_PLAIN);
        lang_text_draw(63, 3, data.x_text + 180, data.y_text - 12, FONT_SMALL_PLAIN);
        lang_text_draw_multiline(63, 4,
                                 data.x_text + 50, data.y_text + 12 + 16 * data.text_height_blocks,
                                 16 * data.text_width_blocks - 100, FONT_NORMAL_BLACK);
    } else {
        lang_text_draw_multiline(63, 1,
                                 data.x_text + 16, data.y_text + 80,
                                 16 * data.text_width_blocks - 48, FONT_NORMAL_GREEN);
    }
    graphics_reset_dialog();
}
static void draw_messages(int total_messages) {
    int max = total_messages < MAX_MESSAGES ? total_messages : MAX_MESSAGES;
    int index = scrollbar.scroll_position;
    for (int i = 0; i < max; i++, index++) {
        const city_message *msg = city_message_get(index);
        const lang_message *lang_msg = lang_get_message(city_message_get_text_id(msg->MM_text_id));

        int image_type_offset = 0;
        if (lang_msg->message_type == MESSAGE_TYPE_DISASTER)
            image_type_offset = 2;
        if (lang_msg->message_type == MESSAGE_TYPE_TUTORIAL)
            image_type_offset = 4;

        if (msg->is_read) {
            imagedrawnamespace::image_draw(image_id_from_group(GROUP_MESSAGE_ICON) + 15 + image_type_offset, data.x_text + 12,
                       data.y_text + 6 + 20 * i);
        } else
            imagedrawnamespace::image_draw(image_id_from_group(GROUP_MESSAGE_ICON) + 14 + image_type_offset, data.x_text + 12,
                       data.y_text + 6 + 20 * i);
        font_t font = FONT_NORMAL_WHITE;
        if (data.focus_button_id == i + 1)
            font = FONT_NORMAL_RED;

        if (false) {
            int o = -100;
            int oo = 45;
            font_t f = FONT_LARGE_PLAIN;
            color_t c = COLOR_WHITE;
            uint8_t str[10];

            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->eventmsg_body_id, c);
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->eventmsg_title_id, c); // FF FF
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_02, c); // FF FF
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_city, c);; // enum?

            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_amount, c);;
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_resource, c);;
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_months_left, c);
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_07, c);

            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->eventmsg_phrase_id, c);
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_city_past, c);; // enum?
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_09, c); // 00 00
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_10, c); // 00 00

            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_amount_past, c);;
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->req_resource_past, c);;
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_11a_i8, c);; // FF FF
            o += oo; draw_debug_line(str, data.x_text + o, data.y_text + 8 + 20 * i, 0, "", msg->unk_12, c);; // 00 00

            continue;
        }

        int width = lang_text_draw(25, msg->month, data.x_text + 42, data.y_text + 8 + 20 * i, font);
        lang_text_draw_year(msg->year, data.x_text + 42 + width, data.y_text + 8 + 20 * i, font);

        if (GAME_ENV == ENGINE_ENV_PHARAOH && msg->eventmsg_body_id != -1) {
            text_draw(get_eventmsg_text(msg->eventmsg_title_id, 0), data.x_text + 180, data.y_text + 8 + 20 * i, font, 0);
        } else if (lang_msg->title.text) // temp fix so it doesn't crash
            text_draw(lang_msg->title.text, data.x_text + 180, data.y_text + 8 + 20 * i, font, 0);
    }
    scrollbar_draw(&scrollbar);
}
static void draw_foreground(void) {
    graphics_in_dialog();
    image_buttons_draw(16, 32 + 16 * data.height_blocks - 42, &image_button_help, 1);
    image_buttons_draw(16 * data.width_blocks - 38, 32 + 16 * data.height_blocks - 36, &image_button_close, 1);

    int total_messages = city_message_count();
    if (total_messages > 0)
        draw_messages(total_messages);

    graphics_reset_dialog();
}

static void handle_input(const mouse *m, const hotkeys *h) {
    const mouse *m_dialog = mouse_in_dialog(m);
    int old_button_id = data.focus_button_id;
    data.focus_button_id = 0;

    int button_id;
    int handled = image_buttons_handle_mouse(m_dialog, 16, 32 + 16 * data.height_blocks - 42, &image_button_help, 1,
                                             &button_id);
    if (button_id)
        data.focus_button_id = 11;

    handled |= image_buttons_handle_mouse(m_dialog, 16 * data.width_blocks - 38,
                                          32 + 16 * data.height_blocks - 36, &image_button_close, 1, &button_id);
    if (button_id)
        data.focus_button_id = 12;

    if (scrollbar_handle_mouse(&scrollbar, m_dialog))
        data.focus_button_id = 13;

    handled |= generic_buttons_handle_mouse(m_dialog, data.x_text, data.y_text + 4,
                                            generic_buttons_messages, MAX_MESSAGES, &button_id);
    if (!data.focus_button_id)
        data.focus_button_id = button_id;

    if (button_id && old_button_id != button_id)
        window_invalidate();

    if (!handled && input_go_back_requested(m, h))
        button_close(0, 0);

}

static void on_scroll(void) {
    city_message_set_scroll_position(scrollbar.scroll_position);
    window_invalidate();
}

static void button_help(int param1, int param2) {
    window_message_dialog_show(MESSAGE_DIALOG_MESSAGES, -1, window_city_draw_all);
}
static void button_close(int param1, int param2) {
    window_city_show();
}
static void button_message(int param1, int param2) {
    int id = city_message_set_current(scrollbar.scroll_position + param1);
    if (id < city_message_count()) {
        const city_message *msg = city_message_get(id);
        city_message_mark_read(id);
        window_message_dialog_show_city_message(
                msg->MM_text_id,
                id,
                msg->year, msg->month, msg->param1, msg->param2,
                msg->MM_text_id,
                0);
    }
}
static void button_delete(int id_to_delete, int param2) {
    int id = city_message_set_current(scrollbar.scroll_position + id_to_delete);
    if (id < city_message_count()) {
        city_message_delete(id);
        scrollbar_update_max(&scrollbar, city_message_count() - MAX_MESSAGES);
        window_invalidate();
    }
}

static void get_tooltip(tooltip_context *c) {
    if (data.focus_button_id == 11)
        c->text_id = 1;
    else if (data.focus_button_id == 12)
        c->text_id = 2;
    else
        return;
    c->type = TOOLTIP_BUTTON;
}

void window_message_list_show(void) {
    window_type window = {
            WINDOW_MESSAGE_LIST,
            draw_background,
            draw_foreground,
            handle_input,
            get_tooltip
    };
    init();
    window_show(&window);
}
