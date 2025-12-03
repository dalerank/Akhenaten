#include "message_dialog_god.h"

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
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"
#include "game/gods.h"
#include "dev/debug.h"

#include <iostream>
#include <sstream>

int ui::message_dialog_god::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_god::draw_foreground(UiFlags flags) {
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_god::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);
    
    // Initialize god from city message
    if (message_id != -1) {
        const city_message& city_msg = city_message_get(message_id);
        if (city_msg.god != GOD_UNKNOWN) {
            god = (e_god)city_msg.god;
            background = true;
        }
    }
}

void ui::message_dialog_god::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    ui["content_text"] = msg.content.text;

    const image_t *img = nullptr;
    if (god != GOD_UNKNOWN) {
        int image_id = image_id_from_group(GROUP_PANEL_GODS_DIALOGDRAW) + 19 + god;
        img = image_get(image_id);
    } else if (background && background_img) {
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

    draw_foreground_image();
}

void ui::message_dialog_god::draw_city_message_text(const lang_message& msg) {
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
    full_text.printf("%s @P%s", header.c_str(), text.c_str());

    ui["content_text"] = full_text;
}

declare_console_command_p(show_god_message) {
    std::string god_str, message_id;
    is >> god_str >> message_id;
    
    if (god_str.empty() || message_id.empty()) {
        os << "Usage: show_god_message <god_id> <message_id>" << std::endl;
        os << "God IDs: 0=Osiris, 1=Ra, 2=Ptah, 3=Seth, 4=Bast" << std::endl;
        return;
    }
    
    int god_id = atoi(god_str.c_str());
    if (god_id < 0 || god_id >= MAX_GODS) {
        os << "Invalid god ID. Valid range: 0-" << (MAX_GODS - 1) << std::endl;
        return;
    }
    
    e_god god = (e_god)god_id;
    messages::god(god, message_id.c_str());
    os << "Showing message from god " << god_id << " with message_id: " << message_id << std::endl;
}

