#include "city/city_festival.h"

#include "city/city.h"
#include "core/profiler.h"
#include "js/js_game.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, e_god *ptr) {
    js_register_bound_int_property(J, name, reinterpret_cast<int *>(ptr));
}

void ank_global_obj_bind_field(js_State *J, js_StringNode name, e_festival_type *ptr) {
    js_register_bound_int8_property(J, name, reinterpret_cast<int8_t *>(ptr));
}

ANK_GLOBAL_OBJECT(g_city.festival, __city_festival,
    planned_god,
    planned_size,
    months_till_next,
    months_since_festival);