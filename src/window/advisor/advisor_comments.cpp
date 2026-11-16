#include "window/advisor/advisor_comments.h"

#include "city/city.h"
#include "city/city_floods.h"
#include "core/variant.h"
#include "game/resource.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario_invasion.h"

#include <algorithm>

advisor_comment_rules_t ANK_VARIABLE(advisor_comment_rules)
chief_advisor_rules_t ANK_VARIABLE(chief_advisor_rules)

  const e_advisor_comment_topic_tokens_t ANK_CONFIG_ENUM(e_advisor_comment_topic_tokens);
const e_advisor_text_tone_tokens_t ANK_CONFIG_ENUM(e_advisor_text_tone_tokens);
const e_chief_row_number_tokens_t ANK_CONFIG_ENUM(e_chief_row_number_tokens);

namespace {

    enum e_chief_text {
        CHIEF_TEXT_SENTIMENT_LOATHED = 20,
        CHIEF_TEXT_SENTIMENT_FIRST = 21,
        CHIEF_TEXT_SENTIMENT_IDOLIZED = 31,
        CHIEF_TEXT_SENTIMENT_CAUSE_FIRST = 31,
        CHIEF_TEXT_LOATHED_CAUSE_FIRST = 32,
        CHIEF_TEXT_LOW_SENTIMENT_CAUSE_FIRST = 37,
        CHIEF_TEXT_LOW_SENTIMENT = 42,
        CHIEF_TEXT_WAR_FRIGHTENS_IMMIGRANTS = 43,
        CHIEF_TEXT_IMMIGRATING = 44,
        CHIEF_TEXT_NO_HOUSING_FOR_IMMIGRANTS = 45,
        CHIEF_TEXT_NO_IMMIGRATION_CAUSE_FIRST = 46,
        CHIEF_TEXT_IMMIGRATION_BUILD_HOUSING = 60,
        CHIEF_TEXT_IMMIGRATION_CAUSE_FIRST = 61,
        CHIEF_TEXT_MIGRATION_BALANCE_WEALTH = 67,
        CHIEF_TEXT_IMMIGRATION_RAISE_SENTIMENT = 68,
        CHIEF_TEXT_MIGRATION_BUILD_HOUSING = 69,
        CHIEF_TEXT_STAY_CAUSE_FIRST = 70,
        CHIEF_TEXT_UNEMPLOYMENT_ROW_URGENT = 76,
        CHIEF_TEXT_UNEMPLOYMENT_ROW_SERIOUS = 77,
        CHIEF_TEXT_UNEMPLOYMENT_ROW_IMPORTANT = 78,
        CHIEF_TEXT_UNEMPLOYMENT_ROW = 79,
        CHIEF_TEXT_SHORTAGE_ROW_URGENT = 80,
        CHIEF_TEXT_SHORTAGE_ROW_SERIOUS = 81,
        CHIEF_TEXT_SHORTAGE_ROW_IMPORTANT = 82,
        CHIEF_TEXT_SHORTAGE_ROW = 83,
        CHIEF_TEXT_NO_EMPLOYMENT_PROBLEMS = 84,
        CHIEF_TEXT_UNEMPLOYMENT_URGENT = 85,
        CHIEF_TEXT_UNEMPLOYMENT_SERIOUS = 86,
        CHIEF_TEXT_UNEMPLOYMENT_IMPORTANT = 87,
        CHIEF_TEXT_UNEMPLOYMENT_TOLERABLE = 88,
        CHIEF_TEXT_LABOR_SHORTAGE_URGENT = 89,
        CHIEF_TEXT_LABOR_SHORTAGE_SERIOUS = 90,
        CHIEF_TEXT_LABOR_SHORTAGE_IMPORTANT = 91,
        CHIEF_TEXT_EMPLOYMENT_BALANCED = 93,
        CHIEF_TEXT_CAPITAL_SUPPLIES = 94,
        CHIEF_TEXT_FOOD_ROW_URGENT = 95,
        CHIEF_TEXT_FOOD_ROW_SERIOUS = 96,
        CHIEF_TEXT_FOOD_ROW_IMPORTANT = 97,
        CHIEF_TEXT_FOOD_ROW_SUPPLIES_FOR = 98,
        CHIEF_TEXT_FOOD_STOCKS_EMPTY = 99,
        CHIEF_TEXT_FOOD_STOCKS_LOW = 100,
        CHIEF_TEXT_FOOD_STOCKS_ENOUGH = 102,
        CHIEF_TEXT_HEALTH_ROW_FIRST = 103,
        CHIEF_TEXT_HEALTH_FIRST = 114,
        CHIEF_TEXT_GODS_ROW_SEVERAL_ANGRY = 125,
        CHIEF_TEXT_GODS_ROW_THREE_ANGRY = 127,
        CHIEF_TEXT_GODS_ROW_TWO_ANGRY = 129,
        CHIEF_TEXT_GODS_ROW_ONE_ANGRY = 131,
        CHIEF_TEXT_GODS_ROW_APPEASED = 133,
        CHIEF_TEXT_GODS_SEVERAL_ANGRY = 138,
        CHIEF_TEXT_GODS_THREE_ANGRY = 140,
        CHIEF_TEXT_GODS_TWO_ANGRY = 142,
        CHIEF_TEXT_GODS_ONE_ANGRY = 144,
        CHIEF_TEXT_GODS_APPEASED = 146,
        CHIEF_TEXT_GODS_ONE_HAPPY = 147,
        CHIEF_TEXT_GODS_TWO_HAPPY = 148,
        CHIEF_TEXT_TAXES_ROW_UNCOLLECTED = 151,
        CHIEF_TEXT_ASSETS_ROW_RISEN = 152,
        CHIEF_TEXT_ASSETS_ROW_SAME = 153,
        CHIEF_TEXT_ASSETS_ROW_FALLEN = 154,
        CHIEF_TEXT_TAXES_UNCOLLECTED = 155,
        CHIEF_TEXT_TREASURY_RISING = 156,
        CHIEF_TEXT_TREASURY_STEADY = 157,
        CHIEF_TEXT_TREASURY_FALLING = 158,
        CHIEF_TEXT_THEFTS_ROW_MANY = 159,
        CHIEF_TEXT_THEFTS_ROW_SEVERAL = 160,
        CHIEF_TEXT_THEFTS_ROW_SOME = 161,
        CHIEF_TEXT_THEFTS_ROW_FEW = 162,
        CHIEF_TEXT_THEFTS_ROW_NONE = 163,
        CHIEF_TEXT_THEFTS_ROW_STOLEN = 164,
        CHIEF_TEXT_THEFTS_MANY = 165,
        CHIEF_TEXT_THEFTS_SEVERAL = 166,
        CHIEF_TEXT_THEFTS_SOME = 167,
        CHIEF_TEXT_THEFTS_FEW = 168,
        CHIEF_TEXT_THEFTS_NONE = 169,
        CHIEF_TEXT_MILITARY_ROW_NO_COMPANIES = 170,
        CHIEF_TEXT_MILITARY_ROW_NO_THREATS = 171,
        CHIEF_TEXT_MILITARY_ROW_ENEMIES_CLOSING = 172,
        CHIEF_TEXT_MILITARY_ROW_ENEMIES_ATTACKING = 173,
        CHIEF_TEXT_MILITARY_ROW_KINGDOM_SOLDIERS = 174,
        CHIEF_TEXT_MILITARY_ROW_TROOPS_NEEDED = 175,
        CHIEF_TEXT_MILITARY_ROW_TROOPS_ELSEWHERE = 176,
        CHIEF_TEXT_MILITARY_NO_FORCES = 177,
        CHIEF_TEXT_MILITARY_WATCHING = 178,
        CHIEF_TEXT_ENEMY_ADVANCING = 179,
        CHIEF_TEXT_ENEMIES_AT_CITY = 180,
        CHIEF_TEXT_KINGDOM_SOLDIERS_AT_CITY = 181,
        CHIEF_TEXT_TROOPS_REQUESTED = 182,
        CHIEF_TEXT_TROOPS_ABROAD = 183,
        CHIEF_TEXT_REQUESTS_ROW_MANY = 184,
        CHIEF_TEXT_REQUESTS_ROW_SOME = 186,
        CHIEF_TEXT_REQUESTS_ROW_NONE = 187,
        CHIEF_TEXT_REQUESTS_MANY = 188,
        CHIEF_TEXT_REQUESTS_SEVERAL = 189,
        CHIEF_TEXT_REQUESTS_SOME = 190,
        CHIEF_TEXT_REQUESTS_NONE = 191,
        CHIEF_TEXT_FLOOD_ROW_FIRST = 192,
        CHIEF_TEXT_FLOOD_FORECAST_FIRST = 198,
        CHIEF_TEXT_FLOOD_MONTH_FIRST = 204,
        CHIEF_TEXT_FOOD_SUPPLY_FAR_SHORT = 212,
        CHIEF_TEXT_FOOD_SUPPLY_SHORT = 213,
        CHIEF_TEXT_FOOD_SUPPLY_SLIGHTLY_SHORT = 214,
        CHIEF_TEXT_FOOD_SUPPLY_BARELY_ENOUGH = 215,
        CHIEF_TEXT_FOOD_SUPPLY_ENOUGH = 216,
        CHIEF_TEXT_FOOD_SUPPLY_PLENTY = 217,
        CHIEF_TEXT_FOOD_ROW_PLENTY = 13,
        CHIEF_TEXT_FOOD_ROW_ENOUGH = 14,
        CHIEF_TEXT_FOOD_ROW_JUST_ENOUGH = 15,
        CHIEF_TEXT_FOOD_ROW_SLIGHTLY_SHORT = 16,
        CHIEF_TEXT_FOOD_ROW_SHORT = 17,
        CHIEF_TEXT_FOOD_ROW_FAR_SHORT = 18,
    };

