#include "scenario/distant_battle.h"

#include "js/js_game.h"
#include "core/profiler.h"

bool __empire_has_distant_battle() { return g_distant_battle.has_distant_battle() != 0; }
ANK_FUNCTION(__empire_has_distant_battle)

int __distant_battle_army_path_length() {
    if (!g_distant_battle.has_distant_battle()) {
        return 0;
    }
    const army_path& p = g_distant_battle.get_path();
    return static_cast<int>(p.size());
}
ANK_FUNCTION(__distant_battle_army_path_length)

vec2i __distant_battle_army_path_point(int index) {
    if (!g_distant_battle.has_distant_battle()) {
        return {0, 0};
    }
    const army_path& p = g_distant_battle.get_path();
    if (index < 0 || index >= static_cast<int>(p.size())) {
        return {0, 0};
    }
    return p[index];
}
ANK_FUNCTION_1(__distant_battle_army_path_point)

std::optional<bvariant> __game_get_active_battle_property(pcstr property) {
    return archive_helper::get(g_distant_battle.battle, property, true);
}
ANK_FUNCTION_1(__game_get_active_battle_property)

std::optional<bvariant> __empire_get_dispatched_army_property(pcstr property) {
    return archive_helper::get(g_distant_battle.dispatched_army, property, true);
}
ANK_FUNCTION_1(__empire_get_dispatched_army_property)