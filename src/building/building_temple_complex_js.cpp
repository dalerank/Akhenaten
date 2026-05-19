#include "building_temple_complex.h"

#include "city/city_buildings.h"
#include "js/js_game.h"
#include "mujs/jsvalue.h"
#include "mujs/jsbuiltin.h"

static js_Object *g_temple_complex_proto = nullptr;

static int temple_complex_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static void temple_complex_proto_has_upgrade(js_State *J) {
    const int bid = temple_complex_this_id(J);
    const int upgrade = js_helpers::js_to_value<int>(J, 1);
    auto *b = building_get_ex<building_temple_complex>(bid);
    js_helpers::js_push_value(J, b ? b->has_upgrade((e_temple_compex_upgrade)upgrade) : false);
}

static void temple_complex_proto_allowed_altar_count(js_State *J) {
    const int bid = temple_complex_this_id(J);
    auto *b = building_get_ex<building_temple_complex>(bid);
    js_helpers::js_push_value(J, b ? (int)b->base_params().allowed_altar.size() : 0);
}

static void temple_complex_proto_allowed_altar_at(js_State *J) {
    const int bid = temple_complex_this_id(J);
    const int idx = js_helpers::js_to_value<int>(J, 1);
    auto *b = building_get_ex<building_temple_complex>(bid);
    const int result = (b && idx >= 0 && idx < (int)b->base_params().allowed_altar.size())
                       ? (int)b->base_params().allowed_altar[idx] : 0;
    js_helpers::js_push_value(J, result);
}

static void temple_complex_proto_allowed_oracle_count(js_State *J) {
    const int bid = temple_complex_this_id(J);
    auto *b = building_get_ex<building_temple_complex>(bid);
    js_helpers::js_push_value(J, b ? (int)b->base_params().allowed_oracle.size() : 0);
}

static void temple_complex_proto_allowed_oracle_at(js_State *J) {
    const int bid = temple_complex_this_id(J);
    const int idx = js_helpers::js_to_value<int>(J, 1);
    auto *b = building_get_ex<building_temple_complex>(bid);
    const int result = (b && idx >= 0 && idx < (int)b->base_params().allowed_oracle.size())
                       ? (int)b->base_params().allowed_oracle[idx] : 0;
    js_helpers::js_push_value(J, result);
}

static void temple_complex_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "BuildingTempleComplex(%d)", temple_complex_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_BuildingTempleComplex(js_State *J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_temple_complex_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_temple_complex_building(js_State *J) {
    js_Object *building_proto = js_get_building_prototype();
    g_temple_complex_proto = jsV_newobject(J, JS_COBJECT, building_proto);
    js_pushobject(J, g_temple_complex_proto);

    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.has_upgrade"),          temple_complex_proto_has_upgrade,          1);
    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.allowed_altar_count"),  temple_complex_proto_allowed_altar_count,  0);
    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.allowed_altar_at"),     temple_complex_proto_allowed_altar_at,     1);
    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.allowed_oracle_count"), temple_complex_proto_allowed_oracle_count, 0);
    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.allowed_oracle_at"),    temple_complex_proto_allowed_oracle_at,    1);
    jsB_propf(J, js_intern("BuildingTempleComplex.prototype.toString"),             temple_complex_proto_toString,             0);

    js_newcconstructor(J, jsB_new_BuildingTempleComplex, jsB_new_BuildingTempleComplex, js_intern("BuildingTempleComplex"), 1);
    js_defglobal(J, js_intern("BuildingTempleComplex"), JS_DONTENUM);
}
