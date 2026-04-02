#include "js/js.h"

#include "ui.h"
#include "js/js_game.h"
#include "graphics/elements/ui_js.h"
#include "mujs/jsi.h"
#include "mujs/jsvalue.h"
#include "widget/widget_sidebar.h"
#include "graphics/elements/generic_button.h"
#include "graphics/window.h"
#include "window/window_city.h"
#include "window/editor/window_editor.h"
#include "window/window_build_menu.h"
#include "window/message_dialog_new.h"
#include "window/window_advisors.h"
#include "window/window_labor_priority.h"
#include "window/resource_settings.h"
#include "window/trade_opened.h"
#include "window/autoconfig_window.h"
#include "window/window_empire.h"
#include "empire/trade_prices.h"
#include "game/resource.h"
#include "window/popup_dialog.h"
#include "city/city_message.h"
#include "city/city_building_menu_ctrl.h"
#include "core/profiler.h"
#include "core/log.h"
#include "core/flat_map.h"
#include "game/game.h"
#include "graphics/image.h"

#include <cstring>

xstring js_toxstring(js_State* J, int idx) {
    if (!js_isstring(J, idx)) {
        return {};
    }

    js_StringNode id = js_tostring(J, 1);
    xstring result;
    result._set(id);
    return result;
}

xstring js_xref(js_State* J) {
    js_StringNode new_ref = js_ref(J);
    xstring new_ref_str;
    new_ref_str._set(new_ref);
    return new_ref_str;
}

void __ui_draw_image(int imgid, vec2i pos) {
    ui::eimage(imgid, pos);
}
ANK_FUNCTION_2(__ui_draw_image);
void __ui_popup_message(xstring message) {
    messages::popup(message, 0, 0);
}
ANK_FUNCTION_1(__ui_popup_message)

void __ui_begin_widget(vec2i pos) {
    ui::begin_widget(pos);
}
ANK_FUNCTION_1(__ui_begin_widget);
void __ui_end_widget() {
    ui::end_widget();
}
ANK_FUNCTION(__ui_end_widget);
void __ui_set_clip_rectangle(vec2i pos, vec2i size) {
    const vec2i offset = ui::current_offset();
    ui::push(ui::cmd_t::clip_set, ui::opt::Pos{offset + pos}, ui::opt::Size{size});
}
ANK_FUNCTION_2(__ui_set_clip_rectangle);
void __ui_reset_clip_rectangle() {
    ui::push(ui::cmd_t::clip_reset);
}
ANK_FUNCTION(__ui_reset_clip_rectangle);
void __ui_fill_rect(vec2i pos, vec2i size, unsigned int c) {
    ui::fill_rect(pos, size, (color)c);
}
ANK_FUNCTION_3(__ui_fill_rect);
void __ui_border(vec2i pos, vec2i size, int type, unsigned int c, int flags) {
    ui::border(pos, size, type, (color)c, (UiFlags)flags);
}
ANK_FUNCTION_5(__ui_border);
void __ui_label_colored(pcstr text, vec2i pos, int font, unsigned int c) {
    ui::label_colored(text, pos, (e_font)font, (color)c);
}
ANK_FUNCTION_4(__ui_label_colored);

bool __ui_draw_button(pcstr text, vec2i pos, vec2i size, int font, int flags, pcstr tooltip) {
    const vec2i offset = ui::current_offset();
    const bool is_underlying = g_window_manager.underlying_windows_redrawing > 0;
    flags |= is_underlying ? UiFlags_Readonly : UiFlags_None;
    auto& btn = ui::button(text, pos, size, fonts_vec{(e_font)font}, (UiFlags)flags);
    if (tooltip && *tooltip) {
        btn.tooltip(xstring(tooltip));
    }

    if (is_underlying) {
        return false;
    }

    int lmb_click = 0;
    generic_buttons_handle_mouse(&mouse::ref(), offset, &btn, 1, nullptr, &lmb_click);
    return !!lmb_click;
}
ANK_FUNCTION_6(__ui_draw_button);

