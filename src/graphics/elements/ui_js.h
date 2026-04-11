#pragma once

#include "core/core.h"
#include "core/profiler.h"
#include "core/typename.h"
#include "core/custom_span.hpp"
#include "graphics/elements/ui.h"
#include "js/js_struct.h"
#include "js/js_game.h"

struct js_Object;
struct js_State;

using UiElementProtoRegIterator = FuncLinkedList<void (*)(js_State *)>;

/** Link `void func(js_State *J)` into UI MuJS registration (same idea as ANK_REGISTER_PROPS_ITERATOR). */
#define ANK_REGISTER_UI_ELEMENT_PROTO(func) \
    void func(js_State *J); \
    namespace ui_js_config { inline int ANK_CONFIG_PULL_VAR_NAME(func) = 1; } \
    static UiElementProtoRegIterator ANK_CONFIG_CC1(ui_el_proto_reg_, __LINE__)(func)

void js_ui_register_element_proto(const xstring &kind, js_Object *proto);
js_Object *js_ui_element_proto_for_kind(const xstring &kind);

xstring js_toxstring(js_State* J, int idx);

namespace ui {
    void proxy_get_value(js_State* J);
    void proxy_set_value(js_State* J);

    element* GET_ELEM(js_State* J);

    void proxy_get_noop(js_State* J);
    void proxy_get_text(js_State* J);
    void proxy_set_text(js_State* J);
    void proxy_get_enabled(js_State* J);
    void proxy_set_enabled(js_State* J);
    void proxy_get_readonly(js_State* J);
    void proxy_set_readonly(js_State* J);
    void proxy_get_darkened(js_State* J);
    void proxy_set_darkened(js_State* J);
    void proxy_get_font(js_State* J);
    void proxy_set_font(js_State* J);
    void proxy_get_text_color(js_State* J);
    void proxy_set_text_color(js_State* J);
    void proxy_set_image(js_State* J);
    void proxy_get_image_tid(js_State* J);
    void proxy_set_image_tid(js_State* J);
    void proxy_get_selected(js_State* J);
    void proxy_set_selected(js_State* J);
    void proxy_set_tooltip(js_State* J);
    void proxy_set_onclick(js_State* J);
    void proxy_set_ondraw(js_State* J);
    void proxy_set_textfn(js_State* J);
    void proxy_set_checkedfn(js_State* J);

    struct widget;

    template <typename T>
    inline void widget::event(const T& ev, xstring evname_str) {
        OZZY_PROFILER_SECTION(_, evname_str.c_str());

        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        widget::event(evname_str, *js_j);
    }

    template <typename T>
    inline void widget::event(const T& ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        widget::event(ev, evname_str);
    }

    template <typename T, typename... ES>
    inline void widget::event(const T& ev, ES... es) {
        xstring evname_str = js_helpers::es_hash_str(es...).c_str();
        widget::event(ev, evname_str);
    }

    template <typename T>
    inline void event(const T& ev, xstring evname_str) {
        OZZY_PROFILER_SECTION(_, evname_str.c_str());

        bvariant_map::scoped js_j;
        js_helper::writer(*js_j, ev);
        js_call_event_handlers(evname_str, *js_j);
    }

    template <typename T, typename... ES>
    inline void event(const T& ev, ES... es) {
        xstring evname_str = js_helpers::es_hash_str(es...).c_str();
        ui::event(ev, evname_str);
    }

    template <typename T>
    inline void event(const T& ev) {
        type_name_holder<T> evname;
        xstring evname_str(type_simplified_name(evname.value.data()));
        ui::event(ev, evname_str);
    }
} // namespace ui
