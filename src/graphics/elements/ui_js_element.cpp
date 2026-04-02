#include "ui_js.h"

#include "mujs/jsvalue.h"

static js_Object *g_ui_element_prototype = nullptr;

static void jsB_UIElement_call(js_State *J) {
    js_typeerror(J, "UIElement is not callable");
}

static void jsB_UIElement_construct(js_State *J) {
    js_typeerror(J, "UIElement cannot be constructed");
}

js_Object *js_ui_element_prototype() {
    return g_ui_element_prototype;
}

void js_register_ui_element(js_State *J) {
    g_ui_element_prototype = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_ui_element_prototype);
    js_newcconstructor(J, jsB_UIElement_call, jsB_UIElement_construct, "UIElement", 0);
    js_defglobal(J, "UIElement", JS_DONTENUM);
}
