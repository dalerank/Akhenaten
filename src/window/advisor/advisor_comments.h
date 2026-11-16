#pragma once

#include "city/constants.h"
#include "core/archive.h"
#include "core/tokenum.h"

#include <cstdint>

// OG window/advisor/chief.c (row texts) and window/advisor_comments.c (comment window texts).
enum e_advisor_comment_topic {
    ADVISOR_COMMENT_SENTIMENT = 0,
    ADVISOR_COMMENT_MIGRATION = 1,
    ADVISOR_COMMENT_EMPLOYMENT = 2,
    ADVISOR_COMMENT_FOOD_STOCKS = 3,
    ADVISOR_COMMENT_FOOD_CONSUMPTION = 4,
    ADVISOR_COMMENT_HEALTH = 5,
    ADVISOR_COMMENT_RELIGION = 6,
    ADVISOR_COMMENT_FINANCES = 7,
    ADVISOR_COMMENT_CRIME = 8,
    ADVISOR_COMMENT_MILITARY = 9,
    ADVISOR_COMMENT_KINGDOM = 10,
    ADVISOR_COMMENT_NILOMETER = 11,
    ADVISOR_COMMENT_TOPIC_COUNT
};
using e_advisor_comment_topic_tokens_t
  = token_holder<e_advisor_comment_topic, ADVISOR_COMMENT_SENTIMENT, ADVISOR_COMMENT_TOPIC_COUNT>;

enum e_advisor_text_tone { ADVISOR_TONE_RED = 0, ADVISOR_TONE_WHITE = 1, ADVISOR_TONE_GREEN = 2, ADVISOR_TONE_COUNT };
using e_advisor_text_tone_tokens_t = token_holder<e_advisor_text_tone, ADVISOR_TONE_RED, ADVISOR_TONE_COUNT>;

enum e_chief_row_number {
    CHIEF_NUMBER_NONE = 0,
    CHIEF_NUMBER_PLAIN = 1,
    CHIEF_NUMBER_PERCENT = 2,
    CHIEF_NUMBER_MONEY = 3,
    CHIEF_NUMBER_COUNT
};
using e_chief_row_number_tokens_t = token_holder<e_chief_row_number, CHIEF_NUMBER_NONE, CHIEF_NUMBER_COUNT>;

// OG advisor_comment_rules (advisor_comments.c), names as in OG advisors_config.c.
struct advisor_comment_rules_t {
    int sentiment_low = 50;
    int sentiment_fair = 100;
    int migration_max_armed_figures = 3;
    int migration_newcomers_strong = 5;
    int migration_percentage_strong = 80;
    int employment_balanced_unemployment = 5;
    int employment_balanced_workers_needed = 5;
    int unemployment_urgent = 17;
    int unemployment_serious = 10;
    int unemployment_important = 5;
    int labor_shortage_urgent = 20;
    int labor_shortage_serious = 10;
    int food_stocks_low_percent = 50;
    int food_supply_plenty_percent = 150;
    int food_supply_enough_percent = 110;
    int food_supply_barely_enough_percent = 95;
    int food_supply_slightly_short_percent = 85;
    int food_supply_short_percent = 70;
    int angry_god_mood = 40;
    int very_angry_god_mood = 20;
    int happy_god_mood = 60;
    int thefts_many = 10;
    int thefts_several = 5;
    int thefts_some = 2;
    int requests_counted = 5;
    int requests_some_max = 2;
    int requests_several_max = 4;
};
ANK_CONFIG_STRUCT(advisor_comment_rules_t, sentiment_low, sentiment_fair, migration_max_armed_figures,
  migration_newcomers_strong, migration_percentage_strong, employment_balanced_unemployment,
  employment_balanced_workers_needed, unemployment_urgent, unemployment_serious, unemployment_important,
  labor_shortage_urgent, labor_shortage_serious, food_stocks_low_percent, food_supply_plenty_percent,
  food_supply_enough_percent, food_supply_barely_enough_percent, food_supply_slightly_short_percent,
  food_supply_short_percent, angry_god_mood, very_angry_god_mood, happy_god_mood, thefts_many, thefts_several,
  thefts_some, requests_counted, requests_some_max, requests_several_max)

