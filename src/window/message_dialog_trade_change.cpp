#include "message_dialog_trade_change.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_trade_change::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_trade_change::draw_foreground(UiFlags flags) {
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_trade_change::draw_city_message_text(const lang_message& msg) {
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
    int resource_image_id = this->resource_image(player_msg.param2);
    empire_city* city = g_empire.city(player_msg.param1);
    pcstr city_name = city ? lang_get_string(195, city->name_id) : "";
    full_text.printf("%s @P%s @P@I%d %s", header.c_str(), text.c_str(), resource_image_id, city_name);

    ui["content_text"] = full_text;
}

