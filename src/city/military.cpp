#include "military.h"

#include "city/buildings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "figure/formation.h"
#include "figure/formation_batalion.h"
#include "scenario/distant_battle.h"

void city_military_t::clear_infantry_batalions() {
    infantry_batalions = 0;
}

void city_military_t::add_infantry_batalion() {
    infantry_batalions++;
}

bool city_military_t::has_infantry_batalions() {
    return infantry_batalions > 0;
}

void city_military_t::clear_kingdome_service_batalions() {
    kingdome_service_batalions = 0;
}

void city_military_t::update_totals() {
    kingdome_service_batalions = 0;
    total_soldiers = 0;
    infantry_batalions = 0;
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        const formation* m = formation_get(i);
        if (m->in_use && m->batalion_id) {
            infantry_batalions++;
            total_soldiers += m->num_figures;
            if (m->empire_service && m->num_figures > 0) {
                kingdome_service_batalions++;
            }
        }
    }
}

bool city_military_t::is_native_attack_active() {
    return native_attack_duration > 0;
}

void city_military_t::start_native_attack() {
    native_attack_duration = 2;
}

void city_military_t::decrease_native_attack_duration() {
    if (native_attack_duration > 0)
        native_attack_duration--;
}

void city_military_t::determine_distant_battle_city() {
    g_city.distant_battle.battle.city = g_empire.get_city_vulnerable();
}

int city_military_distant_battle_city() {
    return g_city.distant_battle.battle.city;
}

static auto &city_data = g_city;
int city_military_distant_battle_city_is_egyptian() {
    return city_data.distant_battle.battle.city_foreign_months_left <= 0;
}

int city_military_distant_battle_enemy_strength() {
    return city_data.distant_battle.battle.enemy_strength;
}

void city_military_dispatch_to_distant_battle(int roman_strength) {
    city_data.distant_battle.battle.egyptian_months_to_travel_forth = scenario_distant_battle_kingdome_travel_months();
    city_data.distant_battle.battle.egyptian_strength = roman_strength;
}

int city_military_distant_battle_kingdome_army_is_traveling() {
    return city_data.distant_battle.battle.egyptian_months_to_travel_forth > 0
           || city_data.distant_battle.battle.egyptian_months_to_travel_back > 0;
}

int city_military_distant_battle_kingdome_army_is_traveling_forth() {
    return city_data.distant_battle.battle.egyptian_months_to_travel_forth > 0;
}

int city_military_distant_battle_kingdome_army_is_traveling_back() {
    return city_data.distant_battle.battle.egyptian_months_to_travel_back > 0;
}

int city_military_distant_battle_enemy_months_traveled() {
    return city_data.distant_battle.battle.egyptian_months_traveled;
}

int city_military_distant_battle_kingdome_months_traveled() {
    return city_data.distant_battle.battle.egyptian_months_traveled;
}

int city_military_has_distant_battle() {
    return city_data.distant_battle.battle.months_until_battle > 0 || city_data.distant_battle.battle.egyptian_months_to_travel_back > 0
           || city_data.distant_battle.battle.egyptian_months_to_travel_forth > 0
           || city_data.distant_battle.battle.city_foreign_months_left > 0;
}

int city_military_months_until_distant_battle() {
    return city_data.distant_battle.battle.months_until_battle;
}

void city_military_init_distant_battle(int enemy_strength) {
    city_data.distant_battle.battle.enemy_months_traveled = 1;
    city_data.distant_battle.battle.egyptian_months_traveled = 1;
    city_data.distant_battle.battle.months_until_battle = 24;
    city_data.distant_battle.battle.enemy_strength = enemy_strength;
    city_data.distant_battle.battle.total_count++;
    city_data.distant_battle.battle.egyptian_months_to_travel_back = 0;
    city_data.distant_battle.battle.egyptian_months_to_travel_forth = 0;
}

static void update_time_traveled() {
    int roman_travel_months = scenario_distant_battle_kingdome_travel_months();
    int enemy_travel_months = scenario_distant_battle_enemy_travel_months();
    if (city_data.distant_battle.battle.months_until_battle < enemy_travel_months)
        city_data.distant_battle.battle.enemy_months_traveled
          = enemy_travel_months - city_data.distant_battle.battle.months_until_battle + 1;
    else {
        city_data.distant_battle.battle.enemy_months_traveled = 1;
    }
    if (city_data.distant_battle.battle.egyptian_months_to_travel_forth >= 1) {
        if (roman_travel_months - city_data.distant_battle.battle.egyptian_months_traveled
            > enemy_travel_months - city_data.distant_battle.battle.enemy_months_traveled) {
            city_data.distant_battle.battle.egyptian_months_to_travel_forth -= 2;
        } else {
            city_data.distant_battle.battle.egyptian_months_to_travel_forth--;
        }
        if (city_data.distant_battle.battle.egyptian_months_to_travel_forth <= 1)
            city_data.distant_battle.battle.egyptian_months_to_travel_forth = 1;

        city_data.distant_battle.battle.egyptian_months_traveled
          = roman_travel_months - city_data.distant_battle.battle.egyptian_months_to_travel_forth + 1;
        if (city_data.distant_battle.battle.egyptian_months_traveled < 1)
            city_data.distant_battle.battle.egyptian_months_traveled = 1;

        if (city_data.distant_battle.battle.egyptian_months_traveled > roman_travel_months)
            city_data.distant_battle.battle.egyptian_months_traveled = roman_travel_months;
    }
}

