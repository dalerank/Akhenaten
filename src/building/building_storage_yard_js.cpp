#include "building_storage.h"

#include "building/building_storage_yard.h"
#include "grid/building.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"

#include <cstdio>

static int storage_yard_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static building_storage_yard * storage_yard_this(js_State *J) {
    const int bid = storage_yard_this_id(J);
    building *raw = building_get(bid);
    return raw ? storage_yard_cast(raw) : nullptr;
}

static void storage_yard_proto_is_empty_all(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    js_helpers::js_push_value(J, b ? b->is_empty_all() : false);
}

static void storage_yard_proto_resource_state(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    if (b) {
        const int resource_id = js_helpers::js_to_value<int>(J, 1);
        const int increase = js_helpers::js_to_value<bool>(J, 2);
        building_storage_cycle_resource_state(b->storage_id(), resource_id, increase);
    }
    js_helpers::js_push_void(J);
}

static void storage_yard_proto_resource_max_accept(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    const int resource_id = js_helpers::js_to_value<int>(J, 1);
    const storage_t *s = b ? building_storage_get(b->storage_id()) : nullptr;
    js_helpers::js_push_value(J, s ? s->resource_max_accept[resource_id] : 0);
}

static void storage_yard_proto_resource_max_get(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    const int resource_id = js_helpers::js_to_value<int>(J, 1);
    const storage_t *s = b ? building_storage_get(b->storage_id()) : nullptr;
    js_helpers::js_push_value(J, s ? s->resource_max_get[resource_id] : 0);
}

static void storage_yard_proto_toggle_empty_all(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    if (b) {
        building_storage_toggle_empty_all(b->storage_id());
    }
}

static void storage_yard_proto_accept_none(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    if (b) {
        building_storage_accept_none(b->storage_id());
    }
}

static void storage_yard_proto_cycle_resource_state(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    const int resource_id = js_helpers::js_to_value<int>(J, 1);
    const storage_t *s = b ? building_storage_get(b->storage_id()) : nullptr;
    js_helpers::js_push_value(J, s ? s->resource_state[resource_id] : 0);
}

static void storage_yard_proto_increase_decrease_resource_state(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    const int resource_id = js_helpers::js_to_value<int>(J, 1);
    const bool increase = js_helpers::js_to_value<bool>(J, 2);
    building_storage_increase_decrease_resource_state(b ? b->storage_id() : 0, resource_id, increase);
}

static void storage_yard_proto_toString(js_State *J) {
    building_storage_yard *b = storage_yard_this(J);
    js_helpers::js_push_value(J, b ? "StorageYard" : "unknown");
}

static js_Object *g_storage_yard_proto = nullptr;

static void jsB_new_StorageYard(js_State *J) {
    int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    building_storage_yard *yard = storage_yard_cast(building_get(id));
    id = yard ? yard->id() : 0;

    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_storage_yard_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_storage_yard(js_State *J) {
    js_Object *building_proto = js_get_building_prototype();
    g_storage_yard_proto = jsV_newobject(J, JS_COBJECT, building_proto);
    js_pushobject(J, g_storage_yard_proto);

    jsB_propf(J, js_intern("StorageYard.prototype.is_empty_all"), storage_yard_proto_is_empty_all, 0);
    jsB_propf(J, js_intern("StorageYard.prototype.resource_state"), storage_yard_proto_resource_state, 1);
    jsB_propf(J, js_intern("StorageYard.prototype.resource_max_accept"), storage_yard_proto_resource_max_accept, 1);
    jsB_propf(J, js_intern("StorageYard.prototype.resource_max_get"), storage_yard_proto_resource_max_get, 1);
    jsB_propf(J, js_intern("StorageYard.prototype.toggle_empty_all"), storage_yard_proto_toggle_empty_all, 0);
    jsB_propf(J, js_intern("StorageYard.prototype.accept_none"), storage_yard_proto_accept_none, 0);
    jsB_propf(J, js_intern("StorageYard.prototype.cycle_resource_state"), storage_yard_proto_cycle_resource_state, 1);
    jsB_propf(J, js_intern("StorageYard.prototype.increase_decrease_resource_state"),
        storage_yard_proto_increase_decrease_resource_state, 2);
    jsB_propf(J, js_intern("StorageYard.prototype.toString"), storage_yard_proto_toString, 0);

    js_newcconstructor(J, jsB_new_StorageYard, jsB_new_StorageYard, js_intern("StorageYard"), 1);
    js_defglobal(J, js_intern("StorageYard"), JS_DONTENUM);
}
