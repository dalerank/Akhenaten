#include "message_dialog_invasion.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "figure/formation.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/rich_text.h"
#include "graphics/text.h"
#include "graphics/video.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "window/window_city.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_invasion::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_invasion::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    if (show_video) {
        draw_foreground_video();
        // Enable go_to_problem button for invasions in video mode
        const lang_message& msg = lang_get_message(text_id);
        assert(msg.message_type == MESSAGE_TYPE_INVASION);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 48, pos.y + 407};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    } else if (background) {
        draw_foreground_image();
        // Enable go_to_problem button for invasions in image mode
        const lang_message& msg = lang_get_message(text_id);
        assert(msg.message_type == MESSAGE_TYPE_INVASION);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 48, pos.y + 407};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    } else {
        draw_foreground_normal();
        
        // Enable go_to_problem button for invasions in normal mode
        const lang_message& msg = lang_get_message(text_id);
        assert(msg.message_type == MESSAGE_TYPE_INVASION);
        ui["button_go_to_problem"].enabled = true;
        ui["button_go_to_problem"].pos = {pos.x + 64, y_text + 36};
        ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    }
    
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}

void ui::message_dialog_invasion::draw_city_message_text(const lang_message& msg) {
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
    width += lang_text_draw(63, 5, x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    text_draw(city_player_name(), x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK, 0);

    lang_text_draw(12, 1, pos.x + 100, y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
    ui["content_text"] = text;
}

void ui::message_dialog_invasion::button_go_to_problem() {
    cleanup();
    int grid_offset = player_msg.param2;
    int invasion_grid_offset = formation_grid_offset_for_invasion(player_msg.param1);
    if (invasion_grid_offset > 0)
        grid_offset = invasion_grid_offset;

    if (grid_offset > 0 && grid_offset < 26244) {
        camera_go_to_mappoint(tile2i(grid_offset));
    }

    window_city_show();
}