    enum {
        GOD_COUNT_OG = 5,
        TEXT_GROUP_NUMBERS = 8,
        TEXT_GROUP_CHIEF_ADVISOR = 61,
        TEXT_MONTHS_SUFFIX = 5,
        TEXT_WORKERS_SUFFIX = 13,
        // OG troop request states (advisor_comments.c troop_request_state).
        TROOP_REQUEST_ABROAD = 5,
        TROOP_REQUEST_RETURNING = 6,
        TROOP_REQUEST_RETURNING_LATE = 7,
    };

    bvariant_map g_state_override;

    int food_supply_per_population(const advisor_city_state& s) {
        return (s.food_supply_percentage * 100) / s.population;
    }

    int requests_counted(const advisor_city_state& s, int cap) {
        return std::min(s.requests_waiting, cap);
    }

    chief_advisor_row sentiment_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        const int sentiment = s.sentiment;
        if (sentiment < 1) {
            row.text = CHIEF_TEXT_SENTIMENT_LOATHED;
            row.tone = ADVISOR_TONE_RED;
            if (s.low_mood_cause != 0) {
                row.cause_text = s.low_mood_cause + CHIEF_TEXT_LOATHED_CAUSE_FIRST;
            }
            return row;
        }
        if (sentiment > 99) {
            row.text = CHIEF_TEXT_SENTIMENT_IDOLIZED;
            row.tone = ADVISOR_TONE_GREEN;
            return row;
        }
        row.tone = (sentiment >= r.sentiment_green_from)   ? ADVISOR_TONE_GREEN
                   : (sentiment >= r.sentiment_white_from) ? ADVISOR_TONE_WHITE
                                                           : ADVISOR_TONE_RED;
        row.text = sentiment / 10 + CHIEF_TEXT_SENTIMENT_FIRST;
        if (sentiment < r.sentiment_cause_below && s.low_mood_cause != 0) {
            row.cause_text = s.low_mood_cause + CHIEF_TEXT_SENTIMENT_CAUSE_FIRST;
        }
        return row;
    }

    // OG never writes migration_direction, so only its "none" branch is reachable.
    chief_advisor_row migration_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        row.tone = ADVISOR_TONE_RED;
        if (s.migration_direction == 0) {
            if (s.kingdom_soldiers + s.enemies > r.migration_max_armed_figures) {
                row.text = CHIEF_TEXT_WAR_FRIGHTENS_IMMIGRANTS;
            } else if (s.newcomers >= r.migration_newcomers_strong) {
                row.text = CHIEF_TEXT_IMMIGRATING;
                row.tone = ADVISOR_TONE_GREEN;
            } else if (s.refused_immigrants_today != 0 || s.room_in_houses <= 0) {
                row.text = CHIEF_TEXT_NO_HOUSING_FOR_IMMIGRANTS;
            } else if (s.migration_percentage < r.migration_percentage_strong) {
                row.text = CHIEF_TEXT_NO_IMMIGRATION_CAUSE_FIRST + s.no_immigration_cause;
            } else {
                row.text = CHIEF_TEXT_IMMIGRATING;
                row.tone = ADVISOR_TONE_GREEN;
            }
        } else if (s.migration_direction == 1) {
            const bool has_room = s.refused_immigrants_today == 0 && s.room_in_houses > 0;
            row.text = has_room ? (s.no_immigration_cause + 53) : 52;
        } else {
            row.text = 59;
            row.tone = ADVISOR_TONE_GREEN;
        }
        return row;
    }

    chief_advisor_row labor_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        const int unemployment = s.unemployment_percentage;
        const int needed = s.workers_needed;
        if (unemployment < r.employment_balanced_below && needed < r.employment_balanced_below) {
            row.text = CHIEF_TEXT_NO_EMPLOYMENT_PROBLEMS;
            row.tone = ADVISOR_TONE_GREEN;
            return row;
        }

        if (unemployment >= r.unemployment_urgent) {
            row.text = CHIEF_TEXT_UNEMPLOYMENT_ROW_URGENT;
            row.tone = ADVISOR_TONE_RED;
        } else if (unemployment >= r.unemployment_serious) {
            row.text = CHIEF_TEXT_UNEMPLOYMENT_ROW_SERIOUS;
            row.tone = ADVISOR_TONE_WHITE;
        } else if (unemployment >= r.unemployment_important) {
            row.text = CHIEF_TEXT_UNEMPLOYMENT_ROW_IMPORTANT;
            row.tone = ADVISOR_TONE_GREEN;
        } else if (unemployment >= r.unemployment_tolerable) {
            row.text = CHIEF_TEXT_UNEMPLOYMENT_ROW;
            row.tone = ADVISOR_TONE_GREEN;
        } else if (needed >= r.workers_needed_urgent) {
            row.text = CHIEF_TEXT_SHORTAGE_ROW_URGENT;
            row.tone = ADVISOR_TONE_RED;
        } else if (needed >= r.workers_needed_serious) {
            row.text = CHIEF_TEXT_SHORTAGE_ROW_SERIOUS;
            row.tone = ADVISOR_TONE_WHITE;
        } else if (needed >= r.workers_needed_important) {
            row.text = CHIEF_TEXT_SHORTAGE_ROW_IMPORTANT;
            row.tone = ADVISOR_TONE_GREEN;
        } else {
            row.text = (needed > 0) ? CHIEF_TEXT_SHORTAGE_ROW : CHIEF_TEXT_UNEMPLOYMENT_ROW_URGENT;
            row.tone = ADVISOR_TONE_GREEN;
        }

        if (unemployment < r.unemployment_tolerable) {
            if (needed > 0) {
                row.number = needed;
                row.number_kind = CHIEF_NUMBER_PLAIN;
                row.suffix_group = TEXT_GROUP_NUMBERS;
                row.suffix_text = TEXT_WORKERS_SUFFIX;
            }
        } else {
            row.number = unemployment;
            row.number_kind = CHIEF_NUMBER_PERCENT;
        }
        return row;
    }

    chief_advisor_row food_stocks_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        row.tone = ADVISOR_TONE_GREEN;
        if (s.kingdom_supplies_grain) {
            row.text = CHIEF_TEXT_CAPITAL_SUPPLIES;
        } else if (s.food_supply_months < 1) {
            row.text = CHIEF_TEXT_FOOD_ROW_URGENT;
            row.tone = ADVISOR_TONE_RED;
        } else if (s.food_needed_per_month > 0
                   && (s.food_stored_total * 100) / s.food_needed_per_month < r.food_stocks_low_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_SERIOUS;
            row.tone = ADVISOR_TONE_WHITE;
        } else {
            row.text = CHIEF_TEXT_FOOD_ROW_SUPPLIES_FOR;
            row.number = s.food_supply_months;
            row.number_kind = CHIEF_NUMBER_PLAIN;
            row.suffix_group = TEXT_GROUP_NUMBERS;
            row.suffix_text = TEXT_MONTHS_SUFFIX;
        }
        return row;
    }

    chief_advisor_row food_consumption_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        row.text = CHIEF_TEXT_FOOD_ROW_FAR_SHORT;
        row.tone = ADVISOR_TONE_RED;
        if (s.population == 0) {
            return row;
        }

        const int pct = food_supply_per_population(s);
        row.tone = ADVISOR_TONE_GREEN;
        if (pct > r.food_supply_plenty_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_PLENTY;
        } else if (pct > r.food_supply_enough_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_ENOUGH;
        } else if (pct > r.food_supply_barely_enough_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_JUST_ENOUGH;
        } else if (pct > r.food_supply_slightly_short_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_SLIGHTLY_SHORT;
        } else if (pct > r.food_supply_short_percent) {
            row.text = CHIEF_TEXT_FOOD_ROW_SHORT;
            row.tone = ADVISOR_TONE_WHITE;
        } else {
            row.text = CHIEF_TEXT_FOOD_ROW_FAR_SHORT;
            row.tone = ADVISOR_TONE_RED;
        }
        return row;
    }

    chief_advisor_row health_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        const int health = std::clamp(s.health, 0, 100);
        row.tone = (health >= r.health_green_from)   ? ADVISOR_TONE_GREEN
                   : (health >= r.health_white_from) ? ADVISOR_TONE_WHITE
                                                     : ADVISOR_TONE_RED;
        row.text = health / 10 + CHIEF_TEXT_HEALTH_ROW_FIRST;
        return row;
    }

    chief_advisor_row religion_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        int angry = 0;
        int happy = 0;
        int lowest = 100;
        for (int god = 0; god < GOD_COUNT_OG; god++) {
            const int mood = s.god_mood(god);
            if (mood < r.angry_god_mood) {
                angry++;
            }
            if (mood > r.happy_god_mood) {
                happy++;
            }
            lowest = std::min(lowest, mood);
        }

        chief_advisor_row row;
        row.tone = ADVISOR_TONE_GREEN;
        if (angry == 0) {
            row.text = CHIEF_TEXT_GODS_ROW_APPEASED + std::min(happy, 4);
            return row;
        }

        const int first = (angry >= 4)   ? CHIEF_TEXT_GODS_ROW_SEVERAL_ANGRY
                          : (angry == 3) ? CHIEF_TEXT_GODS_ROW_THREE_ANGRY
                          : (angry == 2) ? CHIEF_TEXT_GODS_ROW_TWO_ANGRY
                                         : CHIEF_TEXT_GODS_ROW_ONE_ANGRY;
        const bool very_angry = lowest < r.very_angry_god_mood;
        row.text = first + (very_angry ? 1 : 0);
        row.tone = very_angry ? ADVISOR_TONE_WHITE : ADVISOR_TONE_GREEN;
        return row;
    }

    chief_advisor_row finance_row(const advisor_city_state& s) {
        chief_advisor_row row;
        row.tone = ADVISOR_TONE_WHITE;
        if (s.taxes_uncollected != 0 && s.taxes_collected / s.taxes_uncollected <= 0) {
            row.text = CHIEF_TEXT_TAXES_ROW_UNCOLLECTED;
            return row;
        }

        if (s.balance_last_year < s.treasury) {
            row.text = CHIEF_TEXT_ASSETS_ROW_RISEN;
            row.tone = ADVISOR_TONE_GREEN;
            row.number = s.treasury - s.balance_last_year;
            row.number_kind = CHIEF_NUMBER_MONEY;
        } else if (s.treasury < s.balance_last_year) {
            row.text = CHIEF_TEXT_ASSETS_ROW_FALLEN;
            row.number = s.balance_last_year - s.treasury;
            row.number_kind = CHIEF_NUMBER_MONEY;
        } else {
            row.text = CHIEF_TEXT_ASSETS_ROW_SAME;
            row.tone = ADVISOR_TONE_GREEN;
        }
        return row;
    }

    chief_advisor_row crime_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        const int thefts = s.crimes_this_month;
        row.tone = ADVISOR_TONE_GREEN;
        if (thefts >= r.thefts_many) {
            row.text = CHIEF_TEXT_THEFTS_ROW_MANY;
            row.tone = ADVISOR_TONE_RED;
        } else if (thefts == 0) {
            row.text = CHIEF_TEXT_THEFTS_ROW_NONE;
            return row;
        } else if (thefts < r.thefts_some) {
            row.text = CHIEF_TEXT_THEFTS_ROW_FEW;
        } else if (thefts < r.thefts_several) {
            row.text = CHIEF_TEXT_THEFTS_ROW_SOME;
        } else {
            row.text = CHIEF_TEXT_THEFTS_ROW_SEVERAL;
            row.tone = ADVISOR_TONE_WHITE;
        }
        row.number = s.gold_stolen_this_month;
        row.number_kind = CHIEF_NUMBER_PLAIN;
        row.suffix_group = TEXT_GROUP_CHIEF_ADVISOR;
        row.suffix_text = CHIEF_TEXT_THEFTS_ROW_STOLEN;
        return row;
    }

    chief_advisor_row military_row(const advisor_city_state& s) {
        chief_advisor_row row;
        row.tone = ADVISOR_TONE_GREEN;
        if (s.kingdom_soldiers != 0) {
            row.text = CHIEF_TEXT_MILITARY_ROW_KINGDOM_SOLDIERS;
            row.tone = ADVISOR_TONE_RED;
        } else if (s.enemies != 0) {
            row.text = CHIEF_TEXT_MILITARY_ROW_ENEMIES_ATTACKING;
            row.tone = ADVISOR_TONE_RED;
        } else if (s.invasion_running != 0) {
            row.text = CHIEF_TEXT_MILITARY_ROW_ENEMIES_CLOSING;
            row.tone = ADVISOR_TONE_RED;
        } else if (s.troops_away != 0) {
            row.text = CHIEF_TEXT_MILITARY_ROW_TROOPS_ELSEWHERE;
        } else if (s.troops_requested != 0) {
            row.text = CHIEF_TEXT_MILITARY_ROW_TROOPS_NEEDED;
        } else {
            row.text = (s.soldiers >= 0) ? CHIEF_TEXT_MILITARY_ROW_NO_THREATS : CHIEF_TEXT_MILITARY_ROW_NO_COMPANIES;
        }
        return row;
    }

    chief_advisor_row requests_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        row.tone = ADVISOR_TONE_GREEN;
        const int count = requests_counted(s, r.requests_counted);
        if (count == 0) {
            row.text = CHIEF_TEXT_REQUESTS_ROW_NONE;
        } else if (count <= r.requests_some_max) {
            row.text = CHIEF_TEXT_REQUESTS_ROW_SOME;
        } else {
            row.text = CHIEF_TEXT_REQUESTS_ROW_MANY + ((count <= r.requests_several_max) ? 1 : 0);
        }
        return row;
    }

    chief_advisor_row nile_row(const advisor_city_state& s, const chief_advisor_rules_t& r) {
        chief_advisor_row row;
        const int step = std::max(1, r.flood_quality_step);
        const int level = (s.flood_quality + step - 1) / step;
        row.tone = (level == 0) ? ADVISOR_TONE_RED : (level == 1) ? ADVISOR_TONE_WHITE : ADVISOR_TONE_GREEN;
        row.text = level + CHIEF_TEXT_FLOOD_ROW_FIRST;
        if (level != 0) {
            row.second_text = CHIEF_TEXT_FLOOD_MONTH_FIRST + s.flood_month;
        }
        return row;
    }

    int sentiment_comment(const advisor_city_state& s, const advisor_comment_rules_t& r, e_advisor& advisor) {
        switch (s.low_mood_cause) {
        case LOW_MOOD_NO_FOOD:
        case LOW_MOOD_MANY_TENTS:
            advisor = ADVISOR_POPULATION;
            break;
        case LOW_MOOD_NO_JOBS:
        case LOW_MOOD_LOW_WAGES:
            advisor = ADVISOR_LABOR;
            break;
        case LOW_MOOD_HIGH_TAXES:
            advisor = ADVISOR_FINANCIAL;
            break;
        }
        if (s.sentiment < r.sentiment_low) {
            return CHIEF_TEXT_LOW_SENTIMENT_CAUSE_FIRST + s.low_mood_cause;
        }
        if (s.sentiment < r.sentiment_fair) {
            advisor = ADVISOR_NONE;
            return CHIEF_TEXT_LOW_SENTIMENT;
        }
        return -1;
    }

    int migration_comment(const advisor_city_state& s, const advisor_comment_rules_t& r, e_advisor& advisor) {
        const int cause = s.no_immigration_cause;
        switch (cause) {
        case NO_IMMIGRATION_LOW_WAGES:
        case NO_IMMIGRATION_NO_JOBS:
            advisor = ADVISOR_LABOR;
            break;
        case NO_IMMIGRATION_NO_FOOD:
        case NO_IMMIGRATION_HIGH_TAXES:
            advisor = ADVISOR_POPULATION;
            break;
        }
        const bool has_room = (s.refused_immigrants_today == 0) && (s.room_in_houses > 0);
        if (s.migration_direction == 1) {
            if (s.kingdom_soldiers + s.enemies > r.migration_max_armed_figures) {
                return -1;
            }
            if (s.newcomers >= r.migration_newcomers_strong) {
                advisor = ADVISOR_NONE;
                return CHIEF_TEXT_IMMIGRATION_RAISE_SENTIMENT;
            }
            if (!has_room) {
                advisor = ADVISOR_POPULATION;
                return CHIEF_TEXT_IMMIGRATION_BUILD_HOUSING;
            }
            if (s.migration_percentage >= r.migration_percentage_strong) {
                advisor = ADVISOR_NONE;
                return CHIEF_TEXT_IMMIGRATION_RAISE_SENTIMENT;
            }
            return CHIEF_TEXT_IMMIGRATION_CAUSE_FIRST + cause;
        }
        if (s.migration_direction == 0) {
            if (has_room) {
                return CHIEF_TEXT_STAY_CAUSE_FIRST + cause;
            }
            advisor = ADVISOR_POPULATION;
            return CHIEF_TEXT_MIGRATION_BUILD_HOUSING;
        }
        advisor = ADVISOR_NONE;
        return CHIEF_TEXT_MIGRATION_BALANCE_WEALTH;
    }

    int employment_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        const int unemployment = s.unemployment_percentage;
        const int needed = s.workers_needed;
        if (unemployment <= r.employment_balanced_unemployment && needed <= r.employment_balanced_workers_needed) {
            return CHIEF_TEXT_EMPLOYMENT_BALANCED;
        }
        if (unemployment > r.unemployment_urgent) {
            return CHIEF_TEXT_UNEMPLOYMENT_URGENT;
        }
        if (unemployment > r.unemployment_serious) {
            return CHIEF_TEXT_UNEMPLOYMENT_SERIOUS;
        }
        if (unemployment > r.unemployment_important) {
            return CHIEF_TEXT_UNEMPLOYMENT_IMPORTANT;
        }
        if (unemployment > 0) {
            return CHIEF_TEXT_UNEMPLOYMENT_TOLERABLE;
        }
        if (needed > r.labor_shortage_urgent) {
            return CHIEF_TEXT_LABOR_SHORTAGE_URGENT;
        }
        if (needed > r.labor_shortage_serious) {
            return CHIEF_TEXT_LABOR_SHORTAGE_SERIOUS;
        }
        return CHIEF_TEXT_LABOR_SHORTAGE_IMPORTANT;
    }

    int food_stocks_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        if (s.food_supply_months <= 0) {
            return CHIEF_TEXT_FOOD_STOCKS_EMPTY;
        }
        if (s.food_needed_per_month > 0
            && (s.food_stored_total * 100) / s.food_needed_per_month < r.food_stocks_low_percent) {
            return CHIEF_TEXT_FOOD_STOCKS_LOW;
        }
        return CHIEF_TEXT_FOOD_STOCKS_ENOUGH;
    }

    int food_consumption_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        if (s.population == 0) {
            return CHIEF_TEXT_FOOD_SUPPLY_FAR_SHORT;
        }
        const int pct = food_supply_per_population(s);
        if (pct > r.food_supply_plenty_percent) {
            return CHIEF_TEXT_FOOD_SUPPLY_PLENTY;
        }
        if (pct > r.food_supply_enough_percent) {
            return CHIEF_TEXT_FOOD_SUPPLY_ENOUGH;
        }
        if (pct > r.food_supply_barely_enough_percent) {
            return CHIEF_TEXT_FOOD_SUPPLY_BARELY_ENOUGH;
        }
        if (pct > r.food_supply_slightly_short_percent) {
            return CHIEF_TEXT_FOOD_SUPPLY_SLIGHTLY_SHORT;
        }
        if (pct > r.food_supply_short_percent) {
            return CHIEF_TEXT_FOOD_SUPPLY_SHORT;
        }
        return CHIEF_TEXT_FOOD_SUPPLY_FAR_SHORT;
    }

    int religion_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        int angry = 0;
        int happy = 0;
        int lowest = 100;
        for (int god = 0; god < GOD_COUNT_OG; god++) {
            const int mood = s.god_mood(god);
            if (mood < r.angry_god_mood) {
                angry++;
            }
            lowest = std::min(lowest, mood);
            if (mood > r.happy_god_mood) {
                happy++;
            }
        }
        auto angry_text = [&](int text) { return (lowest < r.very_angry_god_mood) ? (text + 1) : text; };
        if (angry > 3) {
            return angry_text(CHIEF_TEXT_GODS_SEVERAL_ANGRY);
        }
        if (angry == 3) {
            return angry_text(CHIEF_TEXT_GODS_THREE_ANGRY);
        }
        if (angry == 2) {
            return angry_text(CHIEF_TEXT_GODS_TWO_ANGRY);
        }
        if (angry == 1) {
            return angry_text(CHIEF_TEXT_GODS_ONE_ANGRY);
        }
        if (happy == 0) {
            return CHIEF_TEXT_GODS_APPEASED;
        }
        if (happy == 1) {
            return CHIEF_TEXT_GODS_ONE_HAPPY;
        }
        if (happy == 2) {
            return CHIEF_TEXT_GODS_TWO_HAPPY;
        }
        return -1;
    }

    int finances_comment(const advisor_city_state& s) {
        if (s.taxes_uncollected != 0 && (s.taxes_collected / s.taxes_uncollected) < 1) {
            return CHIEF_TEXT_TAXES_UNCOLLECTED;
        }
        if (s.treasury > s.balance_last_year) {
            return CHIEF_TEXT_TREASURY_RISING;
        }
        if (s.treasury < s.balance_last_year) {
            return CHIEF_TEXT_TREASURY_FALLING;
        }
        return CHIEF_TEXT_TREASURY_STEADY;
    }

    int crime_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        const int thefts = s.crimes_this_month;
        if (thefts >= r.thefts_many) {
            return CHIEF_TEXT_THEFTS_MANY;
        }
        if (thefts == 0) {
            return CHIEF_TEXT_THEFTS_NONE;
        }
        if (thefts < r.thefts_some) {
            return CHIEF_TEXT_THEFTS_FEW;
        }
        if (thefts < r.thefts_several) {
            return CHIEF_TEXT_THEFTS_SOME;
        }
        return CHIEF_TEXT_THEFTS_SEVERAL;
    }

    int military_comment(const advisor_city_state& s) {
        if (s.kingdom_soldiers != 0) {
            return CHIEF_TEXT_KINGDOM_SOLDIERS_AT_CITY;
        }
        if (s.enemies != 0) {
            return CHIEF_TEXT_ENEMIES_AT_CITY;
        }
        if (s.invasion_running != 0) {
            return CHIEF_TEXT_ENEMY_ADVANCING;
        }
        if (s.troops_away != 0) {
            return CHIEF_TEXT_TROOPS_ABROAD;
        }
        if (s.troops_requested != 0) {
            return CHIEF_TEXT_TROOPS_REQUESTED;
        }
        return (s.soldiers >= 0) ? CHIEF_TEXT_MILITARY_WATCHING : CHIEF_TEXT_MILITARY_NO_FORCES;
    }

    int kingdom_comment(const advisor_city_state& s, const advisor_comment_rules_t& r) {
        const int count = requests_counted(s, r.requests_counted);
        if (count == 0) {
            return CHIEF_TEXT_REQUESTS_NONE;
        }
        if (count <= r.requests_some_max) {
            return CHIEF_TEXT_REQUESTS_SOME;
        }
        if (count <= r.requests_several_max) {
            return CHIEF_TEXT_REQUESTS_SEVERAL;
        }
        return CHIEF_TEXT_REQUESTS_MANY;
    }

    void gather_requests(advisor_city_state& s) {
        for (int i = 0, size = g_scenario.events.events_count(); i < size; i++) {
            const event_ph_t* e = g_scenario.events.at(i);
            if (!e || e->type != EVENT_TYPE_REQUEST || !e->is_active) {
                continue;
            }
            const bool waiting = e->event_state <= e_event_state_in_progress;
            if (e->item.value == RESOURCE_TROOPS) {
                s.troops_requested |= waiting ? 1 : 0;
                const int state = e->event_state;
                if (state == TROOP_REQUEST_ABROAD || state == TROOP_REQUEST_RETURNING
                    || state == TROOP_REQUEST_RETURNING_LATE) {
                    s.troops_away = 1;
                }
            }
            if (waiting && e->item.value != 0) {
                s.requests_waiting++;
            }
        }
    }

} // namespace

