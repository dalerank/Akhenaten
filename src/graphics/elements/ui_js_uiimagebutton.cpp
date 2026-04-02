#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UIImageButton_call(js_State *J) {
    js_typeerror(J, "UIImageButton is not callable");
}

static void jsB_UIImageButton_construct(js_State *J) {
    js_typeerror(J, "UIImageButton cannot be constructed");
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_get_noop, "", 0);
    js_newcfunction(J, set, "", 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_image_button);
void js_register_ui_element_image_button(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);

    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_text, ui::proxy_set_text, "text");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");
    def_accessor(J, ui::proxy_get_font, ui::proxy_set_font, "font");
    def_accessor(J, ui::proxy_get_text_color, ui::proxy_set_text_color, "text_color");
    def_accessor(J, ui::proxy_get_image_tid, ui::proxy_set_image_tid, "image");
    def_accessor(J, ui::proxy_get_selected, ui::proxy_set_selected, "selected");
    def_accessor(J, ui::proxy_get_noop, ui::proxy_set_tooltip, "tooltip");

    def_accessor(J, nullptr, ui::proxy_set_onclick, "onclick");
    def_accessor(J, nullptr, ui::proxy_set_textfn, "textfn");
    def_accessor(J, nullptr, ui::proxy_set_ondraw, "ondraw");

    js_newcconstructor(J, jsB_UIImageButton_call, jsB_UIImageButton_construct, ui::eimage_button::skind().c_str(), 0);
    js_defglobal(J, ui::eimage_button::skind().c_str(), JS_DONTENUM);

    js_ui_register_element_proto(ui::eimage_button::skind(), proto);
}
