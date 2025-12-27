#include "js/js_game.h"
#include "js/js.h"

#include "ui.h"
#include "city/city_message.h"

void __ui_draw_image(int imgid, vec2i pos) { ui::eimage(imgid, pos); }
ANK_FUNCTION_2(__ui_draw_image);

void __ui_popup_message(xstring message) { messages::popup(message, 0, 0); }
ANK_FUNCTION_1(__ui_popup_message)

void js_register_ui_objects(js_State *J) {

}