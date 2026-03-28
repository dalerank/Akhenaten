#include "js/js.h"

#include "ui.h"
#include "js/js_game.h"
#include "mujs/jsi.h"
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

#include <cstring>

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
ui::element* GET_ELEM(js_State* J) {
    J->getproperty(0, "id");
    pcstr id = js_isstring(J, -1) ? js_tostring(J, -1) : nullptr;
    js_pop(J, 1);
    if (!id || strcmp(id, "undefined") == 0) {
        logs::error("UI element proxy: id is undefined");
        js_stacktrace(J);
        return nullptr;
    }
    return __ui_get_element(id);
}

void ui_proxy_get_text(js_State* J) {
    auto elem = GET_ELEM(J);
    J->pushstring(elem ? elem->text().c_str() : "");
}
void ui_proxy_set_text(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->text(js_tostring(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_get_enabled(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->enabled : false);
}
void ui_proxy_set_enabled(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->set_enabled(js_toboolean(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_get_readonly(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->readonly : false);
}
void ui_proxy_set_readonly(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->readonly = js_toboolean(J, 1);
    }
    J->pushundefined();
}
void ui_proxy_get_font(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushnumber(J, elem ? elem->font() : FONT_INVALID);
}
void ui_proxy_set_font(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->font((int)js_tonumber(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_get_text_color(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushnumber(J, elem ? elem->text_color() : COLOR_NULL);
}
void ui_proxy_set_text_color(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->text_color((color)(unsigned int)js_tonumber(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_get_noop(js_State* J) {
    (void)J;
    J->pushundefined();
}
void ui_proxy_set_image(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->image((int)js_tonumber(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_get_selected(js_State* J) {
    auto elem = GET_ELEM(J);
    js_pushboolean(J, elem ? elem->selected() : false);
}
void ui_proxy_set_selected(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->select(js_toboolean(J, 1));
    }
    J->pushundefined();
}
void ui_proxy_set_tooltip(js_State* J) {
    auto elem = GET_ELEM(J);
    if (elem) {
        elem->tooltip(xstring(js_tostring(J, 1)));
    }
    J->pushundefined();
}
void ui_proxy_set_onclick(js_State* J) {
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
    pcstr new_ref = js_ref(J);
    elem->set_ref(ui::element::ONCLICK, new_ref ? xstring(new_ref) : xstring());
    J->pushundefined();
}
void ui_proxy_set_ondraw(js_State* J) {
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
    pcstr new_ref = js_ref(J);
    elem->set_ref(ui::element::ONDRAW, new_ref ? xstring(new_ref) : xstring());
    elem->ondraw(nullptr);
    J->pushundefined();
}
void ui_proxy_set_textfn(js_State* J) {
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
    pcstr new_ref = js_ref(J);
    elem->set_ref(ui::element::TEXTFN, new_ref ? xstring(new_ref) : xstring());
    J->pushundefined();
}
void ui_proxy_set_checkedfn(js_State* J) {
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
    pcstr new_ref = js_ref(J);
    elem->set_ref(ui::element::CHECKEDFN, new_ref ? xstring(new_ref) : xstring());
    J->pushundefined();
}
void ui_proxy_get_noop_render_item(js_State* J) {
    (void)J;
    J->pushundefined();
}
void ui_proxy_get_value(js_State* J) {
    auto elem = GET_ELEM(J);
    J->pushstring(elem ? elem->get_value() : "");
}
void ui_proxy_set_value(js_State* J) {
    auto elem = GET_ELEM(J);
    pcstr v = js_tostring(J, 1);
    if (elem) {
        elem->set_value(v);
    }
    J->pushundefined();
}

void ui_proxy_add_item(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->add_item(js_isstring(J, 1) ? js_tostring(J, 1) : "");
    }
    J->pushundefined();
}

void ui_proxy_clear(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->clear();
    }
    J->pushundefined();
}

void ui_proxy_select_item(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    auto list = elem ? elem->dcast_scrollable_list() : nullptr;
    if (list) {
        pcstr text = js_isstring(J, 1) ? js_tostring(J, 1) : "";
        list->select_item(text);
    }
    J->pushundefined();
}

void ui_proxy_select_entry(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->select_entry(js_tointeger(J, 1));
    }
    J->pushundefined();
}

void ui_proxy_refresh_file_finder(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list)
            list->refresh_file_finder();
    }
    J->pushundefined();
}

void ui_proxy_change_file_path(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            pcstr d = js_isstring(J, 1) ? js_tostring(J, 1) : "";
            pcstr e = js_isstring(J, 2) ? js_tostring(J, 2) : "";
            list->change_file_path(xstring(d), xstring(e));
        }
    }
    J->pushundefined();
}

void ui_proxy_append_files_with_extension(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            pcstr d = js_isstring(J, 1) ? js_tostring(J, 1) : "";
            pcstr e = js_isstring(J, 2) ? js_tostring(J, 2) : "";
            list->append_files_with_extension(d, e);
        }
    }
    J->pushundefined();
}

void ui_proxy_scroll_to_selected(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    if (elem) {
        auto* list = elem->dcast_scrollable_list();
        if (list) {
            list->scroll_to_selected();
        }
    }
    J->pushundefined();
}

void ui_proxy_get_selected_text(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    int syntax = js_tointeger(J, 1);
    auto list = elem ? elem->dcast_scrollable_list() : nullptr;
    xstring text = list ? list->selected_entry_text(syntax).c_str() : "";
    J->pushstring(text.c_str());
}

void ui_proxy_get_items_count(js_State* J) {
    ui::element* elem = GET_ELEM(J);
    auto* list = elem ? elem->dcast_scrollable_list() : nullptr;
    int items_count = list ? list->items_count() : 0;
    js_pushnumber(J, items_count);
}

struct ui_proxy_prop {
    js_CFunction getter;
    js_CFunction setter;
};
static const flat_map<xstring, ui_proxy_prop, 16> g_ui_proxy_props = {
  {"text", {ui_proxy_get_text, ui_proxy_set_text}},
  {"enabled", {ui_proxy_get_enabled, ui_proxy_set_enabled}},
  {"readonly", {ui_proxy_get_readonly, ui_proxy_set_readonly}},
  {"font", {ui_proxy_get_font, ui_proxy_set_font}},
  {"text_color", {ui_proxy_get_text_color, ui_proxy_set_text_color}},
  {"image", {ui_proxy_get_noop, ui_proxy_set_image}},
  {"selected", {ui_proxy_get_selected, ui_proxy_set_selected}},
  {"tooltip", {ui_proxy_get_noop, ui_proxy_set_tooltip}},
  {"onclick", {nullptr, ui_proxy_set_onclick}},
  {"ondraw", {nullptr, ui_proxy_set_ondraw}},
  {"textfn", {nullptr, ui_proxy_set_textfn}},
  {"checked", {ui_proxy_get_selected, ui_proxy_set_selected}},
  {"checkedfn", {nullptr, ui_proxy_set_checkedfn}},
  {"items_count", {ui_proxy_get_items_count, nullptr}},
  {"value", {ui_proxy_get_value, ui_proxy_set_value}},
};

struct ui_proxy_func {
    js_CFunction fn;
    int nargs;
};
static const flat_map<xstring, ui_proxy_func, 16> g_ui_proxy_funcs = {
  {"add_item", {ui_proxy_add_item, 1}},
  {"clear", {ui_proxy_clear, 0}},
  {"select_item", {ui_proxy_select_item, 1}},
  {"select_index", {ui_proxy_select_entry, 1}},
  {"refresh_file_finder", {ui_proxy_refresh_file_finder, 0}},
  {"change_file_path", {ui_proxy_change_file_path, 2}},
  {"append_files_with_extension", {ui_proxy_append_files_with_extension, 2}},
  {"scroll_to_selected", {ui_proxy_scroll_to_selected, 0}},
  {"selected_text", {ui_proxy_get_selected_text, 1}},
};

void js_push_props(js_State* J, ui::widget* w, pcstr element_id) {
    const auto& elem = (*w)[element_id];
    auto props = elem.prop_names();
    for (const xstring& prop_name : props) {
        auto it = g_ui_proxy_props.find(prop_name);
        if (it != g_ui_proxy_props.end()) {
            js_newcfunction(J, it->second.getter, "", 0);
            js_newcfunction(J, it->second.setter, "", 1);
            js_defaccessor(J, -3, prop_name.c_str(), 0);
        }
    }
}

void js_push_funcs(js_State* J, ui::widget* w, pcstr element_id) {
    const auto& elem = (*w)[element_id];
    auto funcs = elem.func_names();
    for (const xstring& func_name : funcs) {
        auto it = g_ui_proxy_funcs.find(func_name);
        if (it != g_ui_proxy_funcs.end()) {
            js_newcfunction(J, it->second.fn, it->first.c_str(), it->second.nargs);
            js_setproperty(J, -2, func_name.c_str());
        }
    }
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