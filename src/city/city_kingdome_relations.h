#pragma once

#include <cstdint>
#include "core/runtime_item.h"
#include "city/city_component.h"
#include "city/constants.h"
#include "core/archive.h"

enum e_debt_state {
    e_debt_none = 0,
    e_debt_one_time = 1,
    e_debt_twice = 2,
    e_debt_latest = 3,
    e_debt_not_allowed = 4,
};

struct event_send_gift_to_kingdome { int gift_size; };
struct event_kingdome_update_gifts { int personal_savings; };

struct kingdome_relation_t : city_component_t<kingdome_relation_t> {
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
    // Savings carried over from the previous campaign mission
    //  survives pre_load and is applied on next mission start
    uint16_t campaign_carry_personal_savings;
    xstring player_name_adversary;
    xstring player_name;
    // Temp storage for carrying over player name to next campaign mission
    xstring campaign_player_name;
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
        // 1 = mission favour / scenario KNGDOME (no Caesar respect on wipe). Saved in former pad byte.
        uint8_t favour_only;
        // 1 = console force_attack — skip pause/retreat. Saved in former pad byte after favour_only.
        uint8_t cheated;
    } invasion;

    void load_scenario(int rank, int load_type);
    void update_debt_state();
    void process_invasion();
    void update();
    void mark_soldier_killed();
    // Clear size/kills after player wipe; Caesar respect unless favour_only.
    void finish_army_defeated();
    // Caesar wrath / console attack: count++, zeros days_until_invasion, enables respect popups.
    // cheated=true skips pause/retreat (console).
    void begin_invasion(int size, bool cheated);
    // Mission favour / scenario KNGDOME wave: size+duration for kill tally (no Caesar respect).
    // Does not bump invasion.count or reset days_until_invasion. Pause/retreat are Caesar-only.
    void begin_favour_army(int size);
    // Console / ATTACK_TYPE_KINGDOME. Returns false if spawn failed (no begin_invasion).
    bool force_attack(int size);
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
        int8_t yearly_decay;
        int8_t yearly_decay_from_mission;
        int8_t yearly_profit_bonus;
        int8_t ra_complex_yearly_bonus;
    };

    static const static_params &params();
};
ANK_CONFIG_PROPERTY(kingdome_relation_t, salary_rank, player_rank, kingdom_change, kingdom_salary_penalty,
                    kingdom_milestone_penalty, kingdom_ignored_request_penalty)

ANK_CONFIG_STRUCT(kingdome_relation_t::static_params, salary_ranks, gift_relation_change_first,
  gift_relation_change_second, gift_relation_change_third, gift_relation_change_last, months_since_gift_locker,
  tribute_not_paid_years_penalty, player_salary_above_king_penalty, player_salary_less_king_promotion,
  first_debt_penalty, second_debt_penalty, last_debt_rating_cap, yearly_decay, yearly_decay_from_mission,
  yearly_profit_bonus, ra_complex_yearly_bonus)