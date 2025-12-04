#include "message_dialog_tutorial.h"

#include "city/city_message.h"
#include "city/city.h"
#include "city/constants.h"
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

int ui::message_dialog_tutorial::handle_mouse(const mouse *m) {
    return ui_handle_mouse(m);
}

void ui::message_dialog_tutorial::draw_foreground(UiFlags flags) {
    graphics_set_to_dialog();
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
    graphics_reset_dialog();
}

void ui::message_dialog_tutorial::draw_city_message_text(const lang_message& msg) {
    xstring text = msg.content.text;
    if (is_eventmsg) {
        text = body_text;
    }
    if (!text) {
        return;
    }
    ui["content_text"] = text;
}

