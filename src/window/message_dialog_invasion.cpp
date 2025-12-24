#include "message_dialog_invasion.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "figure/formation.h"
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
#include "window/window_city.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_invasion::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_invasion::init() {
    message_dialog_base::init();
}

void ui::message_dialog_invasion::draw_foreground(UiFlags flags) {
    draw_foreground_content();
        
    // Enable go_to_problem button for invasions in normal mode
    const lang_message& msg = lang_get_message(text_id);
    assert(msg.message_type == MESSAGE_TYPE_INVASION);
    ui["button_go_to_problem"].enabled = true;
    //ui["button_go_to_problem"].pos = {pos.x + 64, y_text + 36};
    ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
    
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
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
    
    bstring1024 header;
    header.printf("%s %d %s %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name());

    bstring1024 full_text;
    full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, 1));

    ui["content_text"] = full_text;
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

