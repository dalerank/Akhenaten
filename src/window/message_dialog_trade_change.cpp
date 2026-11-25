#include "message_dialog_trade_change.h"

#include "empire/empire.h"
#include "game/localization.h"
#include "core/string.h"

void ui::message_dialog_trade_change::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    bstring1024 full_text;
    int resource_image_id = resource_image(player_msg.param2);
    empire_city* city = g_empire.city(player_msg.param1);
    pcstr city_name = city ? localization().get_string(195, city->name_id) : "";
    full_text.printf("%s @P%s @P@I%d %s", header.c_str(), text.c_str(), resource_image_id, city_name);

    ui["content_text"] = full_text;
}
