#include "message_dialog_price_change.h"

#include "io/gamefiles/lang.h"
#include "graphics/elements/lang_text.h"
#include "core/string.h"

void ui::message_dialog_price_change::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    bstring1024 full_text;
    int resource_image_id = resource_image(player_msg.param2);
    bstring64 money_str;
    money_str.printf("%d %s", player_msg.param1, localization().text_from_key("#top_menu_funds"));
    full_text.printf("%s @P%s @P@I%d %s", header.c_str(), text.c_str(), resource_image_id, money_str.c_str());

    ui["content_text"] = full_text;
}
