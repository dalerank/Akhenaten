#include "building.h"

#include "grid/building.h"
#include "grid/road_access.h"
#include "core/profiler.h"
#include "figure/figure.h"
#include "js/js_game.h"
#include "mujs/mujs.h"
#include "mujs/jsvalue.h"
#include "mujs/jsbuiltin.h"

#include <cstdio>

#include "game/game_events.h"

bool __building_is_valid(int bid) {
    return building_get(bid)->is_valid();
}
ANK_FUNCTION_1(__building_is_valid)

int __building_des_influence_value(int bid) {
    return (int)building_get(bid)->des_influence.value;
}
ANK_FUNCTION_1(__building_des_influence_value)

int __building_des_influence_step_size(int bid) {
    return building_get(bid)->des_influence.step_size;
}
ANK_FUNCTION_1(__building_des_influence_step_size)

int __building_des_influence_range(int bid) {
    return building_get(bid)->des_influence.range;
}
ANK_FUNCTION_1(__building_des_influence_range)

int __building_stored_resource(int bid, int resource) {
    return building_get(bid)->stored_amount((e_resource)resource);
}
ANK_FUNCTION_2(__building_stored_resource)

int __building_get_overlay(int bid) {
    return building_get(bid)->get_overlay();
}
ANK_FUNCTION_1(__building_get_overlay)

int __building_get_worker_percentage(int bid) {
    return building_get(bid)->worker_percentage();
}
ANK_FUNCTION_1(__building_get_worker_percentage)

bool __building_has_figure(int bid, int index) {
    return building_get(bid)->has_figure(index);
}
ANK_FUNCTION_2(__building_has_figure)

int __building_get_figure_id(int bid, int index) {
    return building_get(bid)->get_figure(index)->id;
}
ANK_FUNCTION_2(__building_get_figure_id)

int __building_get_state(int bid) {
    return (int)building_get(bid)->state;
}
ANK_FUNCTION_1(__building_get_state)

int __building_mothball_toggle(int bid) {
    building* b = building_get(bid);
    return b->max_workers ? b->mothball_toggle() : 0;
}
ANK_FUNCTION_1(__building_mothball_toggle)

bool __building_can_play_animation(int bid) {
    return building_get(bid)->dcast()->can_play_animation();
}
ANK_FUNCTION_1(__building_can_play_animation)

void __building_set_animation(int bid, pcstr animkey) {
    building_get(bid)->dcast()->set_animation(animkey);
}
ANK_FUNCTION_2(__building_set_animation)

bool __building_common_spawn_roamer(int bid, int figure_type, int min_houses_coverage, int action) {
    return building_get(bid)->dcast()->common_spawn_roamer((e_figure_type)figure_type, min_houses_coverage, (e_figure_action)action);
}
ANK_FUNCTION_4(__building_common_spawn_roamer)

std::optional<bvariant> __building_get_property(int bid, pcstr property) {
    return archive_helper::get(*building_get(bid), property, true);
}
ANK_FUNCTION_2(__building_get_property)

std::optional<bvariant> __building_get_params_property(int bid, pcstr property) {
    return archive_helper::get(building_get(bid)->params(), property, true);
}
ANK_FUNCTION_2(__building_get_params_property)

int __building_meta_text_id(int bid) {
    return building_get(bid)->params().meta.text_id;
}
ANK_FUNCTION_1(__building_meta_text_id)

void __building_add_fire_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_fire, damage);
    }
}
ANK_FUNCTION_2(__building_add_fire_damage)

void __building_add_collapse_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_collapse, damage);
    }
}
ANK_FUNCTION_2(__building_add_collapse_damage)

void __building_add_structure_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_enemy, damage);
    }
}
ANK_FUNCTION_2(__building_add_structure_damage)

int __map_rubble_building_type(int bid) {
    building *b = building_get(bid);
    return b ? map_rubble_building_type(b->tile.grid_offset()) : 0;
}
ANK_FUNCTION_1(__map_rubble_building_type)

tile2i __building_tile(int bid) {
    building* b = building_get(bid);
    return b ? b->tile : tile2i::invalid;
}
ANK_FUNCTION_1(__building_tile)

bool __map_road_within_radius(tile2i tile, int size, int radius) {
    return map_closest_road_within_radius(tile, size, radius).valid();
}
ANK_FUNCTION_3(__map_road_within_radius)

static js_Object *g_building_proto = nullptr;

static int building_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static void building_proto___property_getter(js_State *J) {
    const int bid = building_this_id(J);
    pcstr prop = js_strnode_cstr(js_tostring(J, 1));
    auto opt = __building_get_property(bid, prop);
    js_helpers::js_push_value<std::optional<bvariant>>(J, opt);
}

static void building_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "Building(%d)", building_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_Building(js_State *J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_building_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_building(js_State *J) {
    g_building_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_building_proto);

    jsB_propf(J, js_intern("Building.prototype.toString"), building_proto_toString, 0);

    jsB_propf(J, js_intern("Building.prototype.__property_getter"), building_proto___property_getter, 1);

    js_newcconstructor(J, jsB_new_Building, jsB_new_Building, js_intern("Building"), 1);
    js_defglobal(J, js_intern("Building"), JS_DONTENUM);
}