int advisor_city_state::god_mood(int god) const {
    switch (god) {
    case 0:
        return god_mood0;
    case 1:
        return god_mood1;
    case 2:
        return god_mood2;
    case 3:
        return god_mood3;
    default:
        return god_mood4;
    }
}

advisor_city_state advisor_city_state_current() {
    advisor_city_state s;
    s.sentiment = g_city.sentiment.value;
    s.low_mood_cause = g_city.sentiment.low_mood_cause;
    s.kingdom_soldiers = g_city.figures.kingdome_soldiers;
    s.enemies = g_city.figures.enemies;
    s.soldiers = g_city.figures.soldiers;
    s.newcomers = g_city.migration.newcomers;
    s.refused_immigrants_today = g_city.migration.refused_immigrants_today;
    s.room_in_houses = g_city.population.room_in_houses;
    s.migration_percentage = g_city.migration.percentage;
    s.no_immigration_cause = g_city.migration.no_immigration_cause;
    s.unemployment_percentage = g_city.labor.unemployment_percentage;
    s.workers_needed = g_city.labor.workers_needed;
    s.kingdom_supplies_grain = g_scenario.kingdom_supplies_grain;
    s.food_supply_months = g_city.resource.food_supply_months;
    s.food_stored_total = (int)g_city.resource.granary_total_stored;
    s.food_needed_per_month = g_city.resource.food_needed_per_month;
    s.population = g_city.population.current;
    s.food_supply_percentage = g_city.food_supply.percentage();
    s.health = g_city.health.value;
    s.god_mood0 = g_city.religion.gods[0].target_mood;
    s.god_mood1 = g_city.religion.gods[1].target_mood;
    s.god_mood2 = g_city.religion.gods[2].target_mood;
    s.god_mood3 = g_city.religion.gods[3].target_mood;
    s.god_mood4 = g_city.religion.gods[4].target_mood;
    s.taxes_collected = g_city.taxes.yearly.collected_citizens + g_city.taxes.yearly.collected_nobles;
    s.taxes_uncollected = g_city.taxes.yearly.uncollected_citizens + g_city.taxes.yearly.uncollected_nobles;
    s.treasury = g_city.finance.treasury;
    s.balance_last_year = g_city.finance.last_year.balance;
    s.crimes_this_month = g_city.finance.crimes_this_month;
    s.gold_stolen_this_month = g_city.finance.gold_stolen_this_month;
    s.invasion_running = scenario_invasion_exists_upcoming() ? 1 : 0;
    gather_requests(s);
    s.flood_quality = g_floods.expected_quality();
    s.flood_month = g_floods.expected_month();

    for (const auto& [name, value] : g_state_override) {
        archive_helper::set(s, name, value, true);
    }
    return s;
}

