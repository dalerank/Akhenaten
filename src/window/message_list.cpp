#include "message_list.h"

#include "scenario/scenario.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/elements/lang_text.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "game/game.h"


ui::message_list_window g_message_list_window;

void ui::message_list_window::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    num_messages_in_view = arch.r_int("num_messages_in_view", 15);
}

static void button_message_handler(int param1, int param2) {
    int id = city_message_set_current(param1);
    if (id < city_message_count()) {
        const city_message& msg = city_message_get(id);
        const xstring mm_msg = lang_get_message_id(msg.MM_text_id);
        city_message_mark_read(id);
        window_message_dialog_show_city_message(mm_msg, id, msg.year, msg.month, msg.param1, msg.param2, msg.MM_text_id, 0);
    }
}

static void button_delete_handler(int id_to_delete, int param2) {
    int id = city_message_set_current(id_to_delete);
    if (id < city_message_count()) {
        city_message_delete(id);
    }
}

void ui::message_list_window::init() {
    autoconfig_window::init();
    city_message_sort_and_compact();

    if (!panel) {
        scrollable_list_ui_params ui_params;
        ui_params.blocks_x = ui["messages_area"].size.x;
        ui_params.blocks_y = ui["messages_area"].size.y;
        ui_params.buttons_size_y = ui["message_row"].size.y;
        ui_params.draw_scrollbar_always = true;

        panel = new scroll_list_panel(num_messages_in_view,
                                      button_message_handler,
                                      button_delete_handler,
                                      button_none,
                                      button_none,
                                      ui_params, false, "", "");
    }
    
    panel->clear_entry_list();
    int total_messages = city_message_count();
    for (int i = 0; i < total_messages; i++) {
        const city_message &msg = city_message_get(i);      
        panel->add_entry("", (void*)&msg);
    }

    panel->set_custom_render_func([this] (int index, int flags, const scroll_list_panel::entry_data &entry, vec2i pos, e_font font) {
        this->draw_message(index, flags, entry, pos, font);
    });

    ui["btnhelp"].onclick([this] {
        window_message_dialog_show("message_dialog_messages", -1, window_city_draw_all);
    });

    ui["btnclose"].onclick([this] {
        if (_close_cb) {
            _close_cb();
        }
    });
}

void ui::message_list_window::draw_message(int index, int flags, const scroll_list_panel::entry_data &entry, vec2i pos, e_font font) {
    painter ctx = game.painter();

    const auto &message_row = ui["message_row"];
    const auto &message_read_icon = ui["message_read_icon"];
    const auto &message_month = ui["message_month"];
    const auto &message_year = ui["message_year"];
    const auto &message_title = ui["message_title"];
    int y_text = pos.y + message_row.pos.y;
    int x_text = pos.x + message_row.pos.x;

    const city_message& msg = *(const city_message*)entry.user_data;
    const int mm_id = city_message_get_text_id(index);
    const lang_message& lang_msg = lang_get_message(mm_id);

    int image_type_offset = 0;
    if (lang_msg.message_type == MESSAGE_TYPE_DISASTER)
        image_type_offset = 2;

    if (lang_msg.message_type == MESSAGE_TYPE_TUTORIAL)
        image_type_offset = 4;

    ImageDraw::img_generic(ctx, image_id_from_group(PACK_GENERAL, 90) + (msg.is_read ? 15 : 14) + image_type_offset, x_text + message_read_icon.pos.x, y_text + message_read_icon.pos.y);

    font = (flags) ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;

    lang_text_draw(25, msg.month, x_text + message_month.pos.x, y_text + message_month.pos.y, font);
    lang_text_draw_year(msg.year, x_text + message_year.pos.x, y_text + message_year.pos.y, font);

    if (msg.eventmsg_body_id != -1) {
        auto text = g_scenario.events.msg_text(msg.eventmsg_title_id, 0);
        text_draw(text, x_text + message_title.pos.x, y_text + message_title.pos.y, font, 0);
    } else if (!lang_msg.title.text.empty()) {
        text_draw(lang_msg.title.text.c_str(), x_text + message_title.pos.x, y_text + message_title.pos.y, font, 0);
    }
}

int ui::message_list_window::draw_background(UiFlags flags) {
    return autoconfig_window::draw_background(flags);
}

void ui::message_list_window::ui_draw_foreground(UiFlags flags) {
    window_city_draw_all();

    ui.begin_widget(pos);
    
    ui.draw();
    panel->ui_params.pos = ui["messages_area"].screen_pos();
    panel->draw();

    ui.end_widget();
}

int ui::message_list_window::ui_handle_mouse(const mouse* m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    ui.begin_widget(pos);
    vec2i scrpos = ui["messages_area"].screen_pos();
    mouse m_dialog = *m;
    m_dialog -= scrpos;
    if (panel->input_handle(&m_dialog)) {
        //button_message_handler();
        //button_delete_handler();
    }
    ui.end_widget();

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        _close_cb();
    }

    return result;
}

void ui::message_list_window::show(close_callback close_cb) {
    static window_type instance = {
        WINDOW_MESSAGE_LIST,
        [] (int flags) { g_message_list_window.draw_background(flags); },
        [] (int flags) { g_message_list_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_message_list_window.ui_handle_mouse(m); }
    };

    g_message_list_window._close_cb = close_cb;
    g_message_list_window.init();

    window_show(&instance);
}

void window_message_list_show(void) {
    ui::message_list_window::show(window_city_show);
}
