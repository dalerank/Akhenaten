#include "debug_console.h"

#include "js/js_game.h"
#include "js/js_struct.h"
#include "mujs/mujs.h"
#include "graphics/elements/ui_js.h"
#include "game/game_events.h"

ANK_REGISTER_STRUCT_WRITER(event_draw_debug_properties, reserved);

static void __debug_props_show(js_State *J) {
    if (js_gettop(J) < 2) {
        return;
    }

    js_StringNode field_sn = js_tostring(J, 1);
    pcstr field = js_strnode_cstr(field_sn);
    if (!field || !*field) {
        return;
    }

    const int val_idx = 2;

    if (js_isboolean(J, val_idx)) {
        game_debug_show_property(field, js_toboolean(J, val_idx));
        return;
    }

    if (js_isnumber(J, val_idx) || js_iscnumber(J, val_idx)) {
        const double num = js_tonumber(J, val_idx);
        const int as_int = static_cast<int>(num);
        if (static_cast<double>(as_int) == num) {
            game_debug_show_property(field, as_int);
        } else {
            game_debug_show_property(field, static_cast<float>(num));
        }
        return;
    }

    if (js_isstring(J, val_idx)) {
        game_debug_show_property(field, js_strnode_cstr(js_tostring(J, val_idx)));
    }
}

void js_register_debug_props_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, __debug_props_show, "__debug_props_show", 2);
}

ANK_REGISTER_PROPS_ITERATOR(draw_debug_properties_handler);
void draw_debug_properties_handler(bool header) {
    if (header) {
        return;
    }

    ui::event(event_draw_debug_properties{});
}