// Thresholds of the chief advisor's rows (OG window/advisor/chief.c).
struct chief_advisor_rules_t {
    int sentiment_white_from = 30;
    int sentiment_green_from = 50;
    int sentiment_cause_below = 50;
    int migration_max_armed_figures = 3;
    int migration_newcomers_strong = 5;
    int migration_percentage_strong = 80;
    int unemployment_urgent = 18;
    int unemployment_serious = 11;
    int unemployment_important = 6;
    int unemployment_tolerable = 1;
    int workers_needed_urgent = 21;
    int workers_needed_serious = 11;
    int workers_needed_important = 6;
    int employment_balanced_below = 6;
    int food_stocks_low_percent = 50;
    int food_supply_plenty_percent = 150;
    int food_supply_enough_percent = 110;
    int food_supply_barely_enough_percent = 95;
    int food_supply_slightly_short_percent = 85;
    int food_supply_short_percent = 70;
    int health_white_from = 20;
    int health_green_from = 30;
    int angry_god_mood = 30;
    int very_angry_god_mood = 20;
    int happy_god_mood = 70;
    int thefts_many = 10;
    int thefts_several = 5;
    int thefts_some = 2;
    int requests_counted = 5;
    int requests_some_max = 2;
    int requests_several_max = 4;
    int flood_quality_step = 20;
};
ANK_CONFIG_STRUCT(chief_advisor_rules_t, sentiment_white_from, sentiment_green_from, sentiment_cause_below,
  migration_max_armed_figures, migration_newcomers_strong, migration_percentage_strong, unemployment_urgent,
  unemployment_serious, unemployment_important, unemployment_tolerable, workers_needed_urgent, workers_needed_serious,
  workers_needed_important, employment_balanced_below, food_stocks_low_percent, food_supply_plenty_percent,
  food_supply_enough_percent, food_supply_barely_enough_percent, food_supply_slightly_short_percent,
  food_supply_short_percent, health_white_from, health_green_from, angry_god_mood, very_angry_god_mood, happy_god_mood,
  thefts_many, thefts_several, thefts_some, requests_counted, requests_some_max, requests_several_max,
  flood_quality_step)

extern advisor_comment_rules_t advisor_comment_rules;
extern chief_advisor_rules_t chief_advisor_rules;

// The city values the chief advisor's rows and comments read (OG city_player fields).
struct advisor_city_state {
    int sentiment = 0;
    int low_mood_cause = 0;
    int migration_direction = 0;
    int kingdom_soldiers = 0;
    int enemies = 0;
    int soldiers = 0;
    int newcomers = 0;
    int refused_immigrants_today = 0;
    int room_in_houses = 0;
    int migration_percentage = 0;
    int no_immigration_cause = 0;
    int unemployment_percentage = 0;
    int workers_needed = 0;
    int kingdom_supplies_grain = 0;
    int food_supply_months = 0;
    int food_stored_total = 0;
    int food_needed_per_month = 0;
    int population = 0;
    int food_supply_percentage = 0;
    int health = 0;
    int god_mood0 = 0;
    int god_mood1 = 0;
    int god_mood2 = 0;
    int god_mood3 = 0;
    int god_mood4 = 0;
    int taxes_collected = 0;
    int taxes_uncollected = 0;
    int treasury = 0;
    int balance_last_year = 0;
    int crimes_this_month = 0;
    int gold_stolen_this_month = 0;
    int invasion_running = 0;
    int troops_requested = 0;
    int troops_away = 0;
    int requests_waiting = 0;
    int flood_quality = 0;
    int flood_month = 0;

    int god_mood(int god) const;
};
ANK_CONFIG_PROPERTY(advisor_city_state, sentiment, low_mood_cause, migration_direction, kingdom_soldiers, enemies,
  soldiers, newcomers, refused_immigrants_today, room_in_houses, migration_percentage, no_immigration_cause,
  unemployment_percentage, workers_needed, kingdom_supplies_grain, food_supply_months, food_stored_total,
  food_needed_per_month, population, food_supply_percentage, health, god_mood0, god_mood1, god_mood2, god_mood3,
  god_mood4, taxes_collected, taxes_uncollected, treasury, balance_last_year, crimes_this_month, gold_stolen_this_month,
  invasion_running, troops_requested, troops_away, requests_waiting, flood_quality, flood_month)

struct chief_advisor_row {
    int text = -1;
    int tone = ADVISOR_TONE_GREEN;
    int cause_text = -1;
    int number = 0;
    int number_kind = CHIEF_NUMBER_NONE;
    int suffix_group = -1;
    int suffix_text = -1;
    int second_text = -1;
};

struct advisor_comment {
    int text = -1;
    e_advisor advisor = ADVISOR_NONE;
};

advisor_city_state advisor_city_state_current();
// Test hook: values set here replace the gathered ones until cleared.
void advisor_city_state_override(const xstring& name, int value);
void advisor_city_state_clear_override();

chief_advisor_row chief_advisor_row_for(int topic, const advisor_city_state& s, const chief_advisor_rules_t& rules);
advisor_comment advisor_comment_for(int topic, const advisor_city_state& s, const advisor_comment_rules_t& rules);
int population_advisor_food_text(const advisor_city_state& s, const chief_advisor_rules_t& rules);
bool chief_advisor_row_opens_comment(int topic, const advisor_city_state& s, const advisor_comment_rules_t& rules);
