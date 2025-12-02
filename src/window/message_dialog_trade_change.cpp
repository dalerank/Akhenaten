#include "message_dialog_trade_change.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/rich_text.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "message_dialog.h"
#include "core/string.h"
#include "game/game.h"

int ui::message_dialog_trade_change::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_trade_change::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}

void ui::message_dialog_trade_change::draw_city_message_text(const lang_message& msg) {
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

    ctx.img_generic(resource_image(player_msg.param2), { pos.x + 64, y_text + 40 });
    lang_text_draw(21, g_empire.city(player_msg.param1)->name_id, pos.x + 100, y_text + 44, FONT_NORMAL_WHITE_ON_DARK);
    rich_text.draw(text, vec2i(x_text + 8, y_text + 86), 16 * text_width_blocks - 16, text_height_blocks - 1, 0);
}

