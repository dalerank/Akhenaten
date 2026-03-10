#include "js/js.h"

#include "ui.h"
#include "js/js_game.h"
#include "mujs/jsi.h"
#include "widget/widget_sidebar.h"
#include "graphics/elements/generic_button.h"
#include "graphics/window.h"
#include "window/window_city.h"
#include "window/window_build_menu.h"
#include "window/message_dialog_new.h"
#include "window/window_advisors.h"
#include "window/window_labor_priority.h"
#include "window/popup_dialog.h"
#include "city/city_message.h"
#include "city/city_building_menu_ctrl.h"
#include "graphics/graphics.h"
#include "core/profiler.h"
#include "game/game.h"

void __ui_draw_image(int imgid, vec2i pos) { ui::eimage(imgid, pos); } ANK_FUNCTION_2(__ui_draw_image);
void __ui_popup_message(xstring message) { messages::popup(message, 0, 0); } ANK_FUNCTION_1(__ui_popup_message)

void __ui_begin_widget(vec2i pos) { ui::begin_widget(pos); } ANK_FUNCTION_1(__ui_begin_widget);
void __ui_end_widget() { ui::end_widget(); } ANK_FUNCTION(__ui_end_widget);
void __ui_fill_rect(vec2i pos, vec2i size, unsigned int c) { ui::fill_rect(pos, size, (color)c); } ANK_FUNCTION_3(__ui_fill_rect);
void __ui_border(vec2i pos, vec2i size, int type, unsigned int c, int flags) { ui::border(pos, size, type, (color)c, (UiFlags)flags); } ANK_FUNCTION_5(__ui_border);
void __ui_label_colored(pcstr text, vec2i pos, int font, unsigned int c) { ui::label_colored(text, pos, (e_font)font, (color)c); } ANK_FUNCTION_4(__ui_label_colored);

bool __ui_draw_button(pcstr text, vec2i pos, vec2i size, int font, int flags) {
    const vec2i offset = ui::current_offset();
    const bool is_underlying = g_window_manager.underlying_windows_redrawing > 0;
    flags |= is_underlying ? UiFlags_Readonly : UiFlags_None;
    auto &btn = ui::button(text, pos, size, fonts_vec{ (e_font)font }, flags);

    if (is_underlying) {
        return false;
    }

    int lmb_click = 0;
    generic_buttons_handle_mouse(&mouse::ref(), offset, &btn, 1, nullptr, &lmb_click);
    return !!lmb_click;
}
ANK_FUNCTION_5(__ui_draw_button);

void __ui_dialog_show_yesno(pcstr text, js_helpers::js_function_ref cb_yes, js_helpers::js_function_ref cb_no) {
    xstring yes_ref = cb_yes.ref;
    xstring no_ref = cb_no.ref;
    popup_dialog::show_yesno(text, [yes_ref, no_ref](bool accepted) {
        if (accepted && !yes_ref.empty()) {
            js_call_function_bool(yes_ref, true);
            js_unref_function(yes_ref);
        } else if (!accepted && !no_ref.empty()) {
            js_call_function_bool(no_ref, false);
            js_unref_function(no_ref);
        }
    });
}
ANK_FUNCTION_3(__ui_dialog_show_yesno)

bool __ui_window_is(int window_id) { return window_is((e_window_id)window_id); } ANK_FUNCTION_1(__ui_window_is)
void __ui_window_advisors_show_advisor(int advisor) { window_advisors_show_advisor((e_advisor)advisor); } ANK_FUNCTION_1(__ui_window_advisors_show_advisor)
void __ui_draw_label(pcstr text, vec2i pos, int font) { ui::label(text, pos, (e_font)font); } ANK_FUNCTION_3(__ui_draw_label);
void __ui_draw_line(bool hline, vec2i pos, int size) { ui::line(hline, pos, size, 0xff000000); } ANK_FUNCTION_3(__ui_draw_line);
void __ui_window_city_show() { window_city_show(); } ANK_FUNCTION(__ui_window_city_show)
void __window_labor_priority_show(int category) { window_labor_priority_show(category); } ANK_FUNCTION_1(__window_labor_priority_show)

void __ui_draw_texture(vec2i pos, int img_id) {
    ::painter ctx = game.painter();
    ctx.img_generic(img_id, pos);
}
ANK_FUNCTION_2(__ui_draw_texture)

void __ui_window_build_menu_show(int id) { window_build_menu_show(id); } ANK_FUNCTION_1(__ui_window_build_menu_show)
void __ui_widget_sidebar_set_type(int id) { widget_sidebar_set_type(id); } ANK_FUNCTION_1(__ui_widget_sidebar_set_type)
int __ui_widget_sidebar_city_offset_x() { return widget_sidebar_city_offset_x(); } ANK_FUNCTION(__ui_widget_sidebar_city_offset_x)

