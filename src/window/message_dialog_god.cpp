#include "message_dialog_god.h"

#include "city/city_message.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "io/gamefiles/lang.h"
#include "core/string.h"
#include "game/game.h"
#include "game/gods.h"
#include "city/city_religion.h"
#include "dev/debug.h"


void ui::message_dialog_god::draw_foreground(UiFlags flags) {
    message_dialog_base::draw_foreground(flags);

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

        ctx.img_generic(img, vec2i{ image_x, image_y });
    }
}

void ui::message_dialog_god::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);

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
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    bstring1024 full_text;
    full_text.printf("%s @P%s", header.c_str(), text.c_str());

    ui["content_text"] = full_text;
}

declare_console_command_p(show_god_message) {
    const bstring128 god_str = args.next_str();
    const bstring128 message_id = args.next_str();

    if (god_str.empty() || message_id.empty()) {
        out.println("Usage: show_god_message <god_id> <message_id>");
        out.println("God IDs: 0=Osiris, 1=Ra, 2=Ptah, 3=Seth, 4=Bast");
        return;
    }

    int god_id = atoi(god_str.c_str());
    if (god_id < 0 || god_id >= MAX_GODS) {
        out.printf("Invalid god ID. Valid range: 0-%d\n", MAX_GODS - 1);
        return;
    }

    e_god god = (e_god)god_id;
    messages::god(god, message_id.c_str());
    out.printf("Showing message from god %d with message_id: %s\n", god_id, message_id);
}
