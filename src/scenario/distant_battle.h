#pragma once

#include <cstdint>

#include "core/archive.h"

struct formation;

using army_path = svector<vec2i, 50>;

struct dispatched_army_t {
    enum e_state : uint8_t {
        state_inactive = 0,
        state_awaiting_soldiers,
        state_traveling,
        state_at_battle,
        state_returning,
        state_returning_win,
        state_returning_lose,
        state_returning_destroyed,
    };

    e_state state;
    uint8_t await_soldiers;
    uint8_t position_index;
    uint8_t movement_delay;
    uint8_t movement_delay_max;
    vec2i pos;
    army_path path;

    void append_soldier(uint16_t fid) {
        if (await_soldiers > 0)
            await_soldiers--;
    }

    vec2i get_current_position() const;
    void formation_batalions_kill_in_distant_battle(int kill_percentage);
    void formation_batalions_kill_soldiers(formation *m, int kill_percentage);
    void return_from_distant_battle();
    void return_soldiers(formation *m);

    void clear();
};
ANK_CONFIG_PROPERTY(dispatched_army_t,
    state, pos)

struct distant_battles_t {
    struct battle_state_t {
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

        void clear();
    };

    battle_state_t battle;
    dispatched_army_t dispatched_army;

    void init_distant_battle(int enemy_strength);
    int kingdome_army_is_traveling();
    int enemy_months_traveled();
    int has_distant_battle();
    void update_time_traveled();
    void fight_distant_battle();
    void update_aftermath();
    void set_city_vulnerable();
    void set_city_foreign();
    bool player_has_won();
    void update_month();
    void update_day();
    int enemy_strength();
    bool city_is_egyptian();
    void dispatch_to_distant_battle(int egyptian_strength, uint8_t soldiers_num);
    const army_path &get_path();

    void determine_distant_battle_city();
    void clear();

    void process_distant_battle_impl();
};
ANK_CONFIG_PROPERTY(distant_battles_t::battle_state_t,
    egyptian_months_to_travel_forth, 
    egyptian_months_to_travel_back,
    months_until_battle,
    city)

extern distant_battles_t g_distant_battle;
