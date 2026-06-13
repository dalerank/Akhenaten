#include "building.h"
#include "building_static_params.h"

#include "building/building_bazaar.h"
#include "building/building_dock.h"
#include "building/building_entertainment.h"
#include "building/building_farm.h"
#include "building/building_granary.h"
#include "building/building_roadblock.h"
#include "building/building_storage_yard.h"
#include "building/building_temple_complex.h"
#include "building_mansion.h"
#include "city/city_buildings.h"
#include "grid/building.h"
#include "grid/road_access.h"
#include "core/bstring.h"
#include "core/profiler.h"
#include "figure/figure.h"
#include "figure/action.h"
#include "js/js_game.h"
#include "mujs/mujs.h"
#include "mujs/jsvalue.h"
#include "mujs/jsbuiltin.h"

#include <cstdio>
#include <cstring>

#include "game/game_events.h"

static int building_this_id(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

bool __building_is_valid(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid();
}
ANK_FUNCTION_1(__building_is_valid)

bool __building_is_bazaar(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_bazaar();
}
ANK_FUNCTION_1(__building_is_bazaar)

bool __building_is_granary(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_granary();
}
ANK_FUNCTION_1(__building_is_granary)

bool __building_is_dock(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_dock();
}
ANK_FUNCTION_1(__building_is_dock)

bool __building_is_roadblock(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_roadblock();
}
ANK_FUNCTION_1(__building_is_roadblock)

bool __building_is_entertainment(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_entertainment();
}
ANK_FUNCTION_1(__building_is_entertainment)

bool __building_is_farm(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->dcast_farm();
}
ANK_FUNCTION_1(__building_is_farm)

bool __building_is_monument(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && b->is_monument();
}
ANK_FUNCTION_1(__building_is_monument)

bool __building_is_storage_yard(int bid) {
    building *b = building_get(bid);
    return b && b->is_valid() && storage_yard_cast(b);
}
ANK_FUNCTION_1(__building_is_storage_yard)

bool __building_is_temple_complex(int bid) {
    return !!building_get_ex<building_temple_complex>(bid);
}
ANK_FUNCTION_1(__building_is_temple_complex)

bool __building_is_protected_by_police(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return false;
    }
    return b->dcast()->is_protected_by_police();
}
ANK_FUNCTION_1(__building_is_protected_by_police)

int __building_first_material_stored(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    const e_resource resource = b->input.resource;
    if (resource == RESOURCE_NONE) {
        return 0;
    }
    return b->stored_amount(resource);
}
ANK_FUNCTION_1(__building_first_material_stored)

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

void __building_des_influence_range_j(js_State* J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, building_get(bid)->des_influence.range);
}

void __building_crime_influence_value_j(js_State* J) {
    const int bid = building_this_id(J);
    building *b = building_get(bid);
    js_helpers::js_push_value(J, b ? b->crime_influence.value : 0);
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

void __building_get_output_resource_id(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, (int)building_get(bid)->output.resource);
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

void __building_get_valid(js_State *J) {
    const int bid = building_this_id(J);
    js_helpers::js_push_value(J, __building_is_valid(bid));
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

void __building_common_spawn_figure_trigger(js_State *J) {
    const int bid = building_this_id(J);
    const int min_houses = js_helpers::js_to_value<int>(J, 1);
    const int slot = js_helpers::js_to_value<int>(J, 2);
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        js_helpers::js_push_value(J, false);
        return;
    }

    js_helpers::js_push_value(J, b->dcast()->common_spawn_figure_trigger(min_houses, (e_building_slot)slot));
}

void __building_create_figure_with_destination(js_State *J) {
    const int bid = building_this_id(J);
    const int figure_type = js_helpers::js_to_value<int>(J, 1);
    const int dest_bid = js_helpers::js_to_value<int>(J, 2);
    const int action = js_helpers::js_to_value<int>(J, 3);
    const int slot = js_helpers::js_to_value<int>(J, 4);
    building *b = building_get(bid);
    building *dest = building_get(dest_bid);
    if (!b || !b->is_valid() || !dest || !dest->is_valid()) {
        js_helpers::js_push_value(J, 0);
        return;
    }

    figure *f = b->dcast()->create_figure_with_destination((e_figure_type)figure_type, dest, (e_figure_action)action, (e_building_slot)slot);
    js_helpers::js_push_value(J, f ? f->id : 0);
}

void __building_add_workers(js_State *J) {
    const int bid = building_this_id(J);
    const int worker_figure_id = js_helpers::js_to_value<int>(J, 1);
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        js_helpers::js_push_void(J);
        return;
    }

    b->dcast()->add_workers((figure_id)worker_figure_id);
    js_helpers::js_push_void(J);
}

