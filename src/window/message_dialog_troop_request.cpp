#include "message_dialog_troop_request.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "city/military.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/text.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"
#include "scenario/distant_battle.h"
#include "empire/empire_city.h"
#include "empire/empire.h"

int ui::message_dialog_troop_request::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_troop_request::draw_foreground(UiFlags flags) {
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_troop_request::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);
    
    background_img = 0;
    background = false;
    
    if (message_id != -1) {
        const city_message& city_msg = city_message_get(message_id);
        if (city_msg.background_img) {
            background_img = city_msg.background_img;
            background = true;
        }
    }
}

void ui::message_dialog_troop_request::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    const image_t *img = nullptr;
    if (background_img) {
        int image_id = background_img;
        if (image_id == messages::IMAGE_FROM_SCHEME) {
            int16_t img_pack = msg.image.pack > 0 ? msg.image.pack : PACK_UNLOADED;
            img = image_get({ img_pack, msg.image.id, msg.image.offset });
        } else {
            img = image_get(image_id);
        }
    } else if (msg.image.id) {
        int image_id = get_message_image_id(msg);
        img = image_id ? image_get(image_id) : nullptr;
    }

    if (img) {
        int current_x = (500 - img->width) / 2;
        ctx.img_generic(img, vec2i{ current_x, 96 });
    }

    draw_content(msg);

    draw_foreground_image();
}

void ui::message_dialog_troop_request::draw_city_message_text(const lang_message& msg) {
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

    int months_until_battle = city_military_months_until_distant_battle();
    int enemy_strength = city_military_distant_battle_enemy_strength();
    int distant_city_id = city_military_distant_battle_city();
    
    bstring1024 full_text;
    
    if (months_until_battle > 0 && distant_city_id >= 0) {
        const empire_city* distant_city = g_empire.city(distant_city_id);
        xstring city_name = distant_city ? ui::str(21, distant_city->name_id) : xstring("Unknown City");
        
        int strength_text_id = 75; // "very strong"
        if (enemy_strength < 46) {
            strength_text_id = 73; // "weak"
        } else if (enemy_strength < 89) {
            strength_text_id = 74; // "strong"
        }
        
        full_text.printf("%s @P%s @P%s %s %s %s %d %s",
                         header.c_str(),
                         text.c_str(),
                         ui::str(52, 72), // "Distant battle at"
                         city_name.c_str(),
                         ui::str(52, strength_text_id), // enemy strength description
                         ui::str(8, 4), // "months"
                         months_until_battle,
                         ui::str(12, 1)); // period marker
    } else {
        // Standard message format
        full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, 1));
    }

    ui["content_text"] = full_text;
}

