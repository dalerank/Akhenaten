#include "message_dialog_image.h"

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

int ui::message_dialog_image::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_image::draw_foreground(UiFlags flags) {
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_image::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);
    
    // Initialize background image from city message
    if (message_id != -1) {
        const city_message& city_msg = city_message_get(message_id);
        if (city_msg.background_img) {
            background_img = city_msg.background_img;
            background = true;
        }
    }
}

void ui::message_dialog_image::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    ui["content_text"] = msg.content.text;

    const image_t *img = nullptr;
    if (background_img) {
        int image_id = background_img;
        if (image_id == messages::IMAGE_FROM_SCHEME) {
            int16_t img_pack = msg.image.pack > 0 ? msg.image.pack : PACK_UNLOADED;
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

