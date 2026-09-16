#include "figure/enemy_army.h"
#include "figure/formation.h"

#include "js/js_game.h"
#include "js/js.h"
#include "js/js_mujs_bound_offset.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"
#include "mujs/mujs.h"
#include "core/hvector.h"
#include "core/profiler.h"

#include <cstdio>

int __enemy_armies_max() {
    return enemy_armies_t::MAX_ENEMY_ARMIES;
}
ANK_FUNCTION(__enemy_armies_max)

hvector<int, 32> __enemy_army_battalion_ids(int army_id) {
    hvector<int, 32> ids;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && !m->is_herd && !m->own_batalion && m->invasion_id == army_id) {
            ids.push_back(m->id);
        }
    }
    return ids;
}
ANK_FUNCTION_1(__enemy_army_battalion_ids)

static js_Object *g_enemy_army_proto = nullptr;

static int enemy_army_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("invasion_id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static enemy_army *enemy_army_this(js_State *J) {
    const int id = enemy_army_this_id(J);
    if (id < 0 || id >= enemy_armies_t::MAX_ENEMY_ARMIES) {
        return nullptr;
    }
    return &g_enemy_armies.data[id];
}

static void js_push_enemy_army(js_State *J, int invasion_id) {
    if (invasion_id < 0 || invasion_id >= enemy_armies_t::MAX_ENEMY_ARMIES) {
        js_pushnull(J);
        return;
    }

    enemy_army *army = &g_enemy_armies.data[invasion_id];
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_enemy_army_proto));
    js_pushnumber(J, (double)invasion_id);
    js_setproperty(J, -2, js_intern("invasion_id"));
    js_register_cobj_ptr_property(J, army);
}

static void enemy_army_proto_home(js_State *J) {
    enemy_army *army = enemy_army_this(J);
    js_helpers::js_push_value<tile2i>(J, army ? army->home : tile2i{});
}

static void enemy_army_proto_destination(js_State *J) {
    enemy_army *army = enemy_army_this(J);
    js_helpers::js_push_value<tile2i>(J, army ? army->destination : tile2i{});
}

static void enemy_army_proto_battalion_ids(js_State *J) {
    enemy_army *army = enemy_army_this(J);
    js_helpers::js_push_value(J, __enemy_army_battalion_ids(army ? army->army_id : -1));
}

static void enemy_army_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "EnemyArmy(%d)", enemy_army_this_id(J));
    J->pushstring(buf);
}

static void enemy_army_set_readonly(js_State *J) {
    (void)J;
}

static void def_readonly_prop(js_State *J, js_CFunction get, const char *name) {
    J->newcfunction(get, js_intern(""), 0);
    J->newcfunction(enemy_army_set_readonly, js_intern(""), 1);
    js_defaccessor(J, -3, js_intern(name), 0);
}

static void jsB_new_EnemyArmy(js_State *J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_enemy_army(J, id);
}

void js_register_enemy_army(js_State *J) {
    g_enemy_army_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_enemy_army_proto);

    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, army_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, formation_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, layout);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, destination_building_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, num_batalions);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, ignore_pharaoh_soldiers);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, buildings_to_destroy);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, enemy_army, buildings_destroyed);

    def_readonly_prop(J, enemy_army_proto_home, "home");
    def_readonly_prop(J, enemy_army_proto_destination, "destination");

    jsB_propf(J, js_intern("EnemyArmy.prototype.battalion_ids"), enemy_army_proto_battalion_ids, 0);
    jsB_propf(J, js_intern("EnemyArmy.prototype.toString"), enemy_army_proto_toString, 0);

    J->newcconstructor(jsB_new_EnemyArmy, jsB_new_EnemyArmy, js_intern("EnemyArmy"), 1);
    js_defglobal(J, js_intern("EnemyArmy"), JS_DONTENUM);
}
