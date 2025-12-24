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
    draw_foreground_content();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();

    painter ctx = game.painter();
    const lang_message &msg = lang_get_message(text_id);

    draw_city_message_text(msg);

    assert(god != GOD_UNKNOWN);

    const xstring god_name = e_god_short_tokens.name((e_god_short)god);
    const uint16_t imgid = god_images[god_name].first_img();
    const image_t *img = image_get(imgid);

    if (img) {
        vec2i area_pos = ui["god_image_area"].pos;
        vec2i area_size = ui["god_image_area"].pxsize();

        vec2i area_abs_pos = pos + area_pos;
        int image_x = area_abs_pos.x + (area_size.x - img->width) / 2;
        int image_y = area_abs_pos.y + (area_size.y - img->height) / 2;

        int frame_base = image_id_from_group(GROUP_PANEL_GODS_DIALOGDRAW);

        int frame_padding_x = 20;
        int frame_padding_y = 20;
        int frame_width = img->width + frame_padding_x * 2;
        int frame_height = img->height + frame_padding_y * 2;
        int frame_x = image_x - frame_padding_x;
        int frame_y = image_y - frame_padding_y;

        ctx.img_generic(img, vec2i{ image_x, image_y });
    }
}

void ui::message_dialog_god::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);
    
    // Initialize god from city message
    if (message_id != -1) {
        const city_message& city_msg = city_message_get(message_id);
        if (city_msg.god != GOD_UNKNOWN) {
            god = (e_god)city_msg.god;
        }
    }
}

void ui::message_dialog_god::archive_load(archive arch) {
    message_dialog_base::archive_load(arch);

    arch.r("god_images", god_images);
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

