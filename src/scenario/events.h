#pragma once

#include "core/bstring.h"

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
    EVENT_TYPE_GIFT = 23,
    EVENT_TYPE_LOCUSTS = 24,
    EVENT_TYPE_FROGS = 25,
    EVENT_TYPE_HAILSTORM = 26,
    EVENT_TYPE_BLOOD_RIVER = 27,
    EVENT_TYPE_CRIME_WAVE = 28,
};

enum {
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

enum {
    EVENT_FACTION_REQUEST_FROM_CITY = 0,
    EVENT_FACTION_REQUEST_FROM_PHARAOH = 1,
};

enum {
    EVENT_TRIGGER_ONCE = 0,
    EVENT_TRIGGER_ONLY_VIA_EVENT = 1,
    EVENT_TRIGGER_RECURRING = 2,

    EVENT_TRIGGER_ALREADY_FIRED = 4,

    EVENT_TRIGGER_ACTIVATED_8 = 8,

    EVENT_TRIGGER_BY_RATING = 10,

    EVENT_TRIGGER_ACTIVATED_12 = 12,
};

enum {
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

enum e_event_state {
    e_event_state_initial = 0,
    e_event_state_in_progress = 1,
    e_event_state_overdue = 2,
    e_event_state_finished = 3,
    e_event_state_finished_late = 4,
    e_event_state_failed = 5,
    e_event_state_received = 6,
    e_event_state_already_fired = 7
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

struct event_ph_t {
    int16_t num_total_header;
    int16_t __unk01;
    int16_t event_id;
    e_event_type type;
    int8_t month;
    int16_t item_fields[4];
    int16_t amount_fields[4];
    event_ph_value time;
    int16_t location_fields[4];
    int16_t on_completed_action;
    int16_t on_refusal_action;
    int16_t event_trigger_type;
    int16_t __unk07;
    int16_t months_initial;
    int16_t quest_months_left;
    e_event_state event_state;
    bool is_overdue;
    bool is_active;
    bool can_comply_dialog_shown;
    int16_t __unk11;
    int8_t festival_deity;
    int8_t __unk12_i8;
    int8_t invasion_attack_target;
    // ...
    // ...
    // ...
    int16_t on_tooLate_action;
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
    int16_t __unk20a;
    int16_t __unk20b;
    int16_t __unk20c;
    int16_t __unk21;
    int16_t __unk22;
};

int16_t scenario_events_num();

const event_ph_t* get_scenario_event(int id);
event_ph_t* set_scenario_event(int id);
uint8_t* get_eventmsg_text(int group_id, int index);

void scenario_events_process();

bool eventmsg_load();
bool eventmsg_auto_phrases_load();

struct mission_id_t;
void scenario_load_events_meta_data(const mission_id_t &missionid);