void advisor_city_state_override(const xstring& name, int value) {
    g_state_override[name] = bvariant(value);
}

void advisor_city_state_clear_override() {
    g_state_override = bvariant_map{};
}

chief_advisor_row chief_advisor_row_for(int topic, const advisor_city_state& s, const chief_advisor_rules_t& rules) {
    switch (topic) {
    case ADVISOR_COMMENT_SENTIMENT:
        return sentiment_row(s, rules);
    case ADVISOR_COMMENT_MIGRATION:
        return migration_row(s, rules);
    case ADVISOR_COMMENT_EMPLOYMENT:
        return labor_row(s, rules);
    case ADVISOR_COMMENT_FOOD_STOCKS:
        return food_stocks_row(s, rules);
    case ADVISOR_COMMENT_FOOD_CONSUMPTION:
        return food_consumption_row(s, rules);
    case ADVISOR_COMMENT_HEALTH:
        return health_row(s, rules);
    case ADVISOR_COMMENT_RELIGION:
        return religion_row(s, rules);
    case ADVISOR_COMMENT_FINANCES:
        return finance_row(s);
    case ADVISOR_COMMENT_CRIME:
        return crime_row(s, rules);
    case ADVISOR_COMMENT_MILITARY:
        return military_row(s);
    case ADVISOR_COMMENT_KINGDOM:
        return requests_row(s, rules);
    case ADVISOR_COMMENT_NILOMETER:
        return nile_row(s, rules);
    default:
        return chief_advisor_row{};
    }
}

