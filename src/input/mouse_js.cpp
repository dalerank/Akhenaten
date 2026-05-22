#include "mouse.h"

#include "js/js_game.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, mouse_button *ptr) {
    js_newobject(J);
    ank_global_obj_bind_field(J, js_intern("is_down"), &ptr->is_down);
    ank_global_obj_bind_field(J, js_intern("went_down"), &ptr->went_down);
    ank_global_obj_bind_field(J, js_intern("went_up"), &ptr->went_up);
    ank_global_obj_bind_field(J, js_intern("double_click"), &ptr->double_click);
    ank_global_obj_bind_field(J, js_intern("system_change"), &ptr->system_change);
    js_setproperty(J, -2, name);
}

ANK_GLOBAL_OBJECT(g_mouse, __mouse,
    x,
    y,
    scrolled,
    left,
    middle,
    right,
    is_inside_window,
    is_touch);

void __mouse_reset_up_state() { mouse::ref().reset_up_state(); }
ANK_FUNCTION(__mouse_reset_up_state)
