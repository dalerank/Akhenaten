#include "empire/empire.h"
#include "empire/empire_city.h"
#include "city/city.h"
#include "scenario/distant_battle.h"

#include "js/js_game.h"

bool __empire_has_distant_battle() { return g_city.distant_battle.has_distant_battle() != 0; }
ANK_FUNCTION(__empire_has_distant_battle)

int __empire_distant_battle_city() { return g_city.distant_battle.battle_city(); }
ANK_FUNCTION(__empire_distant_battle_city)

void __empire_get_city_empire_object(js_State *J) {
    if (js_gettop(J) < 1) {
        js_pushnull(J);
        return;
    }

    if (!js_isnumber(J, 1)) {
        js_pushnull(J);
        return;
    }

    int cid = js_touint32(J, 1);
    if (!cid) {
        js_pushnull(J);
        return;
    }

    const auto *empire_city = g_empire.city(cid);
    if (!empire_city) {
        js_pushnull(J);
        return;
    }

    const auto *empire_obj = empire_city->get_empire_object();
    verify_no_crash(empire_obj && "empire_obj should exist");

    js_newobject(J); {
        js_newobject(J); {
            js_pushnumber(J, empire_obj->pos.x);
            js_setproperty(J, -2, "x");
            js_pushnumber(J, empire_obj->pos.y);
            js_setproperty(J, -2, "y");
        }
        js_setproperty(J, -2, "pos");
    }
}

void js_register_empire_objects(js_State *J) {
    REGISTER_GLOBAL_FUNCTION(J, __empire_get_city_empire_object, "__empire_get_city_empire_object", 1);
}