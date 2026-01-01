#include "js/js_game.h"
#include "js/js.h"

#include "ui.h"
#include "graphics/elements/generic_button.h"
#include "window/window_city.h"
#include "city/city_message.h"

void __ui_draw_image(int imgid, vec2i pos) { ui::eimage(imgid, pos); }
ANK_FUNCTION_2(__ui_draw_image);

void __ui_popup_message(xstring message) { messages::popup(message, 0, 0); }
ANK_FUNCTION_1(__ui_popup_message)

bool __ui_draw_button(pcstr text, vec2i pos, vec2i size, int font, int flags) {
    const vec2i offset = ui::current_offset();
    auto &btn = ui::button(text, pos, size, fonts_vec{ (e_font)font }, flags);
    const bool handled = generic_buttons_handle_mouse(&mouse::ref(), offset, &btn, 1, nullptr);
    return handled;
}
ANK_FUNCTION_5(__ui_draw_button);

void __ui_draw_label(pcstr text, vec2i pos, int font) { ui::label(text, pos, (e_font)font); }
ANK_FUNCTION_3(__ui_draw_label);

void __ui_window_city_show() { window_city_show(); }
ANK_FUNCTION(__ui_window_city_show)

pcstr __ui_element_get_text(pcstr element_id) {
    ui::widget* w = ui::get_current_widget();
    if (w && element_id) {
        ui::element& elem = (*w)[element_id];
        return elem.text().c_str();
    }
    return "";
}
ANK_FUNCTION_1(__ui_element_get_text)

void __ui_element_set_text(pcstr element_id, pcstr text) {
    ui::widget* w = ui::get_current_widget();
    if (w && element_id && text) {
        ui::element& elem = (*w)[element_id];
        elem.text(text);
    }
}
ANK_FUNCTION_2(__ui_element_set_text)

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