#pragma once

#include "core/xstring.h"
#include <cstdint>

enum e_mesage_category {
    MESSAGE_CAT_RIOT = 0,
    MESSAGE_CAT_FIRE = 1,
    MESSAGE_CAT_COLLAPSE = 2,
    MESSAGE_CAT_RIOT_COLLAPSE = 3,
    MESSAGE_CAT_BLOCKED_DOCK = 4,
    MESSAGE_CAT_WORKERS_NEEDED = 8,
    MESSAGE_CAT_TUTORIAL3 = 9,
    MESSAGE_CAT_NO_WORKING_DOCK = 10,
    MESSAGE_CAT_FISHING_BLOCKED = 11,
    MESSAGE_CAT_HEALTH_PROBLEM = 12,
    MESSAGE_CAT_MONUMENTS = 13,

    MESSAGE_CAT_SIZE = 20,
};

enum e_message_advisor {
    MESSAGE_ADVISOR_NONE = 0,
    MESSAGE_ADVISOR_LABOR = 1,
    MESSAGE_ADVISOR_TRADE = 2,
    MESSAGE_ADVISOR_POPULATION = 3,
    MESSAGE_ADVISOR_IMPERIAL = 4,
    MESSAGE_ADVISOR_MILITARY = 5,
    MESSAGE_ADVISOR_HEALTH = 6,
    MESSAGE_ADVISOR_RELIGION = 7,
};

enum e_message_type {
    MESSAGE_BARBARIAN_ATTACK = 23,
    MESSAGE_KINGDOME_REQUESTS_GOODS = 28,
    MESSAGE_KINGDOME_REQUESTS_MONEY = 29,
    MESSAGE_REQUEST_REMINDER = 31,
    MESSAGE_REQUEST_REFUSED = 33,
    MESSAGE_REQUEST_REFUSED_OVERDUE = 34,
    MESSAGE_UNEMPLOYMENT = 36,
    MESSAGE_WORKERS_NEEDED = 37,
    MESSAGE_WRATH_OF_CERES = 41,
    MESSAGE_WRATH_OF_NEPTUNE_NO_SEA_TRADE = 42,
    MESSAGE_WRATH_OF_MERCURY = 43,
    MESSAGE_WRATH_OF_MARS_NO_MILITARY = 44,
    MESSAGE_WRATH_OF_VENUS = 45,
    MESSAGE_NOT_ENOUGH_FOOD = 49,
    MESSAGE_FOOD_NOT_DELIVERED = 50,
    MESSAGE_THEFT = 52,
    MESSAGE_TUTORIAL_FIRE = 53,
    MESSAGE_TUTORIAL_COLLAPSE = 54,
    MESSAGE_GODS_UNHAPPY = 55,
    MESSAGE_TUTORIAL_WATER = 56,
    MESSAGE_TUTORIAL_GROWING_YOUR_CITY = 57,
    MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS = 58,
    MESSAGE_TUTORIAL_RELIGION = 59,
    MESSAGE_TUTORIAL_TAXES_INDUSTRY = 60,
    MESSAGE_EARTHQUAKE = 62,
    MESSAGE_GLADIATOR_REVOLT = 63,
    MESSAGE_GLADIATOR_REVOLT_FINISHED = 73,
    MESSAGE_EMPIRE_HAS_EXPANDED = 77,
    MESSAGE_ROAD_TO_ROME_BLOCKED = 80,
    MESSAGE_WRATH_OF_NEPTUNE = 81,
    MESSAGE_WRATH_OF_MARS = 82,
    MESSAGE_CERES_IS_UPSET = 91,
    MESSAGE_NEPTUNE_IS_UPSET = 92,
    MESSAGE_MERCURY_IS_UPSET = 93,
    MESSAGE_MARS_IS_UPSET = 94,
    MESSAGE_VENUS_IS_UPSET = 95,
    MESSAGE_BLESSING_FROM_CERES = 96,
    MESSAGE_BLESSING_FROM_NEPTUNE = 97,
    MESSAGE_BLESSING_FROM_MERCURY = 98,
    MESSAGE_BLESSING_FROM_MARS = 99,
    MESSAGE_BLESSING_FROM_VENUS = 100,
    MESSAGE_GODS_WRATHFUL = 101,
    MESSAGE_SPIRIT_OF_MARS = 105,
    MESSAGE_CAESAR_RESPECT_1 = 106,
    MESSAGE_CAESAR_RESPECT_2 = 107,
    MESSAGE_CAESAR_RESPECT_3 = 108,
    MESSAGE_WORKING_HIPPODROME = 109,
    MESSAGE_WORKING_COLOSSEUM = 110,
    MESSAGE_EMIGRATION = 111,
    MESSAGE_FIRED = 112,
    MESSAGE_REQUEST_CAN_COMPLY = 314 - 99,
    MESSAGE_ROAD_TO_ROME_OBSTRUCTED = 116,
    MESSAGE_NO_WORKING_DOCK = 117,
    MESSAGE_FISHING_BOAT_BLOCKED = 118,
    MESSAGE_TUTORIAL_HEALTH = 119,
    MESSAGE_LOCAL_UPRISING_SETH = 121,