advisor_comment advisor_comment_for(int topic, const advisor_city_state& s, const advisor_comment_rules_t& rules) {
    advisor_comment c;
    switch (topic) {
    case ADVISOR_COMMENT_SENTIMENT:
        c.text = sentiment_comment(s, rules, c.advisor);
        break;
    case ADVISOR_COMMENT_MIGRATION:
        c.text = migration_comment(s, rules, c.advisor);
        break;
    case ADVISOR_COMMENT_EMPLOYMENT:
        c.advisor = ADVISOR_LABOR;
        c.text = employment_comment(s, rules);
        break;
    case ADVISOR_COMMENT_FOOD_STOCKS:
        c.advisor = ADVISOR_POPULATION;
        c.text = food_stocks_comment(s, rules);
        break;
    case ADVISOR_COMMENT_FOOD_CONSUMPTION:
        c.advisor = ADVISOR_POPULATION;
        c.text = food_consumption_comment(s, rules);
        break;
    case ADVISOR_COMMENT_HEALTH:
        c.advisor = ADVISOR_HEALTH;
        c.text = CHIEF_TEXT_HEALTH_FIRST + std::clamp(s.health, 0, 100) / 10;
        break;
    case ADVISOR_COMMENT_RELIGION:
        c.advisor = ADVISOR_RELIGION;
        c.text = religion_comment(s, rules);
        break;
    case ADVISOR_COMMENT_FINANCES:
        c.advisor = ADVISOR_FINANCIAL;
        c.text = finances_comment(s);
        break;
    case ADVISOR_COMMENT_CRIME:
        c.advisor = ADVISOR_FINANCIAL;
        c.text = crime_comment(s, rules);
        break;
    case ADVISOR_COMMENT_MILITARY:
        c.advisor = ADVISOR_MILITARY;
        c.text = military_comment(s);
        break;
    case ADVISOR_COMMENT_KINGDOM:
        c.advisor = ADVISOR_KINGDOM;
        c.text = kingdom_comment(s, rules);
        break;
    case ADVISOR_COMMENT_NILOMETER:
        c.advisor = ADVISOR_POPULATION;
        c.text = CHIEF_TEXT_FLOOD_FORECAST_FIRST + (s.flood_quality + 19) / 20;
        break;
    default:
        break;
    }
    return c;
}

