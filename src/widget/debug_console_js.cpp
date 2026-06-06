#include "debug_console.h"

#include "js/js_game.h"
#include "js/js_struct.h"
#include "mujs/mujs.h"
#include "mujs/jsvalue.h"
#include "core/xstring.h"
#include "grid/point.h"
#include "graphics/elements/ui_js.h"
#include "game/game_events.h"

ANK_REGISTER_STRUCT_WRITER(event_draw_debug_properties, reserved);

static bool try_show_cptr_property(js_State *J, pcstr display_name, int obj_idx, js_StringNode prop_name) {
    js_Value *v = js_tovalue(J, obj_idx);
    if (!v || v->type != JS_TOBJECT)
        return false;

    js_Object *obj = v->u.object;
    int own = 0;
    js_Property *prop = jsV_getpropertyx(J, obj, prop_name, &own);
    if (!prop || prop->value.type != JS_TOBJECT)
        return false;

    js_Object *pobj = prop->value.u.object;
    void *ptr = nullptr;
    js_CPtrType ptype = JS_PTR_INT;

    if (pobj->type == JS_CPTR) {
        ptr = pobj->u.p.ptr;
        ptype = pobj->u.p.ptype;
    } else if (pobj->type == JS_CPTROFF) {
        void *base = jsV_get_cobj_ptr(obj);
        if (!base)
            return false;
        ptr = (char *)base + pobj->u.poff.off;
        ptype = pobj->u.poff.ptype;
    } else {
        return false;
    }

    if (!ptr)
        return false;

    switch (ptype) {
    case JS_PTR_INT:    game_debug_show_property(display_name, *(int *)ptr);     break;
    case JS_PTR_BOOL:   game_debug_show_property(display_name, *(bool *)ptr);    break;
    case JS_PTR_FLOAT:  game_debug_show_property(display_name, *(float *)ptr);   break;
    case JS_PTR_INT8:   game_debug_show_property(display_name, *(int8_t *)ptr);  break;
    case JS_PTR_UINT8:  game_debug_show_property(display_name, *(uint8_t *)ptr); break;
    case JS_PTR_INT16:  game_debug_show_property(display_name, *(int16_t *)ptr); break;
    case JS_PTR_UINT16: game_debug_show_property(display_name, *(uint16_t *)ptr);break;
    case JS_PTR_XSTRING: game_debug_show_property(display_name, ((xstring *)ptr)->c_str()); break;
    }
    return true;
}

static void __debug_props_show(js_State *J) {
    const int argc = js_gettop(J);
    if (argc < 2) {
        return;
    }

    js_StringNode field_sn = js_tostring(J, 1);
    pcstr field = js_strnode_cstr(field_sn);
    if (!field || !*field) {
        return;
    }

    // 3-arg form: property_input("display_name", obj, "field_name")
    // Resolves the real C++ pointer via JS_CPTR / JS_CPTROFF binding.
    if (argc >= 3 && js_isstring(J, 3)) {
        js_StringNode prop_sn = js_tostring(J, 3);
        if (try_show_cptr_property(J, field, 2, prop_sn)) {
            return;
        }
    }

    // 2-arg fallback: property_input("display_name", value) — read-only display.
    const int val_idx = 2;

    if (J->isobject(val_idx) && !js_isarray(J, val_idx)) {
        js_Object *obj = J->toobject(val_idx);
        if (obj && obj->type == JS_CVEC2I) {
            const vec2i v{obj->u.vec2.x, obj->u.vec2.y};
            game_debug_show_property(field, v, /*disabled*/true);
            return;
        }
    }

    if (js_isboolean(J, val_idx)) {
        bool v = js_toboolean(J, val_idx);
        game_debug_show_property(field, v);
        return;
    }

    if (js_isnumber(J, val_idx) || js_iscnumber(J, val_idx)) {
        const double num = js_tonumber(J, val_idx);
        const int as_int = static_cast<int>(num);
        if (static_cast<double>(as_int) == num) {
            game_debug_show_property(field, as_int, /*disabled*/true);
        } else {
            game_debug_show_property(field, static_cast<float>(num), /*disabled*/true);
        }
        return;
    }

    if (js_isstring(J, val_idx)) {
        game_debug_show_property(field, js_strnode_cstr(js_tostring(J, val_idx)));
    }
}

void js_register_debug_props_functions(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, __debug_props_show, "__debug_props_show", 3);
}

ANK_REGISTER_PROPS_ITERATOR(draw_debug_properties_handler);
void draw_debug_properties_handler(bool header) {
    if (header) {
        return;
    }

    ui::event(event_draw_debug_properties{});
}