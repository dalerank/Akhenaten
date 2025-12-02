#include "message_dialog_imperial.h"

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
#include "graphics/video.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "scenario/scenario.h"
#include "scenario/request.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_imperial::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_imperial::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}

void ui::message_dialog_imperial::draw_city_message_text(const lang_message& msg) {
    xstring text = msg.content.text;
    painter ctx = game.painter();
 
    if (is_eventmsg) {
        text = body_text;
    }
    
    if (!text) {
        return;
    }
    
    int width = lang_text_draw(25, player_msg.month, x_text + 10, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(player_msg.year, x_text + 12 + width, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw(63, 5, x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK);
    text_draw(city_player_name(), x_text + width + 60, y_text + 6, FONT_NORMAL_WHITE_ON_DARK, 0);

    int lines = rich_text.draw(text, vec2i(x_text + 8, y_text + 56), 16 * text_width_blocks - 16, text_height_blocks - 1, 0);
    const auto& city_msg = city_message_get(message_id);
    int y_offset = y_text + 86 + lines * 16;
    ctx.img_generic(resource_image(city_msg.req_resource), vec2i{x_text + 8, y_offset - 4});
    int width2 = text_draw_number(stack_proper_quantity(city_msg.req_amount, city_msg.req_resource), '@', " ", x_text + 28, y_offset, FONT_NORMAL_WHITE_ON_DARK);
    lang_text_draw(23, city_msg.req_resource, x_text + 26 + width2, y_offset, FONT_NORMAL_WHITE_ON_DARK);
    width2 = lang_text_draw_amount(8, 4, city_msg.req_months_left, x_text + 200, y_offset, FONT_NORMAL_WHITE_ON_DARK);
    lang_text_draw(12, 2, x_text + 200 + width2, y_offset, FONT_NORMAL_WHITE_ON_DARK);
}

void ui::message_dialog_imperial::draw_background_image() {
    painter ctx = game.painter();
    const lang_message& msg = lang_get_message(text_id);
    pos = { 32, 28 };

    int small_font = 0;
    int lines_available = 3; // Imperial messages use 3 lines

    rich_text.set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text.clear_links();
    int lines_required = rich_text.draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    if (lines_required > lines_available) {
        small_font = 1;
        rich_text.set_fonts(FONT_SMALL_PLAIN, FONT_SMALL_PLAIN);
        lines_required = rich_text.draw(msg.content.text, vec2i(0, 0), 384, lines_available, 1);
    }

    outer_panel_draw(pos, 26, 28);
    graphics_draw_rect(pos + vec2i{7, 7}, vec2i{402, 294}, COLOR_BLACK);

    int y_base = pos.y + 308;
    int inner_height_blocks = 6;
    if (lines_required > lines_available) {
        // create space to cram an extra line into the dialog
        y_base = y_base - 8;
        inner_height_blocks += 1;
    }
    inner_panel_draw({ pos.x + 8, y_base }, { 25, inner_height_blocks });
    text_draw_centered(msg.title.text, pos.x + 8, pos.y + 414, 400, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    int width = lang_text_draw(25, player_msg.month, pos.x + 16, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw_year(player_msg.year, pos.x + 18 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    width += lang_text_draw(63, 5, pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK);
    text_draw(city_player_name(), pos.x + 70 + width, y_base + 4, FONT_NORMAL_WHITE_ON_DARK, 0);

    text_height_blocks = msg.size.y - 1 - (32 + y_text - pos.y) / 16;
    text_width_blocks = msg.size.x - 4;
    if (small_font) {
        // Draw in black and then white to create shadow effect
        rich_text.draw_colored(msg.content.text, vec2i(pos.x + 16 + 1, y_base + 24 + 1), 384, text_height_blocks - 1, COLOR_BLACK);
        rich_text.draw_colored(msg.content.text, vec2i(pos.x + 16, y_base + 24), 384, text_height_blocks - 1, COLOR_WHITE);
    } else {
        rich_text.draw(msg.content.text, vec2i(pos.x + 16, y_base + 24), 384, text_height_blocks - 1, 0);
    }

    // Draw imperial request information
    assert(msg.message_type == MESSAGE_TYPE_IMPERIAL);
    int y_text = pos.y + 384;
    if (lines_required > lines_available)
        y_text += 8;

    scenario_request request = scenario_request_get_visible(player_msg.param1);
    if (request.is_valid()) {
        text_draw_number(request.amount, '@', " ", pos.x + 8, y_text, FONT_NORMAL_WHITE_ON_DARK);
        ctx.img_generic(image_id_resource_icon(request.resource) + resource_image_offset(request.resource, RESOURCE_IMAGE_ICON), vec2i{pos.x + 70, y_text - 5});
        lang_text_draw(23, request.resource, pos.x + 100, y_text, FONT_NORMAL_WHITE_ON_DARK);
        if (request.state <= e_event_state_overdue) {
            width = lang_text_draw_amount(8, 4, request.months_to_comply, pos.x + 200, y_text, FONT_NORMAL_WHITE_ON_DARK);
            lang_text_draw(12, 2, pos.x + 200 + width, y_text, FONT_NORMAL_WHITE_ON_DARK);
        }
    }

    const image_t *img = nullptr;
    if (god != GOD_UNKNOWN) {
        int image_id = image_id_from_group(GROUP_PANEL_GODS_DIALOGDRAW) + 19 + god;
        img = image_get(image_id);
    } else if (background) {
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

void ui::message_dialog_imperial::draw_background_video() {
    // ???
}

