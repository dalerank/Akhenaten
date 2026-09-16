#include "ui_js.h"

#include "graphics/image.h"
#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

#include <algorithm>

static void jsB_UIImageQueue_call(js_State *J) {
    js_typeerror(J, "UIImageQueue is not callable");
}

static void jsB_UIImageQueue_construct(js_State *J) {
    js_typeerror(J, "UIImageQueue cannot be constructed");
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    J->newcfunction(get ? get : ui::proxy_noop, js_intern(""), 0);
    J->newcfunction(set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

static void def_function(js_State *J, js_CFunction fn, const char *name, int nargs) {
    J->newcfunction(fn, js_intern(name), nargs);
    js_setproperty(J, -2, js_intern(name));
}

static void ui_proxy_img_queue_enqueue(js_State *J) {
    ui::element *elem = ui::GET_ELEM(J);
    auto *q = elem ? elem->dcast_img_queue() : nullptr;
    if (q) {
        const int id = (int)js_tonumber(J, 1);
        const image_t *img = image_get(id);
        if (img) {
            q->enqueue(img->desc());
        }
    }
    J->pushundefined();
}

static void ui_proxy_img_queue_clear(js_State *J) {
    ui::element *elem = ui::GET_ELEM(J);
    auto *q = elem ? elem->dcast_img_queue() : nullptr;
    if (q) {
        q->clear_queue();
    }
    J->pushundefined();
}

static void ui_proxy_get_fade_ms(js_State *J) {
    ui::element *elem = ui::GET_ELEM(J);
    auto *q = elem ? elem->dcast_img_queue() : nullptr;
    js_pushnumber(J, q ? q->fade_ms : 0);
}

static void ui_proxy_set_fade_ms(js_State *J) {
    ui::element *elem = ui::GET_ELEM(J);
    auto *q = elem ? elem->dcast_img_queue() : nullptr;
    if (q) {
        q->fade_ms = std::max(1, (int)js_tonumber(J, 1));
    }
    J->pushundefined();
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_image_queue);

void js_register_ui_element_image_queue(js_State *J) {
    js_Object *proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);

    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_pos, ui::proxy_set_pos, "pos");
    def_accessor(J, ui::proxy_get_screen_pos, ui::proxy_noop, "screen_pos");
    def_accessor(J, ui::proxy_get_size, ui::proxy_set_size, "size");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");

    def_accessor(J, ui::proxy_get_image_tid, ui::proxy_set_image_tid, "image");
    def_accessor(J, ui_proxy_get_fade_ms, ui_proxy_set_fade_ms, "fade_ms");
    def_accessor(J, ui::proxy_noop, ui::proxy_set_tooltip, "tooltip");
    def_accessor(J, nullptr, ui::proxy_set_ondraw, "ondraw");

    def_function(J, ui_proxy_img_queue_enqueue, "enqueue", 1);
    def_function(J, ui_proxy_img_queue_clear, "clear_queue", 0);

    J->newcconstructor(jsB_UIImageQueue_call, jsB_UIImageQueue_construct, (js_StringNode)ui::eimg_queue::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::eimg_queue::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::eimg_queue::skind(), proto);
}
