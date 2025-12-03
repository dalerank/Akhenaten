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
    draw_foreground_normal();
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

void ui::message_dialog_imperial::draw_content(const lang_message &msg) {
    assert(msg.type == TYPE_MESSAGE);
    draw_city_message_text(msg);
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
    
    bstring1024 header;
    header.printf("%s %d %s %s", ui::str(25, player_msg.month), player_msg.year, ui::str(63, 5), city_player_name());

    const auto& city_msg = city_message_get(message_id);
    bstring1024 full_text;
    int resource_image_id = this->resource_image(city_msg.req_resource);
    full_text.printf("%s @P@P%s @P@P @I%d %d %s %s %d %s",
                     header.c_str(),
                     text.c_str(), 
                     resource_image_id, stack_proper_quantity(city_msg.req_amount, city_msg.req_resource), ui::str(23, city_msg.req_resource),
                     ui::str(8, 4), city_msg.req_months_left, ui::str(12, 2));

    ui["content_text"] = full_text;
}

void ui::message_dialog_imperial::draw_background_image() {
    // ???
}

void ui::message_dialog_imperial::draw_background_video() {
    // ???
}

