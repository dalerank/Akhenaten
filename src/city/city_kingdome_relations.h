#pragma once

#include <cstdint>
#include "core/runtime_item.h"
#include "city/city_component.h"
#include "city/constants.h"
#include "core/archive.h"

enum e_gift { 
    GIFT_MODEST = 0,
    GIFT_GENEROUS = 1,
    GIFT_LAVISH = 2,
    GIFT_ROYAL = 3,
    GIFT_KINGDOM = 4,
    GIFT_KINGDOM_ROYAL = 5,
    GIFT_KINGDOM_LAVISH = 6,
    GIFT_KINGDOM_GENEROUS = 7,
    GIFT_KINGDOM_MODEST = 8,
    GIFT_COUNT,
};
extern const token_holder<e_gift, GIFT_MODEST, GIFT_COUNT> e_gift_tokens;

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

struct gift_rule {
    e_gift id;
    float rate;
    float minimum;
};

template<>
struct stable_array_max_elements<gift_rule> {
    enum { max_elements = GIFT_COUNT };
};

template<>
struct std::hash<gift_rule> {
    [[nodiscard]] size_t operator()(const gift_rule &d) const noexcept {
        return d.id;
    }
};
ANK_CONFIG_STRUCT(gift_rule, id, rate, minimum)

struct kingdome_relation_t : city_component_t<kingdome_relation_t> {
    kingdome_gift gifts[GIFT_COUNT];
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
    const kingdome_gift *get_gift(int size);
    int can_send_gift(int size);
    void send_gift(int gift_size);
    int salary_for_rank(int rank);
    void set_salary_rank(int rank);
    void update_debt_state();
    void process_invasion();
    void update();
    void update_gifts();
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
    void on_post_load();
    void reset();

    struct static_params {
        stable_array<gift_rule> gift_rules;
        svector<int, 16> salary_ranks;
        svector<uint8_t, 4> gift_relation_change_first;
        svector<uint8_t, 4> gift_relation_change_second;
        svector<uint8_t, 4> gift_relation_change_third;
        svector<uint8_t, 4> gift_relation_change_last;
        uint8_t months_since_gift_locker;
        svector<int8_t, 8> tribute_not_paid_years_penalty;
        int8_t player_salary_above_king_penalty;
        int8_t player_salary_less_king_promotion;
        int8_t first_debt_penalty;
        int8_t second_debt_penalty;
        int8_t last_debt_rating_cap;
    };

    static const static_params &params();
};
ANK_CONFIG_STRUCT(kingdome_relation_t::static_params,
                  gift_rules, 
                  salary_ranks, 
                  gift_relation_change_first, 
                  gift_relation_change_second, 
                  gift_relation_change_third, 
                  gift_relation_change_last, 
                  months_since_gift_locker, 
                  tribute_not_paid_years_penalty, 
                  player_salary_above_king_penalty, 
                  player_salary_less_king_promotion, 
                  first_debt_penalty, 
                  second_debt_penalty, 
                  last_debt_rating_cap)