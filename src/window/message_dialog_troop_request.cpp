#include "message_dialog_troop_request.h"

#include "city/city_message.h"
#include "city/military.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"
#include "scenario/distant_battle.h"
#include "empire/empire.h"

void ui::message_dialog_troop_request::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);

    if (message_id == -1) {
        return;
    }

    const city_message& city_msg = message_manager().get(message_id);
    image_desc img_desc;
    if (city_msg.background_img && city_msg.background_img == messages::IMAGE_FROM_SCHEME) {
        const lang_message &msg = lang_get_message(text_id);
        img_desc = { msg.image.pack, msg.image.id, msg.image.offset };
    } else {
        const image_t *img = image_get(city_msg.background_img);
        img_desc = img ? img->desc() : image_desc{};
    }
    ui["image"].image(img_desc);
}

void ui::message_dialog_troop_request::draw_background_content() {
    const lang_message& msg = lang_get_message(text_id);
    draw_content(msg);
}

void ui::message_dialog_troop_request::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    int months_until_battle = g_distant_battle.battle.months_until_battle;
    int enemy_strength = g_distant_battle.enemy_strength();
    int distant_city_id = g_distant_battle.battle.city;

    bstring1024 full_text;

    if (months_until_battle > 0 && distant_city_id >= 0) {
        const empire_city* distant_city = g_empire.city(distant_city_id);
        xstring city_name = distant_city ? ui::str(21, distant_city->name_id) : xstring("Unknown City");

        int strength_text_id = 75;
        if (enemy_strength < 46) {
            strength_text_id = 73;
        } else if (enemy_strength < 89) {
            strength_text_id = 74;
        }

        full_text.printf("%s @P%s @P%s %s %s %s %d %s",
                         header.c_str(),
                         text.c_str(),
                         ui::str(52, 72),
                         city_name.c_str(),
                         ui::str(52, strength_text_id),
                         ui::str(8, 4),
                         months_until_battle,
                         ui::str(12, 1));
    } else {
        full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, 1));
    }

    ui["content_text"] = full_text;
}
