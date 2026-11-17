#include "message_dialog_disaster.h"

#include "city/city.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "core/string.h"
#include "message_dialog.h"

int ui::message_dialog_disaster::handle_mouse(const mouse *m) {
    const hotkeys* h = &g_hotkeys;
    const mouse* m_dialog = m->in_dialog();
    const lang_message &msg = lang_get_message(text_id);

    bool handled = handle_input_normal(m_dialog, msg);

    assert(msg.message_type == MESSAGE_TYPE_DISASTER);
    if (!handled) {
        ui.begin_widget(pos);
        handled = ui::handle_mouse(m) != 0;
        ui.end_widget();
    }

    if (!handled && input_go_back_requested(m, h)) {
        button_close();
        return 1;
    }

    return handled ? 1 : 0;
}

void ui::message_dialog_disaster::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);

    const lang_message &msg = lang_get_message(text_id);

    draw_foreground_content();
    assert(msg.message_type == MESSAGE_TYPE_DISASTER);
    ui["button_go_to_problem"].enabled = true;
    ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });

    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    if (player_msg.param1) {
        if (this->text_id == MESSAGE_DIALOG_THEFT) {
            int amount_offset = (player_msg.param1 == 1 || player_msg.param1 == -1) ? 0 : 1;
            header.printf("%s %d %s %s %d %s", lang_text_month(player_msg.month), player_msg.year, ui::str(63, 5), city_player_name(),
                          player_msg.param1, ui::str(8, amount_offset));
        } else {
            header.printf("%s %d %s %s %s", lang_text_month(player_msg.month), player_msg.year, ui::str(63, 5), city_player_name(), ui::str(41, player_msg.param1));
        }
    } else {
        format_city_message_header(header);
    }

    bstring1024 full_text;
    full_text.printf("%s @P%s", header.c_str(), text.c_str());

    ui["content_text"] = full_text;
    if (show_video) {
        ui["bottom_text"] = full_text.c_str();
    }
}

void ui::message_dialog_disaster::draw_city_message_text(const lang_message& msg) {
}

void ui::message_dialog_disaster::draw_background_content() {
}

void ui::message_dialog_disaster::button_go_to_problem() {
    cleanup();
    int grid_offset = player_msg.param2;

    if (grid_offset > 0 && grid_offset < 26244) {
        g_camera.go_to_mappoint(tile2i(grid_offset));
    }

    window_city_show();
}
