#pragma once

#include "core/archive.h"
#include "core/bstring.h"
#include "core/tokenum.h"
#include "game/simulation_time.h"
#include "game/resource.h"

enum e_event_type {
    EVENT_TYPE_NONE = 0,

    EVENT_TYPE_REQUEST = 1,
    EVENT_TYPE_INVASION = 2,

    EVENT_TYPE_SEA_TRADE_PROBLEM = 6,
    EVENT_TYPE_LAND_TRADE_PROBLEM = 7,
    EVENT_TYPE_WAGE_INCREASE = 8,
    EVENT_TYPE_WAGE_DECREASE = 9,
    EVENT_TYPE_CONTAMINATED_WATER = 10,
    EVENT_TYPE_GOLD_MINE_COLLAPSE = 11,
    EVENT_TYPE_CLAY_PIT_FLOOD = 12,
    EVENT_TYPE_DEMAND_INCREASE = 13,
    EVENT_TYPE_DEMAND_DECREASE = 14,
    EVENT_TYPE_PRICE_INCREASE = 15,
    EVENT_TYPE_PRICE_DECREASE = 16,
    EVENT_TYPE_REPUTATION_INCREASE = 17,
    EVENT_TYPE_REPUTATION_DECREASE = 18,
    EVENT_TYPE_CITY_STATUS_CHANGE = 19,
    EVENT_TYPE_MESSAGE = 20,
    EVENT_TYPE_FAILED_FLOOD = 21,
    EVENT_TYPE_PERFECT_FLOOD = 22,
    EVENT_TYPE_GIFT_FROM_PHARAOH = 23,
    EVENT_TYPE_LOCUSTS = 24,
    EVENT_TYPE_FROGS = 25,
    EVENT_TYPE_HAILSTORM = 26,
    EVENT_TYPE_BLOOD_RIVER = 27,
    EVENT_TYPE_CRIME_WAVE = 28,

    EVENT_TYPE_TRADE_CITY_UNDER_SIEGE = 29,
    EVENT_TYPE_FOREIGN_ARMY_ATTACK_WARNING = 30,

    EVENT_TYPE_MAX,
};
using e_event_type_tokens_t = token_holder<e_event_type, EVENT_TYPE_NONE, EVENT_TYPE_MAX>;
extern const e_event_type_tokens_t e_event_type_tokens;

enum e_event_state {
    e_event_state_initial = 0,
    e_event_state_in_progress = 1,
    e_event_state_overdue = 2,
    e_event_state_finished = 3,
    e_event_state_finished_late = 4,
    e_event_state_failed = 5,
    e_event_state_received = 6,
    e_event_state_already_fired = 7,
    e_event_state_max
};
using e_event_state_tokens_t = token_holder<e_event_state, e_event_state_initial, e_event_state_max>;
extern const e_event_state_tokens_t e_event_state_tokens;

enum e_event_subtype {
    EVENT_SUBTYPE_GENERIC_REQUEST = 0,
    EVENT_SUBTYPE_CITY_FELL_TO_ENEMY = 0,
    EVENT_SUBTYPE_MSG_CITY_SAVED = 0,
    EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS = 1,
    EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED = 1,
    EVENT_SUBTYPE_MSG_DISTANT_BATTLE_WON = 1,
    EVENT_SUBTYPE_DISTANT_BATTLE = 2,
    EVENT_SUBTYPE_NEW_TRADE_ROUTE = 2,
    EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST = 2,
    EVENT_SUBTYPE_REQ_FOR_FESTIVAL = 3,
    EVENT_SUBTYPE_LOST_TRADE_ROUTE = 3,
    EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT = 3,
    EVENT_SUBTYPE_CONSTRUCTION_PROJECT = 4,
    EVENT_SUBTYPE_CITY_UNDER_SIEGE = 4,
    EVENT_SUBTYPE_FAMINE = 5,
    EVENT_SUBTYPE_CITY_GENERIC_TROUBLE = 6,
};

enum e_event_faction_request {
    EVENT_FACTION_REQUEST_FROM_CITY = 0,
    EVENT_FACTION_REQUEST_FROM_PHARAOH = 1,
};

enum e_event_trigger_type {
    EVENT_TRIGGER_ONCE = 0,
    EVENT_TRIGGER_ONLY_VIA_EVENT = 1,
    EVENT_TRIGGER_RECURRING = 2,
    EVENT_TRIGGER_ALREADY_FIRED = 4,
    EVENT_TRIGGER_ACTIVATED_8 = 8,
    EVENT_TRIGGER_BY_RATING = 10,
    EVENT_TRIGGER_ACTIVATED_12 = 12,

