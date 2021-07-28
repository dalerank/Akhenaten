#ifndef OZYMANDIAS_EVENTS_H
#define OZYMANDIAS_EVENTS_H

#include "core/buffer.h"

enum {
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
    EVENT_SUBTYPE_GENERIC_REQUEST = 0,          EVENT_SUBTYPE_CITY_FELL_TO_ENEMY = 0,       EVENT_SUBTYPE_MSG_CITY_SAVED = 0,
    EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS = 1,     EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED = 1,   EVENT_SUBTYPE_MSG_DISTANT_BATTLE_WON = 1,
    EVENT_SUBTYPE_DISTANT_BATTLE = 2,           EVENT_SUBTYPE_NEW_TRADE_ROUTE = 2,          EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST = 2,
    EVENT_SUBTYPE_REQ_FOR_FESTIVAL = 3,         EVENT_SUBTYPE_LOST_TRADE_ROUTE = 3,         EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT = 3,
    EVENT_SUBTYPE_CONSTRUCTION_PROJECT = 4,     EVENT_SUBTYPE_CITY_UNDER_SIEGE = 4,
    EVENT_SUBTYPE_FAMINE = 5,
    EVENT_SUBTYPE_CITY_GENERIC_TROUBLE = 6,
};

enum {
    EVENT_TRIGGER_ONCE = 0,
    EVENT_TRIGGER_ONLY_VIA_EVENT = 1,
    EVENT_TRIGGER_RECURRING = 2,

    EVENT_TRIGGER_ALREADY_FIRED = 4,

    EVENT_TRIGGER_UNK_REQ_8 = 8,

    EVENT_TRIGGER_BY_RATING = 10,

    EVENT_TRIGGER_UNK_REQ_12 = 12,
};

enum {
    EVENT_INVADER_ENEMY = 1,
    EVENT_INVADER_EGYPT = 2,
    EVENT_INVADER_PHARAOH = 3,
    EVENT_INVADER_BEDUINS = 4,
};

enum {
    EVENT_ATTACK_TARGET_FOOD = 0,
    EVENT_ATTACK_TARGET_VAULTS = 1,
    EVENT_ATTACK_TARGET_BEST_BUILDINGS = 2,
    EVENT_ATTACK_TARGET_TROOPS = 3,
    EVENT_ATTACK_TARGET_RANDOM = 4,
};

enum {
    EVENT_STATE_INITIAL = 0,
    EVENT_STATE_IN_PROGRESS = 1,
    EVENT_STATE_FINISHED = 2,
    //
    EVENT_STATE_FAILED = 4,
};

enum {
    EVENT_VAR_DIRECT_RESULT = 0,        // because
    EVENT_VAR_INCIDENTALLY = 1,         // (no conjunction)
    EVENT_VAR_IN_SPITE_OF = 2,          // even though...
    EVENT_VAR_NO_CAUSE = 3,             // (depends on the message?)
    EVENT_VAR_CYCLICAL = 4,
    EVENT_VAR_SPECIFIC_AS_NEEDED = 5,
    EVENT_VAR_AUTO = 6,                 // (automatically set)
};

enum {
    EVENT_ACTION_NONE = -1,
    EVENT_ACTION_COMPLETED = 0,
    EVENT_ACTION_REFUSED = 1,
    EVENT_ACTION_TOOLATE = 2,
    EVENT_ACTION_DEFEAT = 3,
};

#define MAX_EVENTS 150
#define NUM_AUTO_PHRASE_VARIANTS 54
#define NUM_PHRASES 601
#define MAX_EVENTMSG_TEXT_DATA NUM_PHRASES * 200

typedef struct {
    int num_total_header;
    int __unk01;
    int event_id;
    int type;
    int month;
    int request_list_item;
    int item_1;
    int item_2;
    int item_3;
    int request_list_amount;
    int amount_FIXED;
    int amount_MIN;
    int amount_MAX;
    int __unk05;
    int year_or_month_FIXED;
    int year_or_month_MIN;
    int year_or_month_MAX;
    int __unk06;
    int city_or_marker_FIXED;
    int city_or_marker_MIN;
    int city_or_marker_MAX;
    int on_completed_action;
    int on_refusal_action;
    int event_trigger_type;
    int __unk07;
    int months_initial;
    int months_left;
    int event_state;
    int in_progress;
    int __unk11;
    int festival_deity;
    int __unk12_i8;
    int invasion_attack_target;
    // ...
    // ...
    // ...
    int on_tooLate_action;
    int on_defeat_action;
    int sender_faction;
    int __unk13_i8;
    int __unk14;
    int route_FIXED;
    int route_MIN;
    int route_MAX;
    int subtype;
    int __unk15_i8;
    int __unk16;
    int __unk17;
    int __unk18;
    int __unk19;
    int on_completed_msgAlt;
    int on_refusal_msgAlt;
    int on_tooLate_msgAlt;
    int on_defeat_msgAlt;
    int __unk20_FIXED;
    int __unk20_MIN;
    int __unk20_MAX;
    int __unk21;
    int __unk22;
} event_ph_t;

const event_ph_t *get_scenario_event(int id);
uint8_t *get_eventmsg_text(int group_id, int index);

void scenario_event_process();

void scenario_events_save_state(buffer *buf);
void scenario_events_load_state(buffer *buf);

bool eventmsg_load(void);
bool eventmsg_auto_phrases_load(void);

#endif //OZYMANDIAS_EVENTS_H
