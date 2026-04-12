#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UIElement_call(js_State *J) {
    js_typeerror(J, "UIElement is not callable");
}

static void jsB_UIElement_construct(js_State *J) {
    js_typeerror(J, "UIElement cannot be constructed");
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_get_noop, js_intern(""), 0);
    js_newcfunction(J, set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element);

void js_register_ui_element(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_text, ui::proxy_set_text, "text");
    def_accessor(J, ui::proxy_get_pos, ui::proxy_set_pos, "pos");
    def_accessor(J, ui::proxy_get_size, ui::proxy_set_size, "size");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");
    def_accessor(J, ui::proxy_get_font, ui::proxy_set_font, "font");
    def_accessor(J, ui::proxy_get_text_color, ui::proxy_set_text_color, "text_color");
    def_accessor(J, ui::proxy_get_noop, ui::proxy_set_image, "image");
    def_accessor(J, ui::proxy_get_selected, ui::proxy_set_selected, "selected");
    def_accessor(J, ui::proxy_get_noop, ui::proxy_set_tooltip, "tooltip");

    def_accessor(J, nullptr, ui::proxy_set_onclick, "onclick");
    def_accessor(J, nullptr, ui::proxy_set_ondraw, "ondraw");

    js_newcconstructor(J, jsB_UIElement_call, jsB_UIElement_construct, (js_StringNode)ui::element::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::element::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::element::skind(), proto);
}