void __ui_dialog_show_yesno(pcstr text, js_helpers::js_function_ref cb_yes, js_helpers::js_function_ref cb_no) {
    xstring yes_ref = cb_yes.ref;
    xstring no_ref = cb_no.ref;
    popup_dialog::show_yesno(text, [yes_ref, no_ref](bool accepted) {
        if (accepted && !yes_ref.empty()) {
            js_call_function_bool(yes_ref, true);
        } else if (!accepted && !no_ref.empty()) {
            js_call_function_bool(no_ref, false);
        }
    });
}
ANK_FUNCTION_3(__ui_dialog_show_yesno)

void __ui_dialog_show_ok(pcstr text) {
    popup_dialog::show_ok(text, [] {});
}
ANK_FUNCTION_1(__ui_dialog_show_ok)

bool __ui_window_is(pcstr window_id) {
    return g_window_manager.window_is(window_id);
}
ANK_FUNCTION_1(__ui_window_is)
void __ui_window_advisors_show_advisor(int advisor) {
    window_advisors_show_advisor((e_advisor)advisor);
}
ANK_FUNCTION_1(__ui_window_advisors_show_advisor)
void __ui_draw_label(pcstr text, vec2i pos, int font) {
    ui::label(text, pos, (e_font)font);
}
ANK_FUNCTION_3(__ui_draw_label);

void __ui_draw_label_ex(pcstr text, vec2i pos, int font, int flags, int box_width) {
    ui::label(text, pos, (e_font)font, (UiFlags)flags, box_width);
}
ANK_FUNCTION_5(__ui_draw_label_ex)

void __ui_draw_resource_icon(vec2i pos, int resource) {
    ui::icon(pos, (e_resource)resource);
}
ANK_FUNCTION_2(__ui_draw_resource_icon)

void __ui_draw_resource_icon_flags(vec2i pos, int resource, int flags) {
    ui::icon(pos, (e_resource)resource, (UiFlags)flags);
}
ANK_FUNCTION_3(__ui_draw_resource_icon_flags)

void __ui_element_max_value(pcstr id, int v) {
    ui::widget* w = ui::get_current_widget();
    if (!w) {
        return;
    }
    (*w)[id].max_value(v);
}
ANK_FUNCTION_2(__ui_element_max_value)

void __window_resource_settings_show(int resource) {
    window_resource_settings_show((e_resource)resource);
}
ANK_FUNCTION_1(__window_resource_settings_show)

int __trade_price_buy(int resource) {
    return trade_price_buy((e_resource)resource);
}
ANK_FUNCTION_1(__trade_price_buy)

int __trade_price_sell(int resource) {
    return trade_price_sell((e_resource)resource);
}
ANK_FUNCTION_1(__trade_price_sell)

void __window_empire_show() {
    window_empire_show();
}
ANK_FUNCTION(__window_empire_show)

void __window_trade_opened_show(int city_id) {
    window_trade_opened_show(city_id);
}
ANK_FUNCTION_1(__window_trade_opened_show)

void __ui_draw_line(bool hline, vec2i pos, int size) {
    ui::line(hline, pos, size, 0xff000000);
}
ANK_FUNCTION_3(__ui_draw_line);
void __ui_window_city_show() {
    window_city_show();
}
ANK_FUNCTION(__ui_window_city_show)
void __ui_window_editor_map_show() {
    window_editor_map_show();
}
ANK_FUNCTION(__ui_window_editor_map_show)
void __window_labor_priority_show(int category) {
    window_labor_priority_show(category);
}
ANK_FUNCTION_1(__window_labor_priority_show)

void __ui_draw_texture(vec2i pos, int img_id) {
    ::painter ctx = game.painter();
    ctx.img_generic(img_id, pos);
}
ANK_FUNCTION_2(__ui_draw_texture)

void __ui_window_build_menu_show(int id) {
    window_build_menu_show(id);
}
ANK_FUNCTION_1(__ui_window_build_menu_show)
void __ui_widget_sidebar_set_type(int id) {
    widget_sidebar_set_type(id);
}
ANK_FUNCTION_1(__ui_widget_sidebar_set_type)
int __ui_widget_sidebar_city_offset_x() {
    return widget_sidebar_city_offset_x();
}
ANK_FUNCTION(__ui_widget_sidebar_city_offset_x)

