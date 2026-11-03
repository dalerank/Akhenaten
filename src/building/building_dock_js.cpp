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

/** Test/helper: unweighted any-match count for up to 3 partner goods (0 = unused). */
static void __test_fill_resource_list(resource_list &out, int r0, int r1, int r2) {
    const int rs[3] = { r0, r1, r2 };
    for (int r : rs) {
        if (r > RESOURCE_NONE && r < RESOURCES_MAX) {
            out[(e_resource)r] = 1;
        }
    }
}

int __test_dock_match_score(int bid, int r0, int r1, int r2) {
    auto b = dock_from_bid(bid);
    if (!b) {
        return -1;
    }
    resource_list active;
    __test_fill_resource_list(active, r0, r1, r2);
    resource_list empty;
    return b->count_matching_goods(active, empty);
}
ANK_FUNCTION_4(__test_dock_match_score)

bool __test_dock_any_match(int bid, int r0, int r1, int r2) {
    return __test_dock_match_score(bid, r0, r1, r2) > 0;
}
ANK_FUNCTION_4(__test_dock_any_match)

/** Test: weighted score — imports ×2, exports ×1 (up to 3 each; 0 = unused). */
int __test_dock_trade_score(int bid, int i0, int i1, int i2, int e0, int e1, int e2) {
    auto b = dock_from_bid(bid);
    if (!b) {
        return -1;
    }
    resource_list imports;
    resource_list exports;
    __test_fill_resource_list(imports, i0, i1, i2);
    __test_fill_resource_list(exports, e0, e1, e2);
    return b->trade_match_score(imports, exports);
}
ANK_FUNCTION_7(__test_dock_trade_score)

int __test_dock_yard_proximity(int bid) {
    auto b = dock_from_bid(bid);
    return b ? b->yard_proximity_cost() : -1;
}
ANK_FUNCTION_1(__test_dock_yard_proximity)

int __test_dock_match_score_for_ship(int bid, int ship_id) {
    auto b = dock_from_bid(bid);
    return b ? b->match_score_for_ship(ship_id) : -1;
}
ANK_FUNCTION_2(__test_dock_match_score_for_ship)

int __test_map_get_free_dock(int ship_id) {
    return map_get_free_destination_dock(ship_id).bid;
}
ANK_FUNCTION_1(__test_map_get_free_dock)

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