ui::element* __ui_get_element(pcstr element_id) {
    OZZY_PROFILER_SECTION(_, element_id)
    ui::widget *w = ui::get_current_widget();
    return (w && element_id) ? &(*w)[element_id] : nullptr;
}

// In MuJS: index 0 = this, index 1 = first argument.
ui::element *GET_ELEM(js_State *J) {
    js_getproperty(J, 0, "id");
    pcstr id = js_isstring(J, -1) ? js_tostring(J, -1) : nullptr;
    js_pop(J, 1);
    if (!id || strcmp(id, "undefined") == 0) {
        logs::error("UI element proxy: id is undefined");
        js_stacktrace(J);
        return nullptr;
    }
    return __ui_get_element(id);
}

void ui_proxy_get_text(js_State *J) { auto elem = GET_ELEM(J); js_pushstring(J, elem ? elem->text().c_str() : ""); }
void ui_proxy_set_text(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->text(js_tostring(J, 1)); } J->pushundefined(); }
void ui_proxy_get_enabled(js_State *J) { auto elem = GET_ELEM(J); js_pushboolean(J, elem ? elem->enabled : false); }
void ui_proxy_set_enabled(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->set_enabled(js_toboolean(J, 1)); } J->pushundefined(); }
void ui_proxy_get_readonly(js_State *J) { auto elem = GET_ELEM(J); js_pushboolean(J, elem ? elem->readonly : false); }
void ui_proxy_set_readonly(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->readonly = js_toboolean(J, 1); } J->pushundefined(); }
void ui_proxy_get_font(js_State *J) { auto elem = GET_ELEM(J); js_pushnumber(J, elem ? elem->font() : FONT_INVALID); }
void ui_proxy_set_font(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->font((int)js_tonumber(J, 1)); } J->pushundefined(); }
void ui_proxy_get_text_color(js_State *J) { auto elem = GET_ELEM(J); js_pushnumber(J, elem ? elem->text_color() : COLOR_NULL); }
void ui_proxy_set_text_color(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->text_color((color)(unsigned int)js_tonumber(J, 1)); } J->pushundefined(); }
void ui_proxy_get_noop(js_State *J) { (void)J; J->pushundefined(); }
void ui_proxy_set_image(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->image((int)js_tonumber(J, 1)); } J->pushundefined(); }
void ui_proxy_get_selected(js_State *J) { auto elem = GET_ELEM(J); js_pushboolean(J, elem ? elem->selected() : false); }
void ui_proxy_set_selected(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->select(js_toboolean(J, 1)); } J->pushundefined(); }
void ui_proxy_set_tooltip(js_State *J) { auto elem = GET_ELEM(J); if (elem) { elem->tooltip(xstring(js_tostring(J, 1))); } J->pushundefined(); }

void js_register_ui_proxy_accessors(js_State *J) {
    js_newobject(J);
    struct { const char *name; js_CFunction getter; js_CFunction setter; } props[] = {
        {"text", ui_proxy_get_text, ui_proxy_set_text},
        {"enabled", ui_proxy_get_enabled, ui_proxy_set_enabled},
        {"readonly", ui_proxy_get_readonly, ui_proxy_set_readonly},
        {"font", ui_proxy_get_font, ui_proxy_set_font},
        {"text_color", ui_proxy_get_text_color, ui_proxy_set_text_color},
        {"image", ui_proxy_get_noop, ui_proxy_set_image},
        {"selected", ui_proxy_get_selected, ui_proxy_set_selected},
        {"tooltip", ui_proxy_get_noop, ui_proxy_set_tooltip},
    };
    for (const auto &p : props) {
        js_newarray(J);
        js_newcfunction(J, p.getter, "", 0);
        js_setindex(J, -2, 0);
        js_newcfunction(J, p.setter, "", 1);
        js_setindex(J, -2, 1);
        js_setproperty(J, -2, p.name);
    }
    js_setglobal(J, "__ui_proxy_accessors");
}

int __ui_building_menu_items(int type) { return g_building_menu_ctrl.count_items(type); } ANK_FUNCTION_1(__ui_building_menu_items)

void __ui_window_message_dialog_show(pcstr template_name) { window_message_dialog_show(template_name, -1, nullptr); }
ANK_FUNCTION_1(__ui_window_message_dialog_show)

#define _R(name) js_newnumber(J, name); js_setglobal(J, #name);
void js_register_ui_objects(js_State *J) {
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

    js_register_ui_proxy_accessors(J);
}