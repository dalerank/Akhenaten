#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UIImage_call(js_State *J) {
    js_typeerror(J, "UIImage is not callable");
}

static void jsB_UIImage_construct(js_State *J) {
    js_typeerror(J, "UIImage cannot be constructed");
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_noop, js_intern(""), 0);
    js_newcfunction(J, set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_image);

void js_register_ui_element_image(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);

    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_pos, ui::proxy_set_pos, "pos");
    def_accessor(J, ui::proxy_get_screen_pos, ui::proxy_noop, "screen_pos");
    def_accessor(J, ui::proxy_get_size, ui::proxy_set_size, "size");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");
    def_accessor(J, ui::proxy_get_image_tid, ui::proxy_set_image_tid, "image");
    def_accessor(J, ui::proxy_noop, ui::proxy_set_tooltip, "tooltip");
    def_accessor(J, nullptr, ui::proxy_set_ondraw, "ondraw");

    js_newcconstructor(J, jsB_UIImage_call, jsB_UIImage_construct, (js_StringNode)ui::eimg::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::eimg::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::eimg::skind(), proto);
}
