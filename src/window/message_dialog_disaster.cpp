#include "message_dialog_disaster.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/text.h"
#include "graphics/video.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "scenario/scenario.h"
#include "scenario/request.h"
#include "window/window_city.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_disaster::handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    const mouse *m_dialog = mouse_in_dialog(m);
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

    xstring text = msg.content.text;
    painter ctx = game.painter();

    if (is_eventmsg) {
        text = body_text;
    }

    if (!text) {
        return;
    }

    bstring1024 header;
    if (player_msg.param1) {
        if (this->text_id == MESSAGE_DIALOG_THEFT) {
            int amount_offset = (player_msg.param1 == 1 || player_msg.param1 == -1) ? 0 : 1;
            header.printf("%s %d %s %s %d %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name(),
                          player_msg.param1, ui::str(8, amount_offset));
        } else {
            header.printf("%s %d %s %s %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name(), ui::str(41, player_msg.param1));
        }
    } else {
        header.printf("%s %d %s %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name());
    }

    bstring1024 full_text;
    full_text.printf("%s @P%s", header.c_str(), text.c_str());

    ui["content_text"] = full_text;
}

void ui::message_dialog_disaster::draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_disaster::draw_city_message_text(const lang_message& msg) {
    // ???
}

void ui::message_dialog_disaster::draw_background_video() {
    // ???
}

void ui::message_dialog_disaster::draw_background_content() {
    // ???
}

void ui::message_dialog_disaster::button_go_to_problem() {
    cleanup();
    int grid_offset = player_msg.param2;

    if (grid_offset > 0 && grid_offset < 26244) {
        camera_go_to_mappoint(tile2i(grid_offset));
    }

    window_city_show();
}

