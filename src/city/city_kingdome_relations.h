#pragma once

#include <cstdint>
#include "core/runtime_item.h"
#include "city/city_component.h"
#include "city/constants.h"
#include "core/svector.h"

enum e_gift { 
    GIFT_MODEST = 0,
    GIFT_GENEROUS = 1,
    GIFT_LAVISH = 2
};

enum e_debt_state {
    e_debt_none = 0,
    e_debt_one_time = 1,
    e_debt_twice = 2,
    e_debt_latest = 3,
    e_debt_not_allowed = 4,
};

struct kingdome_gift {
    int id;
    int cost;
};

struct event_send_gift_to_kingdome { int gift_size; };

struct kingdome_relation_t : city_component_t<kingdome_relation_t> {
    kingdome_gift gifts[3];
    int32_t months_since_gift;
    int32_t gift_overdose_penalty;

    e_debt_state debt_state;
    int32_t months_in_debt;
    uint8_t rating;
    uint8_t rating_last_year;
    uint8_t rating_cap;

    int8_t player_rank;
    e_rating_change kingdom_change;
    uint8_t salary_rank;
    uint8_t salary_amount;
    int8_t kingdom_salary_penalty;
    int32_t donate_amount;
    uint16_t personal_savings;
    uint8_t player_name_adversary[32];
    uint8_t player_name[32];
    uint8_t campaign_player_name[32]; /**< Temp storage for carrying over player name to next campaign mission */
    int8_t kingdom_explanation;
    int8_t kingdom_milestone_penalty;
    int8_t kingdom_ignored_request_penalty;

    struct {
        int32_t count;
        int32_t size;
        int32_t soldiers_killed;
        int32_t warnings_given;
        int32_t days_until_invasion;
        int32_t duration_day_countdown;
        int32_t retreat_message_shown;
    } invasion;

    void load_scenario(int rank, int load_type);
    void init_donation_amount();
    const kingdome_gift* get_gift(int size) { return &gifts[size]; }
    int can_send_gift(int size);
    void calculate_gift_costs();
    void send_gift(int gift_size);
    int salary_for_rank(int rank);
    void set_salary_rank(int rank);
    void update_debt_state();
    void process_invasion();
    void update();
    int get_gift_cost(int size);
    void set_donation_amount(int amount);
    void change_donation_amount(int change);
    void donate_savings_to_city();
    void mark_soldier_killed();
    void force_attack(int size);
    void reset_gifts();
    void advance_month();
    void advance_year();

    void change(int amount);
    void update_explanation();
    void reduce_missed_request(int penalty);
    void increase_success_request(int value);
    void increase_blessing_god(int value);
    void reduce_god_wrath(int value);

    void init();
    void reset();

    struct static_params {
        svector<int, 16> salary_ranks;
        svector<uint8_t, 4> gift_relation_change_first;
        svector<uint8_t, 4> gift_relation_change_second;
        svector<uint8_t, 4> gift_relation_change_third;
        svector<uint8_t, 4> gift_relation_change_last;

        void archive_unload() {}
        void archive_init() {}
        void archive_load(archive arch);
    };

    static const static_params &params();
};
