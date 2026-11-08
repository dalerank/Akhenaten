#include "building_dock.h"

#include "city/city_buildings.h"
#include "game/resource.h"
#include "js/js_game.h"
#include "js/js.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "core/profiler.h"

#include <cstdio>

static building_dock *dock_from_bid(int bid) {
    building *b = building_get(bid);
    return b ? b->dcast_dock() : nullptr;
}

static int dock_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static building_dock *dock_this(js_State *J) {
    return dock_from_bid(dock_this_id(J));
}

/* ---- Dock JS object (inherits Building.prototype) ---- */

static js_Object *g_dock_proto = nullptr;

static void dock_proto_is_trade_accepted(js_State *J) {
    building_dock *b = dock_this(J);
    const e_resource resource = (e_resource)J->to<int>(1);
    J->push(b ? b->is_trade_accepted(resource) : false);
}

static void dock_proto_toggle_good_accepted(js_State *J) {
    building_dock *b = dock_this(J);
    if (b) {
        b->toggle_good_accepted((e_resource)J->to<int>(1));
    }
    js_helpers::js_push_void(J);
}

static void dock_proto_unaccept_all_goods(js_State *J) {
    building_dock *b = dock_this(J);
    if (b) {
        b->unaccept_all_goods();
    }
    js_helpers::js_push_void(J);
}

static void dock_proto_accept_all_goods(js_State *J) {
    building_dock *b = dock_this(J);
    if (b) {
        b->accept_all_goods();
    }
    js_helpers::js_push_void(J);
}

static void dock_proto_accepts_any_goods(js_State *J) {
    building_dock *b = dock_this(J);
    J->push(b ? b->accepts_any_goods() : false);
}

static void dock_proto_count_idle_dockers(js_State *J) {
    building_dock *b = dock_this(J);
    J->push(b ? b->count_idle_dockers() : 0);
}

static void dock_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "Dock(%d)", dock_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_Dock(js_State *J) {
    const int id = J->gettop() > 1 ? (int)js_tointeger(J, 1) : 0;
    building_dock *dock = dock_from_bid(id);
    if (!dock || !dock->is_valid()) {
        js_pushnull(J);
        return;
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_dock_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_dock(js_State *J) {
    js_Object *building_proto = js_get_building_prototype();
    g_dock_proto = jsV_newobject(J, JS_COBJECT, building_proto);
    js_pushobject(J, g_dock_proto);

    jsB_propf(J, js_intern("Dock.prototype.is_trade_accepted"), dock_proto_is_trade_accepted, 1);
    jsB_propf(J, js_intern("Dock.prototype.toggle_good_accepted"), dock_proto_toggle_good_accepted, 1);
    jsB_propf(J, js_intern("Dock.prototype.unaccept_all_goods"), dock_proto_unaccept_all_goods, 0);
    jsB_propf(J, js_intern("Dock.prototype.accept_all_goods"), dock_proto_accept_all_goods, 0);
    jsB_propf(J, js_intern("Dock.prototype.accepts_any_goods"), dock_proto_accepts_any_goods, 0);
    jsB_propf(J, js_intern("Dock.prototype.count_idle_dockers"), dock_proto_count_idle_dockers, 0);
    jsB_propf(J, js_intern("Dock.prototype.toString"), dock_proto_toString, 0);

    J->newcconstructor(jsB_new_Dock, jsB_new_Dock, js_intern("Dock"), 1);
    js_defglobal(J, js_intern("Dock"), JS_DONTENUM);
}
