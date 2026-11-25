#include "message_dialog_invasion.h"

#include "figure/formation.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "game/localization.h"
#include "window/window_city.h"
#include "window/autoconfig_window.h"
#include "core/string.h"
#include "scenario/invasion_auto_resolve.h"

void ui::message_dialog_invasion::init_data(xstring text_id, int message_id, void (*background_callback)(void)) {
    message_dialog_base::init_data(text_id, message_id, background_callback);

    const lang_message& msg = localization().message(text_id);
    assert(msg.message_type == MESSAGE_TYPE_INVASION);
    ui["button_go_to_problem"].enabled = true;
    ui["button_go_to_problem"].onclick([this] { button_go_to_problem(); });
}

void ui::message_dialog_invasion::draw_city_message_text(const lang_message& msg) {
    xstring text = resolve_message_body(msg);
    if (!text) {
        return;
    }

    bstring1024 header;
    format_city_message_header(header);

    bstring1024 full_text;
    full_text.printf("%s @P%s @P%s", header.c_str(), text.c_str(), ui::str(12, 1));

    ui["content_text"] = full_text;
}

void ui::message_dialog_invasion::button_go_to_problem() {
    cleanup();
    int grid_offset = player_msg.param2;
    int invasion_grid_offset = formation_grid_offset_for_invasion(player_msg.param1);
    if (invasion_grid_offset > 0)
        grid_offset = invasion_grid_offset;

    if (grid_offset > 0 && grid_offset < 26244) {
        g_camera.go_to_mappoint(tile2i(grid_offset));
    }

    window_city_show();

    if (g_invasion_auto_resolve.is_seq_frozen((uint16_t)player_msg.param1)) {
        autoconfig_window::show("invasion_quick_battle_window");
    }
}
