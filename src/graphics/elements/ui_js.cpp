#include "js/js.h"

#include "ui.h"
#include "js/js_game.h"
#include "widget/widget_sidebar.h"
#include "graphics/elements/generic_button.h"
#include "window/window_city.h"
#include "window/window_build_menu.h"
#include "window/message_dialog_new.h"
#include "city/city_message.h"
#include "city/city_building_menu_ctrl.h"
#include "graphics/graphics.h"
#include "game/game.h"

void __ui_draw_image(int imgid, vec2i pos) { ui::eimage(imgid, pos); } ANK_FUNCTION_2(__ui_draw_image);
void __ui_popup_message(xstring message) { messages::popup(message, 0, 0); } ANK_FUNCTION_1(__ui_popup_message)

void __ui_begin_widget(int x, int y) { ui::begin_widget({x, y}); } ANK_FUNCTION_2(__ui_begin_widget);
void __ui_end_widget() { ui::end_widget(); } ANK_FUNCTION(__ui_end_widget);
void __ui_fill_rect(int x, int y, int width, int height, unsigned int c) { ui::fill_rect({x, y}, {width, height}, (color)c); } ANK_FUNCTION_5(__ui_fill_rect);
void __ui_border(int x, int y, int width, int height, int type, unsigned int c, int flags) { ui::border({x, y}, {width, height}, type, (color)c, (UiFlags)flags); } ANK_FUNCTION_7(__ui_border);
void __ui_label_colored(pcstr text, int x, int y, int font, unsigned int c) { ui::label_colored(text, {x, y}, (e_font)font, (color)c); } ANK_FUNCTION_5(__ui_label_colored);

bool __ui_draw_button(pcstr text, vec2i pos, vec2i size, int font, int flags) {
    const vec2i offset = ui::current_offset();
    auto &btn = ui::button(text, pos, size, fonts_vec{ (e_font)font }, flags);
    const bool handled = generic_buttons_handle_mouse(&mouse::ref(), offset, &btn, 1, nullptr);
    return handled;
}
ANK_FUNCTION_5(__ui_draw_button);

void __ui_draw_label(pcstr text, vec2i pos, int font) { ui::label(text, pos, (e_font)font); } ANK_FUNCTION_3(__ui_draw_label);
void __ui_draw_line(bool hline, vec2i pos, int size) { ui::line(hline, pos, size, 0xff000000); } ANK_FUNCTION_3(__ui_draw_line);
void __ui_window_city_show() { window_city_show(); } ANK_FUNCTION(__ui_window_city_show)

void __ui_draw_texture(vec2i pos, int img_id) {
    ::painter ctx = game.painter();
    ctx.img_generic(img_id, pos); 
}
ANK_FUNCTION_2(__ui_draw_texture)

void __ui_window_build_menu_show(int id) { window_build_menu_show(id); } ANK_FUNCTION_1(__ui_window_build_menu_show)
void __ui_widget_sidebar_set_type(int id) { widget_sidebar_set_type(id); } ANK_FUNCTION_1(__ui_widget_sidebar_set_type)
int __widget_sidebar_city_offset_x() { return widget_sidebar_city_offset_x(); } ANK_FUNCTION(__widget_sidebar_city_offset_x)

static inline ui::element* __ui_get_element(pcstr element_id) {
    ui::widget *w = ui::get_current_widget();
    return (w && element_id) ? &(*w)[element_id] : nullptr;
}

pcstr __ui_element_get_text(pcstr element_id) {
    auto elem = __ui_get_element(element_id);
    return elem ? elem->text().c_str() : "";
}
ANK_FUNCTION_1(__ui_element_get_text)

void __ui_element_set_text(pcstr element_id, pcstr text) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->text(text); }
}
ANK_FUNCTION_2(__ui_element_set_text)

bool __ui_element_get_enabled(pcstr element_id) {
    auto elem = __ui_get_element(element_id);
    return elem ? elem->enabled : false;
}
ANK_FUNCTION_1(__ui_element_get_enabled)

void __ui_element_set_enabled(pcstr element_id, bool v) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->set_enabled(v); }
}
ANK_FUNCTION_2(__ui_element_set_enabled)

int __ui_element_get_font(pcstr element_id) {
    auto elem = __ui_get_element(element_id);
    return elem ? elem->font() : FONT_INVALID;
}
ANK_FUNCTION_1(__ui_element_get_font)

void __ui_element_set_font(pcstr element_id, int v) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->font(v); }
}
ANK_FUNCTION_2(__ui_element_set_font)

int __ui_element_get_text_color(pcstr element_id) {
    auto elem = __ui_get_element(element_id);
    return elem ? elem->text_color() : COLOR_NULL;
}
ANK_FUNCTION_1(__ui_element_get_text_color)

void __ui_element_set_image(pcstr element_id, int v) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->image(v); }
}
ANK_FUNCTION_2(__ui_element_set_image)

bool __ui_element_get_selected(pcstr element_id) {
    auto elem = __ui_get_element(element_id);
    return elem ? elem->selected() : false;
}
ANK_FUNCTION_1(__ui_element_get_selected)

void __ui_element_set_selected(pcstr element_id, bool v) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->select(v); }
}
ANK_FUNCTION_2(__ui_element_set_selected)

void __ui_element_set_text_color(pcstr element_id, unsigned int v) {
    auto elem = __ui_get_element(element_id);
    if (elem) { elem->text_color((color)v); }
}
ANK_FUNCTION_2(__ui_element_set_text_color)

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
}