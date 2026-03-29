#include "scenario/distant_battle.h"

#include "empire/empire.h"
#include "empire/type.h"
#include "js/js_game.h"
#include "core/log.h"
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

void __distant_battle_cheat_setup_test(int enemy_strength, int city_id) {
    g_distant_battle.dispatched_army.clear();
    g_distant_battle.battle.clear();

    int cid = city_id;
    if (cid <= 0) {
        g_distant_battle.determine_distant_battle_city();
        cid = g_distant_battle.battle.city;
    }

    empire_city* picked = g_empire.city(cid);
    if (!picked || !picked->in_use || !picked->get_empire_object()) {
        cid = 0;
        for (int i = 0; i < empire_t::MAX_CITIES; i++) {
            empire_city* c = g_empire.city(i);
            if (c && c->in_use && c->get_empire_object()
                && (c->type == EMPIRE_CITY_FOREIGN || c->type == EMPIRE_CITY_FOREIGN_TRADING)) {
                cid = i;
                break;
            }
        }
    }

    if (cid <= 0) {
        logs::info("distant_battle_test: no foreign empire city with map object");
        return;
    }

    g_distant_battle.battle.city = static_cast<uint8_t>(cid);
    g_distant_battle.init_distant_battle(enemy_strength > 0 ? enemy_strength : 50);
    logs::info("distant_battle_test: city_id=%d enemy_strength=%d", cid,
      enemy_strength > 0 ? enemy_strength : 50);
}
ANK_FUNCTION_2(__distant_battle_cheat_setup_test)

std::optional<bvariant> __game_get_active_battle_property(pcstr property) {
    return archive_helper::get(g_distant_battle.battle, property, true);
}
ANK_FUNCTION_1(__game_get_active_battle_property)

std::optional<bvariant> __empire_get_dispatched_army_property(pcstr property) {
    return archive_helper::get(g_distant_battle.dispatched_army, property, true);
}
ANK_FUNCTION_1(__empire_get_dispatched_army_property)