ui::element* __ui_get_element(xstring element_id) {
    OZZY_PROFILER_SECTION(_, bstring128("ui:get_elem+", element_id.c_str()).c_str())
    ui::widget* w = ui::get_current_widget();
    return (w && !element_id.empty()) ? &(*w)[element_id] : nullptr;
}

// In MuJS: index 0 = this, index 1 = first argument.
static js_StringNode property_id = js_intern("id");
static js_StringNode property_undefined = js_intern("undefined");

ui::element* ui::GET_ELEM(js_State* J) {
    J->getproperty(0, property_id);
    js_StringNode id = js_isstring(J, -1) ? js_tostring(J, -1) : nullptr;
    js_pop(J, 1);
    if (!id || id == property_undefined) {
        logs::error("UI element proxy: id is undefined");
        js_stacktrace(J);
        return nullptr;
    }

    xstring id_str;
    id_str._set(id);
    return __ui_get_element(id_str);
}

void ui::proxy_get_text(js_State* J) {
    auto elem = GET_ELEM(J);
    J->pushstring(elem ? elem->text().c_str() : "");
}
void ui::proxy_set_text(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->text(js_toxstring(J, 1).c_str());
    }
    J->pushundefined();
}
void ui::proxy_get_enabled(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->enabled : false);
}
void ui::proxy_set_enabled(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->set_enabled(js_toboolean(J, 1));
    }
    J->pushundefined();
}
void ui::proxy_get_readonly(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->readonly : false);
}
void ui::proxy_set_readonly(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->readonly = js_toboolean(J, 1);
    }
    J->pushundefined();
}
void ui::proxy_get_font(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushnumber(J, elem ? elem->font() : FONT_INVALID);
}
void ui::proxy_set_font(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->font((int)js_tonumber(J, 1));
    }
    J->pushundefined();
}

void ui::proxy_get_text_color(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushnumber(J, elem ? elem->text_color() : COLOR_NULL);
}
void ui::proxy_set_text_color(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->text_color((color)(unsigned int)js_tonumber(J, 1));
    }
    J->pushundefined();
}

void ui::proxy_set_image(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->image((int)js_tonumber(J, 1));
    }
    J->pushundefined();
}
void ui::proxy_get_image_tid(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushnumber(J, elem ? elem->image().tid() : -1);
}
void ui::proxy_set_image_tid(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        const int id = (int)js_tonumber(J, 1);
        const image_t *img = image_get(id);
        if (img) {
            elem->image(img->desc());
        }
    }
    J->pushundefined();
}
void ui::proxy_get_selected(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->selected() : false);
}

void ui::proxy_set_selected(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->select(js_toboolean(J, 1));
    }
    J->pushundefined();
}

void ui::proxy_set_tooltip(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->tooltip(js_toxstring(J, 1));
    }
    J->pushundefined();
}

void ui::proxy_set_onclick(js_State* J) {
    auto elem = GET_ELEM(J);
    if (!elem) {
        J->pushundefined();
        return;
    }

    if (js_isnull(J, 1) || js_isundefined(J, 1)) {
        elem->set_ref(ui::element::ONCLICK, "");
        J->pushundefined();
        return;
    }

    if (!J->iscallable(1)) {
        elem->set_ref(ui::element::ONCLICK, "");
        J->pushundefined();
        return;
    }

    js_copy(J, 1);
    elem->set_ref(ui::element::ONCLICK, js_xref(J));
    J->pushundefined();
}
void ui::proxy_set_ondraw(js_State* J) {
    auto elem = GET_ELEM(J);
    if (!elem) {
        J->pushundefined();
        return;
    }

    if (js_isnull(J, 1) || js_isundefined(J, 1)) {
        elem->set_ref(ui::element::ONDRAW, "");
        elem->ondraw(nullptr);
        J->pushundefined();
        return;
    }

    if (!J->iscallable(1)) {
        elem->set_ref(ui::element::ONDRAW, "");
        elem->ondraw(nullptr);
        J->pushundefined();
        return;
    }

    js_copy(J, 1);
    elem->set_ref(ui::element::ONDRAW, js_xref(J));
    elem->ondraw(nullptr);
    J->pushundefined();
}
void ui::proxy_set_textfn(js_State* J) {
    auto elem = GET_ELEM(J);
    if (!elem) {
        J->pushundefined();
        return;
    }

    if (js_isnull(J, 1) || js_isundefined(J, 1)) {
        elem->set_ref(ui::element::TEXTFN, "");
        J->pushundefined();
        return;
    }

    if (!J->iscallable(1)) {
        elem->set_ref(ui::element::TEXTFN, "");
        J->pushundefined();
        return;
    }

    js_copy(J, 1);
    elem->set_ref(ui::element::TEXTFN, js_xref(J));
    J->pushundefined();
}

