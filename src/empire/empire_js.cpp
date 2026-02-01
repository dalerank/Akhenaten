#include "empire/empire.h"
#include "empire/empire_city.h"
#include "city/city.h"
#include "scenario/distant_battle.h"

#include "js/js_game.h"

std::optional<bvariant> __empire_get_city_object_property(int cid, pcstr property) {
    const auto *empire_city = g_empire.city(cid);
    if (!empire_city) {
        return {};
    }

    const auto *empire_obj = empire_city->get_empire_object();
    verify_no_crash(empire_obj && "empire_obj should exist");

    return archive_helper::get(*empire_obj, property, true);
}
ANK_FUNCTION_2(__empire_get_city_object_property)

std::optional<bvariant> __empire_get_ourcity_property(pcstr property) {
    const auto *ourcity_obj = g_empire.ourcity_object();
    if (!ourcity_obj) {
        return {};
    }
    
    verify_no_crash(ourcity_obj && "empire_obj should exist");
    return archive_helper::get(*ourcity_obj, property, true);
}
ANK_FUNCTION_1(__empire_get_ourcity_property)

void js_register_empire_objects(js_State *J) {
}