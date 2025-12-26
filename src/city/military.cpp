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

int city_military_months_until_distant_battle() {
    return city_data.distant_battle.battle.months_until_battle;
}