static void set_city_vulnerable() {
    if (city_data.distant_battle.battle.city)
        g_empire.city(city_data.distant_battle.battle.city)->set_vulnerable();
}

static void set_city_foreign() {
    if (city_data.distant_battle.battle.city)
        g_empire.city(city_data.distant_battle.battle.city)->set_foreign();

    city_data.distant_battle.battle.city_foreign_months_left = 24;
}

static int player_has_won() {
    int won;
    int pct_loss;
    if (city_data.distant_battle.battle.egyptian_strength < city_data.distant_battle.battle.enemy_strength) {
        won = 0;
        pct_loss = 100;
    } else {
        won = 1;
        int pct_advantage = calc_percentage<int>(city_data.distant_battle.battle.egyptian_strength - city_data.distant_battle.battle.enemy_strength, city_data.distant_battle.battle.egyptian_strength);
        
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

static void fight_distant_battle() {
    if (city_data.distant_battle.battle.egyptian_months_to_travel_forth <= 0) {
        events::emit(event_message{ true, "message_distant_battle_lost_no_troops", 0, 0 });
        g_city.kingdome.change(-50);
        set_city_foreign();
    } else if (city_data.distant_battle.battle.egyptian_months_to_travel_forth > 2) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_late", 0, 0 });
        g_city.kingdome.change(-25);
        set_city_foreign();
        city_data.distant_battle.battle.egyptian_months_to_travel_back = city_data.distant_battle.battle.egyptian_months_traveled;
    } else if (!player_has_won()) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_weak", 0, 0 });
        g_city.kingdome.change(-10);
        set_city_foreign();
        city_data.distant_battle.battle.egyptian_months_traveled = 0;
        // no return: all soldiers killed
    } else {
        events::emit(event_message{ true, "message_distant_battle_won", 0, 0 });
        g_city.kingdome.change(25);
        city_buildings_earn_triumphal_arch();
        //building_menu_update(BUILDSET_NORMAL);
        city_data.distant_battle.battle.won_count++;
        city_data.distant_battle.battle.city_foreign_months_left = 0;
        city_data.distant_battle.battle.egyptian_months_to_travel_back = city_data.distant_battle.battle.egyptian_months_traveled;
    }
    city_data.distant_battle.battle.months_until_battle = 0;
    city_data.distant_battle.battle.enemy_months_traveled = 0;
    city_data.distant_battle.battle.egyptian_months_to_travel_forth = 0;
}

static void update_aftermath() {
    if (city_data.distant_battle.battle.egyptian_months_to_travel_back > 0) {
        city_data.distant_battle.battle.egyptian_months_to_travel_back--;
        city_data.distant_battle.battle.egyptian_months_traveled = city_data.distant_battle.battle.egyptian_months_to_travel_back;
        if (city_data.distant_battle.battle.egyptian_months_to_travel_back <= 0) {
            if (city_data.distant_battle.battle.city_foreign_months_left) {
                // soldiers return - not in time
                events::emit(event_message{ true, "message_troops_return_failed", 0, city_data.map.exit_point.grid_offset() });
            } else {
                // victorious
                events::emit(event_message{ true, "message_troops_return_victorious", 0, city_data.map.exit_point.grid_offset() });
            }
            city_data.distant_battle.battle.egyptian_months_traveled = 0;
            formation_batalions_return_from_distant_battle();
        }
    } else if (city_data.distant_battle.battle.city_foreign_months_left > 0) {
        city_data.distant_battle.battle.city_foreign_months_left--;
        if (city_data.distant_battle.battle.city_foreign_months_left <= 0) {
            events::emit(event_message{ true, "message_city_retaken", 0, 0 });
            set_city_vulnerable();
        }
    }
}

void city_military_process_distant_battle() {
    if (city_data.distant_battle.battle.months_until_battle > 0) {
        --city_data.distant_battle.battle.months_until_battle;
        if (city_data.distant_battle.battle.months_until_battle > 0)
            update_time_traveled();
        else {
            fight_distant_battle();
        }
    } else {
        update_aftermath();
    }
}
