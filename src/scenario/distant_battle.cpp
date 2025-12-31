#include "distant_battle.h"

#include "city/buildings.h"
#include "city/map.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/military.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/type.h"
#include "figure/formation_batalion.h"
#include "game/game.h"
#include "empire/empire.h"
#include "city/city.h"
#include "scenario/scenario.h"

distant_battles_t g_distant_battle;

void distant_battles_t::clear() {
    memset(&g_distant_battle, 0, sizeof(distant_battles_t));
}

int scenario_distant_battle_kingdome_travel_months() {
    return g_scenario.empire.distant_battle_kingdome_travel_months;
}

int scenario_distant_battle_enemy_travel_months() {
    return g_scenario.empire.distant_battle_enemy_travel_months;
}

void distant_battles_t::process() {
    if (!has_distant_battle()) {
        for (int i = 0; i < MAX_INVASIONS; i++) {
            const bool should_start_battle = g_scenario.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE
                && game.simtime.year == g_scenario.invasions[i].year + g_scenario.start_year
                && game.simtime.month == g_scenario.invasions[i].month
                && g_scenario.empire.distant_battle_enemy_travel_months > 4
                && g_scenario.empire.distant_battle_kingdome_travel_months > 4;

            if (should_start_battle) {
                events::emit(event_message{ true, "message_kingdome_requests_army", 0, 0 });
                g_distant_battle.init_distant_battle(g_scenario.invasions[i].amount);
                return;
            }
        }
    }

    process_distant_battle_impl();
}

void distant_battles_t::determine_distant_battle_city() {
    battle.city = g_empire.get_city_vulnerable();
}

bool distant_battles_t::city_is_egyptian() {
    return battle.city_foreign_months_left <= 0;
}

int distant_battles_t::kingdome_army_is_traveling() {
    return battle.egyptian_months_to_travel_forth > 0 || battle.egyptian_months_to_travel_back > 0;
}

int distant_battles_t::enemy_months_traveled() {
    return battle.egyptian_months_traveled;
}

void distant_battles_t::init_distant_battle(int enemy_strength) {
    battle.enemy_months_traveled = 1;
    battle.egyptian_months_traveled = 1;
    battle.months_until_battle = 24;
    battle.enemy_strength = enemy_strength;
    battle.total_count++;
    battle.egyptian_months_to_travel_back = 0;
    battle.egyptian_months_to_travel_forth = 0;
}

int distant_battles_t::has_distant_battle() {
    return battle.months_until_battle > 0
        || battle.egyptian_months_to_travel_back > 0
        || battle.egyptian_months_to_travel_forth > 0
        || battle.city_foreign_months_left > 0;
}

void distant_battles_t::process_distant_battle_impl() {
    if (battle.months_until_battle > 0) {
        --battle.months_until_battle;
        if (battle.months_until_battle > 0)
            update_time_traveled();
        else {
            fight_distant_battle();
        }
    } else {
        update_aftermath();
    }
}

void distant_battles_t::set_city_vulnerable() {
    if (battle.city) {
        g_empire.city(battle.city)->set_vulnerable();
    }
}

int distant_battles_t::enemy_strength() {
    return battle.enemy_strength;
}

void distant_battles_t::update_aftermath() {
    if (battle.egyptian_months_to_travel_back > 0) {
        battle.egyptian_months_to_travel_back--;
        battle.egyptian_months_traveled = battle.egyptian_months_to_travel_back;
        if (battle.egyptian_months_to_travel_back <= 0) {
            if (battle.city_foreign_months_left) {
                // soldiers return - not in time
                events::emit(event_message{ true, "message_troops_return_failed", 0, g_city.map.exit_point.grid_offset() });
            } else {
                // victorious
                events::emit(event_message{ true, "message_troops_return_victorious", 0, g_city.map.exit_point.grid_offset() });
            }
            battle.egyptian_months_traveled = 0;
            formation_batalions_return_from_distant_battle();
        }
    } else if (battle.city_foreign_months_left > 0) {
        battle.city_foreign_months_left--;
        if (battle.city_foreign_months_left <= 0) {
            events::emit(event_message{ true, "message_city_retaken", 0, 0 });
            set_city_vulnerable();
        }
    }
}