// OG draw_migration_panel (window/advisor/population.c): the food line, shifted by the migration trend.
int population_advisor_food_text(const advisor_city_state& s, const chief_advisor_rules_t& r) {
    const int pct = (s.population == 0) ? 0 : food_supply_per_population(s);
    int text = 36;
    if (pct > r.food_supply_plenty_percent) {
        text = 51;
    } else if (pct > r.food_supply_enough_percent) {
        text = 48;
    } else if (pct > r.food_supply_barely_enough_percent) {
        text = 45;
    } else if (pct > r.food_supply_slightly_short_percent) {
        text = 42;
    } else if (pct > r.food_supply_short_percent) {
        text = 39;
    }
    if (s.migration_percentage < 0) {
        text += 1;
    } else if (s.migration_percentage > 0) {
        text += 2;
    }
    return text;
}

// OG chief_advisor_button_row (file_dialog_buttons.c).
bool chief_advisor_row_opens_comment(int topic, const advisor_city_state& s, const advisor_comment_rules_t& rules) {
    if (topic == ADVISOR_COMMENT_MIGRATION && s.migration_direction == 0) {
        return s.kingdom_soldiers + s.enemies <= rules.migration_max_armed_figures;
    }
    if (topic == ADVISOR_COMMENT_SENTIMENT && s.sentiment == rules.sentiment_fair) {
        return false;
    }
    return true;
}

