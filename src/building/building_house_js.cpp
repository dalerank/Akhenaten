#include "building_house.h"
#include "building/building.h"
#include "building/building_house_model.h"
#include "city/city.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "js/js_game.h"
#include "js/js.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "core/profiler.h"
#include "core/bstring.h"

#include <cstdio>

static building_house *house_from_bid(int bid) {
    building *b = building_get(bid);
    return b ? b->dcast_house() : nullptr;
}

static int house_this_id(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

std::optional<bvariant> __house_get_property(int bid, const xstring property) {
    building_house* house = house_from_bid(bid);
    if (!house) {
        return {};
    }

    auto result = archive_helper::get(house->runtime_data(), property, true);
    if (result.has_value()) {
        return result;
    }

    return archive_helper::get(house->base, property, true);
}

void house_proto___house_level(js_State *J) {
    const int bid = house_this_id(J);
    building_house* house = house_from_bid(bid);
    const int value = (!house) ? 0 : house->house_level();
    J->push(value);
}

std::optional<bvariant> __house_model_property(int level, pcstr property) {
    return archive_helper::get(building_house::get_model(level), xstring(property), true);
}
ANK_FUNCTION_2(__house_model_property)

void house_proto_get_inventory(js_State *J) {
    const int bid = house_this_id(J);
    const int index = J->to<int>(1);
    building_house* house = house_from_bid(bid);
    const int value = (!house || index < 0 || index >= 4) ? 0 : house->runtime_data().inventory[index + INVENTORY_MIN_GOOD];
    J->push(value);
}

/* ---- House JS object (inherits Building.prototype, like js_register_building) ---- */

static js_Object *g_house_proto = nullptr;

static void house_proto___property_getter(js_State *J) {
    const int bid = house_this_id(J);
    xstring prop = js_toxstring(J, 1);
    auto opt = __house_get_property(bid, prop);
    J->push<std::optional<bvariant>>(opt);
}

static void house_proto___population_room(js_State *J) {
    const int bid = house_this_id(J);
    building_house* house = house_from_bid(bid);
    const int value = (!house) ? 0 : house->population_room();
    J->push(value);
}

static void house_proto___is_vacant_lot(js_State *J) {
    const int bid = house_this_id(J);
    building_house* house = house_from_bid(bid);
    const bool value = (!house) ? false : house->is_vacant_lot();
    J->push(value);
}

static void house_proto_get_food(js_State *J) {
    const int bid = house_this_id(J);
    const int index = J->to<int>(1);
    building_house* house = house_from_bid(bid);
    const int value = (!house || index < 0 || index >= 8) ? 0 : house->runtime_data().foods[index];
    J->push(value);
}

static void house_proto_set_food(js_State *J) {
    const int bid = house_this_id(J);
    const int index = J->to<int>(1);
    building_house* house = house_from_bid(bid);
    if (house && index >= 0 && index < 8) {
        const int amount = J->to<int>(2);
        house->runtime_data().foods[index] = (uint16_t)(amount < 0 ? 0 : amount);
    }
    js_helpers::js_push_void(J);
}

static void house_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "House(%d)", house_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_House(js_State *J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    building *b = building_get(id);
    if (!b || !b->is_valid() || !b->is_house()) {
        js_pushnull(J);
        return;
    }
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_house_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_house(js_State *J) {
    js_Object *building_proto = js_get_building_prototype();
    g_house_proto = jsV_newobject(J, JS_COBJECT, building_proto);
    js_pushobject(J, g_house_proto);

    jsB_propf(J, js_intern("House.prototype.__property_getter"), house_proto___property_getter, 1);
    jsB_propf(J, js_intern("House.prototype.__population_room"), house_proto___population_room, 0);
    jsB_propf(J, js_intern("House.prototype.__house_level"), house_proto___house_level, 0);
    jsB_propf(J, js_intern("House.prototype.__is_vacant_lot"), house_proto___is_vacant_lot, 0);
    jsB_propf(J, js_intern("House.prototype.get_inventory"), house_proto_get_inventory, 1);
    jsB_propf(J, js_intern("House.prototype.get_food"), house_proto_get_food, 1);
    jsB_propf(J, js_intern("House.prototype.set_food"), house_proto_set_food, 2);
    jsB_propf(J, js_intern("House.prototype.inv"), house_proto_get_inventory, 1);
    jsB_propf(J, js_intern("House.prototype.toString"), house_proto_toString, 0);

    J->newcconstructor(jsB_new_House, jsB_new_House, js_intern("House"), 1);
    js_defglobal(J, js_intern("House"), JS_DONTENUM);
}