static void building_proto___property_setter(js_State *J) {
    const int bid = building_this_id(J);
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }

    pcstr prop = js_strnode_cstr(js_tostring(J, 1));
    const int value = (int)js_tointeger(J, 2);
    if (!strcmp(prop, "spawned_worker_this_month")) {
        b->spawned_worker_this_month = (uint8_t)value;
    }
}

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

void __building_destroy_by_fire(js_State *J) {
    const int bid = building_this_id(J);
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->main()->destroy_by_fire();
    }
    js_helpers::js_push_void(J);
}

tile2i __building_tile(int bid) {
    building* b = building_get(bid);
    return b->tile;
}
ANK_FUNCTION_1(__building_tile)

xstring __building_display_name(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return {};
    }
    return b->cls_name();
}
ANK_FUNCTION_1(__building_display_name)

pcstr __building_static_text(int type, pcstr field) {
    const auto &params = building_static_params::get((e_building_type)type);
    if (!strcmp(field, "build_menu_text")) {
        return params.build_menu_text.c_str();
    }
    if (!strcmp(field, "info_title_id")) {
        return params.info_title_id.c_str();
    }
    return "";
}
ANK_FUNCTION_2(__building_static_text)

void __building_tile_j(js_State *J) {
    const int bid = building_this_id(J);
    building* b = building_get(bid);
    js_helpers::js_push_value(J, b->tile);
}

pcstr __building_static_config_name(int type) {
    return building_static_params::get((e_building_type)type).name;
}
ANK_FUNCTION_1(__building_static_config_name)

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

int building_static_first_img_for_type(int type, xstring anim_key);
static void building_proto_first_img(js_State *J) {
    const int bid = building_this_id(J);
    building *b = building_get(bid);
    const xstring anim_key = js_helpers::js_to_value<xstring>(J, 1);
    js_helpers::js_push_value(J, b ? building_static_first_img_for_type(b->type, anim_key) : 0);
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
    jsB_propf(J, js_intern("Building.prototype.__valid"), __building_get_valid, 0);
    jsB_propf(J, js_intern("Building.prototype.__worker_percentage"), __building_get_worker_percentage, 0);
    jsB_propf(J, js_intern("Building.prototype.__output_resource_id"), __building_get_output_resource_id, 0);
    jsB_propf(J, js_intern("Building.prototype.__overlay"), __building_get_overlay, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_value"), __building_des_influence_value_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_step_size"), __building_des_influence_step_size_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__des_influence_range"), __building_des_influence_range_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__crime_influence_value"), __building_crime_influence_value_j, 0);
    jsB_propf(J, js_intern("Building.prototype.__property_getter"), building_proto___property_getter, 1);
    jsB_propf(J, js_intern("Building.prototype.__property_setter"), building_proto___property_setter, 2);
    jsB_propf(J, js_intern("Building.prototype.__can_play_animation"), __building_can_play_animation, 0);

    jsB_propf(J, js_intern("Building.prototype.has_figure"), __building_has_figure, 1);
    jsB_propf(J, js_intern("Building.prototype.mothball_toggle"), __building_mothball_toggle, 0);
    jsB_propf(J, js_intern("Building.prototype.add_structure_damage"), __building_add_structure_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.add_fire_damage"), __building_add_fire_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.add_collapse_damage"), __building_add_collapse_damage, 1);
    jsB_propf(J, js_intern("Building.prototype.destroy_by_fire"), __building_destroy_by_fire, 0);
    jsB_propf(J, js_intern("Building.prototype.stored_resource"), __building_stored_resource, 1);
    jsB_propf(J, js_intern("Building.prototype.set_animation"), __building_set_animation, 1);
    jsB_propf(J, js_intern("Building.prototype.common_spawn_roamer"), __building_common_spawn_roamer, 3);
    jsB_propf(J, js_intern("Building.prototype.common_spawn_figure_trigger"), __building_common_spawn_figure_trigger, 2);
    jsB_propf(J, js_intern("Building.prototype.create_figure_with_destination"), __building_create_figure_with_destination, 4);
    jsB_propf(J, js_intern("Building.prototype.add_workers"), __building_add_workers, 1);
    jsB_propf(J, js_intern("Building.prototype.first_img"), building_proto_first_img, 1);

    jsB_propf(J, js_intern("Building.prototype.toString"), building_proto_toString, 0);

    js_newcconstructor(J, jsB_new_Building, jsB_new_Building, js_intern("Building"), 1);
    js_defglobal(J, js_intern("Building"), JS_DONTENUM);
}

js_Object *js_get_building_prototype(void) {
    return g_building_proto;
}