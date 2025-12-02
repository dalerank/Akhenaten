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
        vec2i btn_pos = { pos.x + 64, y_text + 36 };
        if (m_dialog->left.went_down &&
            m_dialog->x >= btn_pos.x && m_dialog->x < btn_pos.x + 27 &&
            m_dialog->y >= btn_pos.y && m_dialog->y < btn_pos.y + 27) {
            button_go_to_problem();
            return true;
        }
    }

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

void ui::message_dialog_disaster::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    const lang_message& msg = lang_get_message(text_id);
    
    if (show_video) {
        draw_foreground_video();
        // Enable go_to_problem button for disasters in video mode
        assert(msg.message_type == MESSAGE_TYPE_DISASTER);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 48, pos.y + 407};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    } else if (background) {
        draw_foreground_image();
        // Enable go_to_problem button for disasters in image mode
        assert(msg.message_type == MESSAGE_TYPE_DISASTER);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 48, pos.y + 407};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    } else {
        draw_foreground_normal();
        // Enable go_to_problem button for disasters in normal mode
        assert(msg.message_type == MESSAGE_TYPE_DISASTER);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 64, y_text + 36};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    }
    
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}

void ui::message_dialog_disaster::draw_city_message_text(const lang_message& msg) {
    xstring text = msg.content.text;
    painter ctx = game.painter();
 
    if (is_eventmsg) {
        text = body_text;
    }
    
    if (!text) {
        return;
    }
    
    int width = lang_text_draw(25, player_msg.month, x_text + 10, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(player_msg.year, x_text + 12 + width, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    if (player_msg.param1) {
        if (text_id == MESSAGE_DIALOG_THEFT) {
            lang_text_draw_amount(8, 0, player_msg.param1, pos.x + 240, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
        } else {
            lang_text_draw(41, player_msg.param1, pos.x + 240, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
        }
    } else {
        width += lang_text_draw(63, 5, x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
        text_draw(city_player_name(), x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK, 0);
    }

    lang_text_draw(12, 1, pos.x + 100, y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
    ui["content_text"] = text;
}

void ui::message_dialog_disaster::draw_background_image() {
    // ???
}

void ui::message_dialog_disaster::draw_background_video() {
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

