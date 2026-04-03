#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UITextInput_call(js_State *J) {
    js_typeerror(J, "UITextInput is not callable");
}

static void jsB_UITextInput_construct(js_State *J) {
    js_typeerror(J, "UITextInput cannot be constructed");
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_get_noop, js_intern(""), 0);
    js_newcfunction(J, set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_input);

void js_register_ui_element_input(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_value, ui::proxy_set_value, "value");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");

    js_newcconstructor(J, jsB_UITextInput_call, jsB_UITextInput_construct, (js_StringNode)ui::einput::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::einput::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::einput::skind(), proto);
}