void ui::proxy_get_value(js_State* J) {
    auto elem = GET_ELEM(J);
    J->pushstring(elem ? elem->get_value() : "");
}

void ui::proxy_set_value(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->set_value(js_toxstring(J, 1).c_str());
    }
    J->pushundefined();
}

void ui::proxy_get_noop(js_State* J) {
    (void)J;
    J->pushundefined();
}

void ui::proxy_set_checkedfn(js_State* J) {
    auto elem = GET_ELEM(J);
    if (!elem) {
        J->pushundefined();
        return;
    }

    if (js_isnull(J, 1) || js_isundefined(J, 1)) {
        elem->set_ref(ui::element::CHECKEDFN, "");
        J->pushundefined();
        return;
    }

    if (!J->iscallable(1)) {
        elem->set_ref(ui::element::CHECKEDFN, "");
        J->pushundefined();
        return;
    }

    js_copy(J, 1);
    elem->set_ref(ui::element::CHECKEDFN, js_xref(J));
    J->pushundefined();
}

static flat_map<xstring, js_Object *, 32> g_ui_element_proto_by_kind;

void js_ui_register_element_proto(const xstring &kind, js_Object *proto) {
    if (!proto) {
        return;
    }
    g_ui_element_proto_by_kind.insert(std::make_pair(kind, proto));
}

js_Object *js_ui_element_proto_for_kind(const xstring &kind) {
    auto it = g_ui_element_proto_by_kind.find(kind);
    if (it != g_ui_element_proto_by_kind.end()) {
        return it->second;
    }

    auto def = g_ui_element_proto_by_kind.find(ui::element::skind());
    if (def != g_ui_element_proto_by_kind.end()) {
        return def->second;
    }

    verify_no_crash(false && "UI element prototype not found");
    return nullptr;
}

int __ui_building_menu_items(int type) {
    return g_building_menu_ctrl.count_items(type);
}
ANK_FUNCTION_1(__ui_building_menu_items)

void __ui_window_message_dialog_show(pcstr template_name) {
    window_message_dialog_show(template_name, -1, nullptr);
}
ANK_FUNCTION_1(__ui_window_message_dialog_show)

#define _R(name)            \
    js_newnumber(J, name);  \
    js_setglobal(J, #name);

void js_register_ui_objects(js_State* J) {
    for (UiElementProtoRegIterator *s = UiElementProtoRegIterator::tail; s; s = s->next) {
        s->func(J);
    }

    _R(UiFlags_None)
    _R(UiFlags_Darkened)
    _R(UiFlags_Grayscale)
    _R(UiFlags_PanelInner)
    _R(UiFlags_LabelMultiline)
    _R(UiFlags_AlignYCentered)
    _R(UiFlags_NoBody)
    _R(UiFlags_Rich)
    _R(UiFlags_Selected)
    _R(UiFlags_AlignCentered)
    _R(UiFlags_NoScroll)
    _R(UiFlags_AlignLeft)
    _R(UiFlags_AlignXCentered)
    _R(UiFlags_Readonly)
    _R(UiFlags_NoBorder)
    _R(UiFlags_Outline)
    _R(UiFlags_SplitText)
    _R(UiFlags_PanelSmall)
    _R(UiFlags_PanelOuter)
    _R(UiFlags_ThinBorder)
}