void distant_battles_t::set_city_foreign() {
    if (battle.city) {
        g_empire.city(battle.city)->set_foreign();
    }

    battle.city_foreign_months_left = 24;
}

bool distant_battles_t::player_has_won() {
    bool won;
    int pct_loss;
    if (battle.egyptian_strength < battle.enemy_strength) {
        won = 0;
        pct_loss = 100;
    } else {
        won = 1;
        int pct_advantage = calc_percentage<int>(battle.egyptian_strength - battle.enemy_strength, battle.egyptian_strength);

        if (pct_advantage < 10)
            pct_loss = 70;
        else if (pct_advantage < 25)
            pct_loss = 50;
        else if (pct_advantage < 50)
            pct_loss = 25;
        else if (pct_advantage < 75)
            pct_loss = 15;
        else if (pct_advantage < 100)
            pct_loss = 10;
        else if (pct_advantage < 150)
            pct_loss = 5;
        else {
            pct_loss = 0;
        }
    }

    formation_batalions_kill_in_distant_battle(pct_loss);
    return won;
}

void distant_battles_t::fight_distant_battle() {
    if (battle.egyptian_months_to_travel_forth <= 0) {
        events::emit(event_message{ true, "message_distant_battle_lost_no_troops", 0, 0 });
        g_city.kingdome.change(-50);
        set_city_foreign();
    } else if (battle.egyptian_months_to_travel_forth > 2) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_late", 0, 0 });
        g_city.kingdome.change(-25);
        set_city_foreign();
        battle.egyptian_months_to_travel_back = battle.egyptian_months_traveled;
    } else if (!player_has_won()) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_weak", 0, 0 });
        g_city.kingdome.change(-10);
        set_city_foreign();
        battle.egyptian_months_traveled = 0;
        // no return: all soldiers killed
    } else {
        events::emit(event_message{ true, "message_distant_battle_won", 0, 0 });
        g_city.kingdome.change(25);
        city_buildings_earn_triumphal_arch();
        //building_menu_update(BUILDSET_NORMAL);
        battle.won_count++;
        battle.city_foreign_months_left = 0;
        battle.egyptian_months_to_travel_back = battle.egyptian_months_traveled;
    }
    battle.months_until_battle = 0;
    battle.enemy_months_traveled = 0;
    battle.egyptian_months_to_travel_forth = 0;
}

void distant_battles_t::update_time_traveled() {
    int egyptian_travel_months = scenario_distant_battle_kingdome_travel_months();
    int enemy_travel_months = scenario_distant_battle_enemy_travel_months();

    if (battle.months_until_battle < enemy_travel_months) {
        battle.enemy_months_traveled = enemy_travel_months - battle.months_until_battle + 1;
    } else {
        battle.enemy_months_traveled = 1;
    }

    if (battle.egyptian_months_to_travel_forth >= 1) {
        if (egyptian_travel_months - battle.egyptian_months_traveled
    > enemy_travel_months - battle.enemy_months_traveled) {
            battle.egyptian_months_to_travel_forth -= 2;
        } else {
            battle.egyptian_months_to_travel_forth--;
        }

        if (battle.egyptian_months_to_travel_forth <= 1) {
            battle.egyptian_months_to_travel_forth = 1;
        }

        battle.egyptian_months_traveled = egyptian_travel_months - battle.egyptian_months_to_travel_forth + 1;
        if (battle.egyptian_months_traveled < 1) {
            battle.egyptian_months_traveled = 1;
        }

        if (battle.egyptian_months_traveled > egyptian_travel_months) {
            battle.egyptian_months_traveled = egyptian_travel_months;
        }
    }
}

