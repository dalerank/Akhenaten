#include "scenario/distant_battle.h"

#include "js/js_game.h"

bool __empire_has_distant_battle() { return g_distant_battle.has_distant_battle() != 0; }
ANK_FUNCTION(__empire_has_distant_battle)

std::optional<bvariant> __game_get_active_battle_property(pcstr property) {
    return archive_helper::get(g_distant_battle.battle, property, true);
}
ANK_FUNCTION_1(__game_get_active_battle_property)

std::optional<bvariant> __empire_get_dispatched_army_property(pcstr property) {
    return archive_helper::get(g_distant_battle.dispatched_army, property, true);
}
ANK_FUNCTION_1(__empire_get_dispatched_army_property)