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
    rich_text.draw(text.c_str(), vec2i(x_text + 8, y_text + 86), 16 * text_width_blocks, text_height_blocks - 1, 0);
}

void ui::message_dialog_disaster::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    int small_font = 0;
    int lines_available = 4;
    if (msg.type == TYPE_MESSAGE) {
        lines_available = 3;
    }

    rich_text.set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text.clear_links();
    int lines_required = rich_text.draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    if (lines_required > lines_available) {
        small_font = 1;
        rich_text.set_fonts(FONT_SMALL_PLAIN, FONT_SMALL_PLAIN);
        lines_required = rich_text.draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    }

    outer_panel_draw(pos, 26, 28);
    graphics_draw_rect(pos + vec2i{7, 7}, vec2i{402, 294}, COLOR_BLACK);

    int y_base = pos.y + 308;
    int inner_height_blocks = 6;
    if (lines_required > lines_available) {
        // create space to cram an extra line into the dialog
        y_base = y_base - 8;
        inner_height_blocks += 1;
    }
    inner_panel_draw({ pos.x + 8, y_base }, { 25, inner_height_blocks });
    text_draw_centered(msg.title.text, pos.x + 8, pos.y + 414, 400, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    int width = lang_text_draw(25, player_msg.month, pos.x + 16, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(player_msg.year, pos.x + 18 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);

    if (msg.type == TYPE_MESSAGE && msg.message_type == MESSAGE_TYPE_DISASTER && text_id == MESSAGE_DIALOG_THEFT) {
        lang_text_draw_amount(8, 0, player_msg.param1, pos.x + 90 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        width += lang_text_draw(63, 5, pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
        text_draw(city_player_name(), pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK, 0);
    }

    text_height_blocks = msg.size.y - 1 - (32 + y_text - pos.y) / 16;
    text_width_blocks = msg.size.x - 4;
    if (small_font) {
        // Draw in black and then white to create shadow effect
        rich_text.draw_colored(msg.content.text, vec2i(pos.x + 16 + 1, y_base + 24 + 1), 384, text_height_blocks - 1, COLOR_BLACK);
        rich_text.draw_colored(msg.content.text, vec2i(pos.x + 16, y_base + 24), 384, text_height_blocks - 1, COLOR_WHITE);
    } else {
        rich_text.draw(msg.content.text, vec2i(pos.x + 16, y_base + 24), 384, text_height_blocks - 1, 0);
    }

    assert(msg.message_type == MESSAGE_TYPE_DISASTER);

    const image_t *img = nullptr;
    assert(god == GOD_UNKNOWN);

    if (background) {
        int image_id = background_img;
        if (image_id == messages::IMAGE_FROM_SCHEME) {
            int img_pack = msg.image.pack > 0 ? msg.image.pack : PACK_UNLOADED;
            img = image_get({ img_pack, msg.image.id, msg.image.offset });
        } else {
            img = image_get(image_id);
        }
    } 

    if (img) {
        int current_x = (500 - img->width) / 2;
        ctx.img_generic(img, vec2i{ current_x, 96 });
    }

    // Enable go_to_problem button for disasters in image mode
    assert(msg.message_type == MESSAGE_TYPE_DISASTER);
    ui["button_go_to_problem"].enabled = true;
    ui["button_go_to_problem"].pos = {pos.x + 48, pos.y + 407};
    ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    
    draw_foreground_image();
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