    //

    MESSAGE_TEMPLATE_ATTACK_CHEAT = 122,
    MESSAGE_TEMPLATE_UNUSED = 123,
    MESSAGE_TEMPLATE_ATK_PHARAOH_6MO_1MO = 124,
    MESSAGE_TEMPLATE_ATK_PHARAOH_1YR = 125,
    MESSAGE_TEMPLATE_ATK_PHARAOH_INIT_2YR = 126,
    MESSAGE_TEMPLATE_ATK_CITY_6MO_1MO = 127,
    MESSAGE_TEMPLATE_ATK_CITY_1YR = 128,
    MESSAGE_TEMPLATE_ATK_CITY_INIT_2YR = 129,
    MESSAGE_TEMPLATE_REQUEST = 130,
    MESSAGE_TEMPLATE_GENERAL = 131,
    MESSAGE_TEMPLATE_GIFT = 132,
    MESSAGE_TEMPLATE_ATTACK_ALERT = 133,
    MESSAGE_TEMPLATE_MONUMENT_CONGRATZ = 146,
    MESSAGE_TEMPLATE_EARTHQUAKE = 261,
    MESSAGE_TEMPLATE_CITY_SAVED = 262,
    MESSAGE_TEMPLATE_DISTANT_BATTLE_WON = 263,
    MESSAGE_TEMPLATE_LAND_TRADE_PROBLEM = 264,
    MESSAGE_TEMPLATE_SEA_TRADE_PROBLEM = 265,
    MESSAGE_TEMPLATE_TRADE_CITY_UNDER_SIEGE = 266,
    MESSAGE_TEMPLATE_CITY_UNDER_ATTACK = 267,
    MESSAGE_TEMPLATE_WAGE_INCREASE = 268,
    MESSAGE_TEMPLATE_WAGE_DECREASE = 269,
    MESSAGE_TEMPLATE_CONTAMINATED_WATER = 270,
    MESSAGE_TEMPLATE_GOLD_MINE_CAVEIN = 271,
    MESSAGE_CLAY_PIT_CAVEIN = 272,
    MESSAGE_TEMPLATE_DISTANT_BATTLE = 273,
    MESSAGE_TEMPLATE_DEMAND_INCREASE = 274,
    MESSAGE_TEMPLATE_DEMAND_DECREASE = 275,
    MESSAGE_TEMPLATE_FESTIVAL = 276,
    MESSAGE_TEMPLATE_CONSTR_PROJECT = 277,
    MESSAGE_TEMPLATE_PRICE_INCREASE = 278,
    MESSAGE_TEMPLATE_PRICE_DECREASE = 279,
    MESSAGE_TEMPLATE_FOREIGN_CITY_FALLS = 338,
    MESSAGE_TEMPLATE_FOREIGN_CITY_CONQUERED = 339,

    MESSAGE_NO_WORKING_DOCK_PH = 316 - 99,

    MESSAGE_TUTORIAL_SOLDIERS_AND_FORT = 245 - 99,
    MESSAGE_TUTORIAL_REQUESTS_FROM_OTHER_CITIES = 251 - 99,
    MESSAGE_TUTORIAL_FIRE_IN_THE_VILLAGE = 252 - 99,
    MESSAGE_TUTORIAL_COLLAPSED_BUILDING = 253 - 99,
    MESSAGE_TUTORIAL_MONUMENTS_AND_MORE = 257 - 99,
    MESSAGE_TUTORIAL_TRADE_WITH_OTHER_CITIES = 260 - 99,

    MESSAGE_SMALL_BLESSING_OSIRIS = 321 - 99,
    MESSAGE_CURSE_OSIRIS_NOEFFECT = 337 - 99,

    MESSAGE_SMALL_BLESSING_RA_1 = 322 - 99,
    MESSAGE_SMALL_BLESSING_RA_2 = 331 - 99,
    MESSAGE_CURSE_RA_1 = 280 - 99,
    MESSAGE_CURSE_RA_2 = 332 - 99,
    MESSAGE_CURSE_RA_3 = 333 - 99,
    MESSAGE_CURSE_RA_NOEFFECT = 336 - 99,

