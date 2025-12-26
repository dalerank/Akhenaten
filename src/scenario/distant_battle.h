#pragma once

#include <cstdint>

struct distant_battles_t {
    struct battle_state {
        uint8_t city;
        int8_t city_foreign_months_left;
        int8_t total_count;
        int8_t won_count;
        uint8_t enemy_strength;
        uint8_t egyptian_strength;
        int8_t months_until_battle;
        int8_t egyptian_months_to_travel_forth;
        int8_t egyptian_months_to_travel_back;
        int8_t enemy_months_traveled;
        int8_t egyptian_months_traveled;
    };

    battle_state battle;
    void init_distant_battle(int enemy_strength);
    int has_distant_battle();
    void process_distant_battle();
    void update_time_traveled();
    void fight_distant_battle();
    void update_aftermath();
    void set_city_vulnerable();
    void set_city_foreign();
    bool player_has_won();
};

int scenario_distant_battle_kingdome_travel_months(void);

int scenario_distant_battle_enemy_travel_months(void);

void scenario_distant_battle_process(void);
