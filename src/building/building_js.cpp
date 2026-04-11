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

static int building_this_id(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

bool __building_is_valid(int bid) {
    return building_get(bid)->is_valid();
}
ANK_FUNCTION_1(__building_is_valid)

int __building_des_influence_value(int bid) {
    return (int)building_get(bid)->des_influence.value;
}
ANK_FUNCTION_1(__building_des_influence_value)

void __building_des_influence_value_j(js_State* J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, (int)building_get(bid)->des_influence.value);
}

int __building_des_influence_step_size(int bid) {
    return building_get(bid)->des_influence.step_size;
}
ANK_FUNCTION_1(__building_des_influence_step_size)

void __building_des_influence_step_size_j(js_State* J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, building_get(bid)->des_influence.step_size);
}

int __building_des_influence_range(int bid) {
    building* b = building_get(bid);
    return b ? b->des_influence.range : 0;
}
ANK_FUNCTION_1(__building_des_influence_range)

void __building_des_influence_range_j(js_State* J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, building_get(bid)->des_influence.range);
}

void __building_stored_resource(js_State* J) {
    const int bid = building_this_id(J);
    const int resource = js_helpers::js_to_value<int>(J, 1);
    js_helpers::js_push_value(J, building_get(bid)->stored_amount((e_resource)resource));
}

void __building_get_overlay(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value<int>(J, building_get(bid)->get_overlay());
}

void __building_get_worker_percentage(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, building_get(bid)->worker_percentage());
}

void __building_has_figure(js_State *J) {
    const int bid = building_this_id(J);
    const int index = js_helpers::js_to_value<int>(J, 1);
    js_helpers::js_push_value(J, building_get(bid)->has_figure(index));
}

int __building_get_figure_id(int bid, int index) {
    return building_get(bid)->get_figure(index)->id;
}
ANK_FUNCTION_2(__building_get_figure_id)

void __building_get_state(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, (int)building_get(bid)->state);
}

void __building_mothball_toggle(js_State *J) {
    const int bid = building_this_id(J);
    building* b = building_get(bid);
    js_helpers::js_push_value(J, b->max_workers ? b->mothball_toggle() : 0);
}

void __building_can_play_animation(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, building_get(bid)->dcast()->can_play_animation());
}

void __building_set_animation(js_State *J) {
    const int bid = building_this_id(J);
    const char *animkey = js_helpers::js_to_value<const char *>(J, 1);
    building_get(bid)->dcast()->set_animation(xstring(animkey));
    js_helpers::js_push_void(J);
}

void __building_common_spawn_roamer(js_State *J) {
    const int bid = building_this_id(J);
    const int figure_type = js_helpers::js_to_value<int>(J, 1);
    const int min_houses_coverage = js_helpers::js_to_value<int>(J, 2);
    const int action = js_helpers::js_to_value<int>(J, 3);
    bool result = building_get(bid)->dcast()->common_spawn_roamer((e_figure_type)figure_type, min_houses_coverage, (e_figure_action)action);
    js_helpers::js_push_value(J, result);
}

std::optional<bvariant> __building_get_params_property(int bid, pcstr property) {
    return archive_helper::get(building_get(bid)->params(), property, true);
}
ANK_FUNCTION_2(__building_get_params_property)

void __building_meta_text_id(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value<int>(J, building_get(bid)->params().meta.text_id);
}

void __building_add_fire_damage(js_State *J) {
    const int bid = building_this_id(J);
    const int damage = js_helpers::js_to_value<int>(J, 1);
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_fire, damage);
    }
    js_helpers::js_push_void(J);
}

void __building_add_collapse_damage(js_State *J) {
    const int bid = building_this_id(J);
    const int damage = js_helpers::js_to_value<int>(J, 1);
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_collapse, damage);
    }
    js_helpers::js_push_void(J);
}

void __building_add_structure_damage(js_State* J) {
    const int bid = building_this_id(J);
    building *b = building_get(bid);
    const int damage = js_helpers::js_to_value<int>(J, 1);
    b->force_damage(e_damage_enemy, damage);
    js_helpers::js_push_void(J);
}

tile2i __building_tile(int bid) {
    building* b = building_get(bid);
    return b->tile;
}
ANK_FUNCTION_1(__building_tile)

void __building_tile_j(js_State *J) {
    const int bid = building_this_id(J);
    building* b = building_get(bid);
    js_helpers::js_push_value(J, b->tile);
}

bool __map_road_within_radius(tile2i tile, int size, int radius) {
    return map_closest_road_within_radius(tile, size, radius).valid();
}
ANK_FUNCTION_3(__map_road_within_radius)

static js_Object *g_building_proto = nullptr;

static void building_proto___property_getter(js_State *J) {
    const int bid = building_this_id(J);
    pcstr prop = js_strnode_cstr(js_tostring(J, 1));
    auto opt = archive_helper::get(*building_get(bid), prop, true);
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

    jsB_propf(J, js_intern("Building.prototype.__tile"), __building_tile_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__meta_text_id"), __building_meta_text_id, 0);
    jsB_propf(J, js_intern("Building.prototype.__state"), __building_get_state, 0);
    jsB_propf(J, js_intern("Building.prototype.__worker_percentage"), __building_get_worker_percentage, 0);
    jsB_propf(J, js_intern("Building.prototype.__overlay"), __building_get_overlay, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_value"), __building_des_influence_value_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_step_size"), __building_des_influence_step_size_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_range"), __building_des_influence_range_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__property_getter"), building_proto___property_getter, 1);
    jsB_propf(J, js_intern("Building.prototype.__can_play_animation"), __building_can_play_animation, 0);

    jsB_propf(J, js_intern("Building.prototype.has_figure"), __building_has_figure, 1);
    jsB_propf(J, js_intern("Building.prototype.mothball_toggle"), __building_mothball_toggle, 0);
    jsB_propf(J, js_intern("Building.prototype.add_structure_damage"), __building_add_structure_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.add_fire_damage"), __building_add_fire_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.add_collapse_damage"), __building_add_collapse_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.stored_resource"), __building_stored_resource, 1);
    jsB_propf(J, js_intern("Building.prototype.set_animation"), __building_set_animation, 1);
    jsB_propf(J, js_intern("Building.prototype.common_spawn_roamer"), __building_common_spawn_roamer, 3);

    jsB_propf(J, js_intern("Building.prototype.toString"), building_proto_toString, 0);

    js_newcconstructor(J, jsB_new_Building, jsB_new_Building, js_intern("Building"), 1);
    js_defglobal(J, js_intern("Building"), JS_DONTENUM);
}

js_Object *js_get_building_prototype(void) {
    return g_building_proto;
}