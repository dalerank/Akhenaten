#pragma once

#include <cstdint>

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

struct kingdome_relation_t {
    kingdome_gift gifts[3];
    int32_t months_since_gift;
    int32_t gift_overdose_penalty;

    e_debt_state debt_state;
    int32_t months_in_debt;

    int32_t player_rank;
    uint8_t salary_rank;
    uint8_t salary_amount;
    int32_t donate_amount;
    uint16_t personal_savings;
    uint8_t player_name_adversary[32];
    uint8_t player_name[32];
    uint8_t campaign_player_name[32]; /**< Temp storage for carrying over player name to next campaign mission */
    struct {
        int32_t count;
        int32_t size;
        int32_t soldiers_killed;
        int32_t warnings_given;
        int32_t days_until_invasion;
        int32_t duration_day_countdown;
        int32_t retreat_message_shown;
    } invasion;

    void init_scenario(int rank, int load_type);
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
};
