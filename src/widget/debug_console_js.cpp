#include "debug_console.h"

#include "js/js_game.h"
#include "mujs/mujs.h"

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

void register_debug_props_show(js_State *J) {
    js_getglobal(J, "__debug_props_show");
    const bool exists = J->iscallable(-1);
    js_pop(J, 1);
    if (!exists) {
        REGISTER_GLOBAL_FUNCTION(J, __debug_props_show, "__debug_props_show", 2);
    }
}

ANK_DECLARE_JSFUNCTION_ITERATOR(register_debug_props_show)