    EVENT_TRIGGER_MAX
};
using e_event_trigger_type_tokens_t = token_holder<e_event_trigger_type, EVENT_TRIGGER_ONCE, EVENT_TRIGGER_MAX>;
extern const e_event_trigger_type_tokens_t e_event_trigger_type_tokens;

enum e_event_invabder {
    EVENT_INVADER_ENEMY = 1,
    EVENT_INVADER_EGYPT = 2,
    EVENT_INVADER_PHARAOH = 3,
    EVENT_INVADER_BEDUINS = 4,
};

enum e_event_attack {
    EVENT_ATTACK_TARGET_FOOD = 0,
    EVENT_ATTACK_TARGET_VAULTS = 1,
    EVENT_ATTACK_TARGET_BEST_BUILDINGS = 2,
    EVENT_ATTACK_TARGET_TROOPS = 3,
    EVENT_ATTACK_TARGET_RANDOM = 4,
};

enum e_event_var {
    EVENT_VAR_DIRECT_RESULT = 0, // because
    EVENT_VAR_INCIDENTALLY = 1,  // (no conjunction)
    EVENT_VAR_IN_SPITE_OF = 2,   // even though...
    EVENT_VAR_NO_CAUSE = 3,      // (depends on the message?)
    EVENT_VAR_CYCLICAL = 4,
    EVENT_VAR_SPECIFIC_AS_NEEDED = 5,
    EVENT_VAR_AUTO = 6, // (automatically set)
};

enum e_event_action {
    EVENT_ACTION_NONE = -1,
    EVENT_ACTION_COMPLETED = 0,
    EVENT_ACTION_REFUSED = 1,
    EVENT_ACTION_TOOLATE = 2,
    EVENT_ACTION_DEFEAT = 3,
};

struct event_ph_value {
    int16_t value;
    int16_t f_fixed;
    int16_t f_min;
    int16_t f_max;
};
ANK_CONFIG_STRUCT(event_ph_value, value)

struct event_ph_date {
    int16_t year;
    int16_t month;
    int16_t unk02;
    int16_t unk03;
};
ANK_CONFIG_STRUCT(event_ph_date, year, month)

struct event_ph_t {
    int16_t num_total_header;
    int16_t __unk01;
    int16_t event_id;
    e_event_type type;
    event_ph_value item;
    event_ph_value amount;
    event_ph_date time;
    std::array<int16_t, 4> location_fields;
    int16_t on_completed_action;
    int16_t on_refusal_action;
    e_event_trigger_type event_trigger_type;
    uint16_t tag_id;
    uint8_t months_initial;
    uint8_t quest_months_left;
    e_event_state event_state;
    bool is_overdue;
    bool is_active;
    bool can_comply_dialog_shown;
    bool appear_dialgow_shown;
    int16_t __unk11;
    int8_t festival_deity;
    int8_t reserved_unk12;
    int8_t invasion_attack_target;
    // ...
    // ...
    // ...
    int16_t on_too_late_action;
    int16_t on_defeat_action;
    int8_t sender_faction;
    int8_t __unk13_i8;
    int16_t route_fields[4];
    int8_t subtype;
    int8_t __unk15_i8;
    int8_t __unk16;
    int8_t __unk17;
    int16_t __unk18;
    int16_t __unk19;
    int8_t on_completed_msgAlt;
    int8_t on_refusal_msgAlt;
    int8_t on_tooLate_msgAlt;
    int8_t on_defeat_msgAlt;
    int16_t reserved_1;
    std::array<uint16_t, 4> reasons;
    uint16_t rand_reason() const;

    game_date_t date() { return {time.year, time.month}; }
    void archive_load(archive arch);
};
ANK_CONFIG_STRUCT(event_ph_t, type, time, amount, tag_id, months_initial, location_fields, reasons, sender_faction)

struct mission_id_t;
struct event_manager_t {
    int16_t events_count();
    const event_ph_t* at(int id) const;
    event_ph_t* at(int id);
    void process_active_request(int id);
    void process_event(int id, bool via_event_trigger, int chain_action_parent, int caller_event_id = -1, int caller_event_var = EVENT_VAR_AUTO);
    void process_event_city_under_siege(const event_ph_t &event, bool via_event_trigger, int chain_action_parent, int caller_event_id, int caller_event_var);
    void process_events();
    void process_random_events();
    event_ph_t *create(const event_ph_t *parent);
    bool create(const event_ph_t *master, const event_ph_t *parent, e_event_trigger_type trigger_type);
    bool is_valid_event_index(int id);
    int get_auto_reason_phrase_id(int param_1, int param_2);

    pcstr msg_text(int group_id, int index);
    void load_mission_metadata(const mission_id_t &missionid);
    void create_good_request(int tag, e_resource r, int amount, int months_initial);
};