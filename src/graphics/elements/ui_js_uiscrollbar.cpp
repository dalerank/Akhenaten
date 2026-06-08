#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UIScrollbar_call(js_State *J) {
    js_typeerror(J, "UIScrollbar is not callable");
}

static void jsB_UIScrollbar_construct(js_State *J) {
    js_typeerror(J, "UIScrollbar cannot be constructed");
}

static void ui_proxy_get_scrollbar_value(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto* sb = elem ? elem->dcast_escrollbar() : nullptr;
    js_pushnumber(J, sb ? sb->value() : 0);
}

static void ui_proxy_set_scrollbar_value(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto* sb = elem ? elem->dcast_escrollbar() : nullptr;
    if (sb) {
        sb->scrollbar.scroll_position = js_tointeger(J, 1);
    }
    J->pushundefined();
}

static void ui_proxy_get_scrollbar_max_value(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto* sb = elem ? elem->dcast_escrollbar() : nullptr;
    js_pushnumber(J, sb ? sb->scrollbar.max_scroll_position : 0);
}

static void ui_proxy_set_scrollbar_max_value(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto* sb = elem ? elem->dcast_escrollbar() : nullptr;
    if (sb) {
        sb->max_value(js_tointeger(J, 1));
    }
    J->pushundefined();
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_noop, js_intern(""), 0);
    js_newcfunction(J, set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_scrollbar);

void js_register_ui_element_scrollbar(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_pos, ui::proxy_set_pos, "pos");
    def_accessor(J, ui::proxy_get_screen_pos, ui::proxy_noop, "screen_pos");
    def_accessor(J, ui::proxy_get_size, ui::proxy_set_size, "size");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui_proxy_get_scrollbar_value, ui_proxy_set_scrollbar_value, "value");
    def_accessor(J, ui_proxy_get_scrollbar_max_value, ui_proxy_set_scrollbar_max_value, "max_value");

    js_newcconstructor(J, jsB_UIScrollbar_call, jsB_UIScrollbar_construct, (js_StringNode)ui::escrollbar::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::escrollbar::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::escrollbar::skind(), proto);
}
