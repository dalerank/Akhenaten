#include "ui_js.h"

#include "mujs/mujs.h"
#include "mujs/jsvalue.h"

static void jsB_UIScrollableList_call(js_State *J) {
    js_typeerror(J, "UIScrollableList is not callable");
}

static void jsB_UIScrollableList_construct(js_State *J) {
    js_typeerror(J, "UIScrollableList cannot be constructed");
}

void ui_proxy_get_selected_text(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    const int syntax = js_tointeger(J, 1);
    auto* list = elem ? elem->dcast_scrollable_list() : nullptr;
    const xstring text = list ? list->selected_entry_text(syntax) : xstring();
    J->pushstring(text.c_str());
}

static void ui_proxy_scroll_to_selected(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            list->scroll_to_selected();
        }
    }
    J->pushundefined();
}

static void ui_proxy_add_item(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            uintptr_t user_data = 0;
            if (js_gettop(J) >= 2 && !js_isundefined(J, 2)) {
                user_data = (uintptr_t)js_tointeger(J, 2);
            }
            list->add_item(js_toxstring(J, 1).c_str(), user_data);
        }
    }
    J->pushundefined();
}

static void ui_proxy_clear(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->clear();
    }
    J->pushundefined();
}

static void ui_proxy_select_item(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto list = elem ? elem->dcast_scrollable_list() : nullptr;
    if (list) {
        list->select_item(js_toxstring(J, 1).c_str());
    }
    J->pushundefined();
}

static void ui_proxy_select_entry(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->select_entry(js_tointeger(J, 1));
    }
    J->pushundefined();
}


static void ui_proxy_refresh_file_finder(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->refresh_file_finder();
    }
    J->pushundefined();
}

static void ui_proxy_change_file_path(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            xstring d = js_toxstring(J, 1);
            xstring e = js_toxstring(J, 2);
            list->change_file_path(d, e);
        }
    }
    J->pushundefined();
}

static void ui_proxy_append_files_with_extension(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            xstring d = js_toxstring(J, 1);
            xstring e = js_toxstring(J, 2);
            list->append_files_with_extension(d.c_str(), e.c_str());
        }
    }
    J->pushundefined();
}

void ui_proxy_get_items_count(js_State* J) {
    ui::element* elem = ui::GET_ELEM(J);
    auto* list = elem ? elem->dcast_scrollable_list() : nullptr;
    int items_count = list ? list->items_count() : 0;
    js_pushnumber(J, items_count);
}

static void def_accessor(js_State *J, js_CFunction get, js_CFunction set, const char *name) {
    js_newcfunction(J, get ? get : ui::proxy_noop, js_intern(""), 0);
    js_newcfunction(J, set, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

static void def_function(js_State *J, js_CFunction fn, const char *name, int nargs) {
    js_newcfunction(J, fn, js_intern(name), nargs);
    js_setproperty(J, -2, js_intern(name));
}

ANK_REGISTER_UI_ELEMENT_PROTO(js_register_ui_element_scrollable_list);

void js_register_ui_element_scrollable_list(js_State *J) {
    js_Object* proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, proto);
    def_accessor(J, ui::proxy_get_text, ui::proxy_set_text, "text");
    def_accessor(J, ui::proxy_get_pos, ui::proxy_set_pos, "pos");
    def_accessor(J, ui::proxy_get_screen_pos, ui::proxy_noop, "screen_pos");
    def_accessor(J, ui::proxy_get_size, ui::proxy_set_size, "size");
    def_accessor(J, ui::proxy_get_enabled, ui::proxy_set_enabled, "enabled");
    def_accessor(J, ui::proxy_get_readonly, ui::proxy_set_readonly, "readonly");
    def_accessor(J, ui::proxy_get_font, ui::proxy_set_font, "font");
    def_accessor(J, ui::proxy_get_text_color, ui::proxy_set_text_color, "text_color");
    def_accessor(J, ui::proxy_get_selected, ui::proxy_set_selected, "selected");
    def_accessor(J, ui::proxy_noop, ui::proxy_set_tooltip, "tooltip");
    def_accessor(J, ui_proxy_get_items_count, nullptr, "items_count");

    def_function(J, ui_proxy_add_item, "add_item", 1);
    def_function(J, ui_proxy_clear, "clear", 0);
    def_function(J, ui_proxy_select_item, "select_item", 1);
    def_function(J, ui_proxy_select_entry, "select_index", 1);
    def_function(J, ui_proxy_refresh_file_finder, "refresh_file_finder", 0);
    def_function(J, ui_proxy_change_file_path, "change_file_path", 2);
    def_function(J, ui_proxy_append_files_with_extension, "append_files_with_extension", 2);
    def_function(J, ui_proxy_scroll_to_selected, "scroll_to_selected", 0);
    def_function(J, ui_proxy_get_selected_text, "selected_text", 1);

    js_newcconstructor(J, jsB_UIScrollableList_call, jsB_UIScrollableList_construct, (js_StringNode)ui::escrollable_list::skind()._get(), 0);
    js_defglobal(J, (js_StringNode)ui::escrollable_list::skind()._get(), JS_DONTENUM);

    js_ui_register_element_proto(ui::escrollable_list::skind(), proto);
}
