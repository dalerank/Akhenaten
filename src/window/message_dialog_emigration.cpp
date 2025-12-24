#include "message_dialog_emigration.h"

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
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_emigration::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_emigration::draw_foreground(UiFlags flags) {
    draw_foreground_content();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_emigration::draw_city_message_text(const lang_message& msg) {
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
    int city_sentiment = g_city.sentiment.low_mood_cause;
    if (city_sentiment >= 1 && city_sentiment <= 5) {
        full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, city_sentiment + 2));
    } else {
        full_text.printf("%s @P%s", header.c_str(), text.c_str());
    }

    ui["content_text"] = full_text;
}