    MESSAGE_BLESSING_PTAH = 297 - 99,
    MESSAGE_BLESSING_PTAH_NOEFFECT = 145 - 99,
    MESSAGE_SMALL_BLESSING_PTAH = 323 - 99,

    MESSAGE_BLESSING_BAST = 299 - 99,
    MESSAGE_SMALL_BLESSING_BAST = 325 - 99,
    MESSAGE_CURSE_BAST_NOEFFECT = 335 - 99,

    MESSAGE_FLOOD_MEDIOCRE = 342 - 99,
    MESSAGE_FLOOD_POOR = 343 - 99,
};

struct city_message {
    int sequence;
    uint32_t MM_text_id;
    int year;
    int month;
    int param1;
    int param2;
    bool is_read;
    //
    int16_t eventmsg_body_id;
    int16_t eventmsg_title_id;
    int16_t sender_faction;
    int req_city;

    int req_amount;
    int req_resource;
    uint8_t req_months_left;
    int unk_07;

    int eventmsg_phrase_id;
    int req_city_past;
    int unk_09;
    uint8_t unk_10;
    bool hide_img;

    int req_amount_past;
    int req_resource_past;
    int unk_11a_i8;
    uint8_t god;
    uint16_t background_img;
};

#define MAX_MESSAGES 1000
#define MAX_MESSAGES_QUEUE 20

struct messages {
    static void popup(xstring message_id, int param1, int param2);
    static void god(int god, xstring message_id);
};

struct event_message { bool use_popup; xstring message_id; int param1; int param2; };
struct event_message_god { int god; xstring message_id; };
struct event_message_population { bool use_popup; xstring title; };

struct message_manager_t {
    city_message messages[MAX_MESSAGES];

    int queue[20];
    int consecutive_message_delay;

    int next_message_sequence;
    uint16_t total_messages;
    uint16_t reserved_1;
    uint16_t current_message_id;
    uint16_t reserved_2;
    uint16_t reserved_3;
    uint16_t reserved_4;
    uint16_t reserved_5;
    uint8_t reserved_6;
    uint8_t reserved_7;

    union {
        uint16_t popmiles;
        uint16_t pop500 : 1;
        uint16_t pop1000 : 1;
        uint16_t pop2000 : 1;
        uint16_t pop3000 : 1;
        uint16_t pop5000 : 1;
        uint16_t pop10000 : 1;
        uint16_t pop15000 : 1;
        uint16_t pop20000 : 1;
        uint16_t pop25000 : 1;
    } population_shown;

    int message_count[MESSAGE_CAT_SIZE];
    int message_delay[MESSAGE_CAT_SIZE];

    uint32_t last_sound_time[MESSAGE_CAT_RIOT_COLLAPSE + 1];

    int problem_count;
    int problem_index;
    uint32_t problem_last_click_time;

    short scroll_position;

    void init();
    void init_problem_areas();
    int new_message_id();

    city_message& post_common(bool use_popup, int message_id, int param1, int param2, int god, int bg_img);
    city_message& post_common(bool use_popup, xstring message, int param1, int param2, int god, int bg_img);
};

extern message_manager_t g_message_manager;
struct event_ph_t;

void city_message_disable_sound_for_next_message(void);
void city_message_apply_sound_interval(int category);

void city_message_post_full(bool use_popup, int template_id, const event_ph_t* event, int parent_event_id, int title_id, int body_id, int phrase_id, int param1, int param2);

city_message &city_message_post_with_popup_delay(e_mesage_category category, bool use_popup, xstring message, int param1, short param2);
void city_message_post_with_message_delay(e_mesage_category category, int use_popup, int message_type, int delay);

void city_message_process_queue(void);
void city_message_sort_and_compact(void);

int city_message_get_text_id(int message_id);
int city_message_get_advisor(int message_type);

void city_message_reset_category_count(e_mesage_category category);
void city_message_increase_category_count(e_mesage_category category);
int city_message_get_category_count(e_mesage_category category);
void city_message_decrease_delays();

bool city_message_mark_population_shown(int population);

const city_message& city_message_get(int message_id);

int city_message_set_current(int message_id);
void city_message_mark_read(int message_id);
void city_message_delete(int message_id);
int city_message_count(void);

int city_message_problem_area_count(void);
int city_message_next_problem_area_grid_offset(void);

void city_message_clear_scroll(void);
int city_message_scroll_position(void);
void city_message_set_scroll_position(int scroll_position);