static bvariant_map chief_advisor_row_to_map(const chief_advisor_row& row) {
    bvariant_map m;
    m["text"] = bvariant(row.text);
    m["tone"] = bvariant(row.tone);
    m["cause_text"] = bvariant(row.cause_text);
    m["number"] = bvariant(row.number);
    m["number_kind"] = bvariant(row.number_kind);
    m["suffix_group"] = bvariant(row.suffix_group);
    m["suffix_text"] = bvariant(row.suffix_text);
    m["second_text"] = bvariant(row.second_text);
    return m;
}

bvariant_map __chief_advisor_row(int topic) {
    return chief_advisor_row_to_map(chief_advisor_row_for(topic, advisor_city_state_current(), chief_advisor_rules));
}
ANK_FUNCTION_1(__chief_advisor_row)

bvariant_map __advisor_comment(int topic) {
    const advisor_comment c = advisor_comment_for(topic, advisor_city_state_current(), advisor_comment_rules);
    bvariant_map m;
    m["text"] = bvariant(c.text);
    m["advisor"] = bvariant((int)c.advisor);
    return m;
}
ANK_FUNCTION_1(__advisor_comment)

bool __chief_advisor_row_opens_comment(int topic) {
    return chief_advisor_row_opens_comment(topic, advisor_city_state_current(), advisor_comment_rules);
}
ANK_FUNCTION_1(__chief_advisor_row_opens_comment)

bvariant_map __population_advisor_food() {
    const advisor_city_state s = advisor_city_state_current();
    bvariant_map m;
    m["people"] = bvariant(s.food_supply_percentage);
    m["text"] = bvariant(population_advisor_food_text(s, chief_advisor_rules));
    return m;
}
ANK_FUNCTION(__population_advisor_food)
