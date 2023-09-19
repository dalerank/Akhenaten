#include "sentiment.h"

#include "building/building.h"
#include "building/model.h"
#include "building/count.h"
#include "city/constants.h"
#include "city/data_private.h"
#include "city/message.h"
#include "city/population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/difficulty.h"
#include "game/tutorial.h"
#include "game/time.h"
#include "config/config.h"
#include "city/coverage.h"

#include <algorithm>

static const int SENTIMENT_PER_TAX_RATE[26] = {3, 2, 2, 2, 1, 1, 1, 0, 0, -1, -2, -2, -3, -3, -3, -5, -5, -5, -5, -6, -6, -6, -6, -6, -6, -6};

int city_sentiment(void) {
    return city_data.sentiment.value;
}

void city_set_can_create_mugger(bool v) { city_data.sentiment.can_create_mugger = v; }
bool city_can_create_mugger() {
    return city_data.sentiment.can_create_mugger;
}

void city_set_can_create_protestor(bool v) { city_data.sentiment.can_create_protestor = v; }
bool city_can_create_protestor() {
    return city_data.sentiment.can_create_protestor;
}

int city_sentiment_low_mood_cause() {
    return city_data.sentiment.low_mood_cause;
}

void city_show_message_criminal(int message_id, int money_stolen, int tile_offset) {
    bool show_popup_message = false;
    if (city_data.sentiment.last_mugger_message <= 0) {
        city_data.sentiment.last_mugger_message = 90;
        show_popup_message = true;
    }

    city_message_post(show_popup_message, MESSAGE_TUTORIAL_CRIME, money_stolen, tile_offset);
}

void city_sentiment_change_happiness(int amount) {
    buildings_valid_do([amount] (building &b) {
        if (b.house_size)
            b.sentiment.house_happiness = calc_bound(b.sentiment.house_happiness + amount, 0, 100);
    });
}

void city_sentiment_set_max_happiness(int max) {
    buildings_valid_do([max] (building &b) {
        if (b.house_size) {
            b.sentiment.house_happiness = std::min<int>(b.sentiment.house_happiness, max);
            b.sentiment.house_happiness = calc_bound(b.sentiment.house_happiness, 0, 100);
        }
    });
}

void city_sentiment_reset_protesters_criminals() {
    city_data.sentiment.protesters = 0;
    city_data.sentiment.criminals = 0;
}

void city_sentiment_add_protester() {
    city_data.sentiment.protesters++;
}

void city_sentiment_add_criminal() {
    city_data.sentiment.criminals++;
}

int city_sentiment_protesters() {
    return city_data.sentiment.protesters;
}

int city_sentiment_criminals() {
    return city_data.sentiment.criminals;
}

static int get_sentiment_penalty_for_tent_dwellers() {
    // alternate the penalty for every update
    if (!city_data.sentiment.include_tents) {
        city_data.sentiment.include_tents = true;
        return 0;
    }

    city_data.sentiment.include_tents = false;

    int penalty;
    int pct_tents = calc_percentage(city_data.population.people_in_tents, city_data.population.population);
    if (city_data.population.people_in_villas_palaces > 0) {
        if (pct_tents >= 57)
            penalty = 0;
        else if (pct_tents >= 40)
            penalty = -3;
        else if (pct_tents >= 26)
            penalty = -4;
        else if (pct_tents >= 10)
            penalty = -5;
        else {
            penalty = -6;
        }
    } else if (city_data.population.people_in_large_insula_and_above > 0) {
        if (pct_tents >= 57)
            penalty = 0;
        else if (pct_tents >= 40)
            penalty = -2;
        else if (pct_tents >= 26)
            penalty = -3;
        else if (pct_tents >= 10)
            penalty = -4;
        else {
            penalty = -5;
        }
    } else {
        if (pct_tents >= 50) {
            penalty = 1;
        } else if (pct_tents >= 40)
            penalty = 0;
        else if (pct_tents >= 26)
            penalty = -1;
        else if (pct_tents >= 10)
            penalty = -2;
        else {
            penalty = -3;
        }
    }
    return penalty;
}

static int get_sentiment_contribution_wages() {
    city_data.sentiment.wages = city_data.labor.wages;
    int contribution = 0;
    int wage_diff = city_data.labor.wages - city_data.labor.wages_kingdome;
    if (wage_diff < 0) {
        contribution = wage_diff / 2;
        if (!contribution)
            contribution = -1;

    } else if (wage_diff > 7) {
        contribution = 4;
    } else if (wage_diff > 4) {
        contribution = 3;
    } else if (wage_diff > 1) {
        contribution = 2;
    } else if (wage_diff > 0) {
        contribution = 1;
    }

    return contribution;
}

static int get_sentiment_contribution_religion_coverage() {
    if (!config_get(CONFIG_GP_CH_RELIGION_COVERAGE_INFLUENCE_SENTIMENT)) {
        return 0;
    }

    if (city_gods_knowns().size() > 0) {
        int average_coverage = 0;
        for (auto *god : city_gods_knowns()) {
            average_coverage += city_culture_coverage_religion(god->type);
        }

        average_coverage /= (int)city_gods_knowns().size();
        average_coverage /= 20; // one point for each 20% of coverage
        int religion_points = calc_bound(average_coverage, 0, 5);
        return religion_points;
    }

    return 0;
}

static int get_sentiment_contribution_employment() {
    int unemployment = city_data.sentiment.unemployment = city_data.labor.unemployment_percentage;
    if (unemployment > 25)
        return -3;
    else if (unemployment > 17)
        return -2;
    else if (unemployment > 10)
        return -1;
    else if (unemployment > 4)
        return 0;
    else {
        return 1;
    }
}

static int get_sentiment_contribution_monuments() {
    if (!config_get(CONFIG_GP_CH_MONUMENTS_INFLUENCE_SENTIMENT)) {
        return 0;
    }

    e_building_type types[] = {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST};
    int shrines = 0;
    for (auto &type : types) {
        shrines += building_count_active(type);
    }

    int shrine_points = 0;
    if (city_data.population.population > 5000) {
        shrine_points = 5;
    } if (city_data.population.population > 1000) {
        shrine_points = 10;
    } else if (city_data.population.population > 500) {
        shrine_points = 15;
    } else if (city_data.population.population > 350) {
        shrine_points = 25;
    } else if (city_data.population.population > 100) {
        shrine_points = 50;
    }
    int monument_points = calc_bound((shrines * shrine_points - city_data.population.population - 350) / 50, 0, 5);
    return monument_points;
}

void city_sentiment_update_day() {
    city_data.sentiment.last_mugger_message = std::max<short>(0, city_data.sentiment.last_mugger_message--);

    if (game_time_day() % 8 == 0) {
        city_sentiment_update();
    }
}

void city_criminals_update_day() {
    buildings_valid_do([] (building &b) {
        if (b.house_size) {
            int delta;
            if (b.sentiment.house_happiness >= 50) {
                delta = (b.sentiment.house_happiness - 50) / 30;
            } else if (b.sentiment.house_happiness < 50) {
                delta = -std::max<int>((50 - b.sentiment.house_happiness) / 10, 0);
            }

            b.house_criminal_active += delta;
            b.house_criminal_active = std::clamp<int>(b.house_criminal_active, 0, 100);
        }
    });
}

void city_sentiment_update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Sentiment Update");
    city_population_check_consistency();

    int sentiment_contribution_taxes = SENTIMENT_PER_TAX_RATE[city_data.finance.tax_percentage];
    int sentiment_contribution_wages = get_sentiment_contribution_wages();
    int sentiment_contribution_employment = get_sentiment_contribution_employment();
    int sentiment_contribution_religion_coverage = get_sentiment_contribution_religion_coverage();
    int sentiment_contribution_monuments = get_sentiment_contribution_monuments();
    int sentiment_penalty_tents = get_sentiment_penalty_for_tent_dwellers();

    city_data.sentiment.contribution_taxes = sentiment_contribution_taxes;
    city_data.sentiment.contribution_wages = sentiment_contribution_wages;
    city_data.sentiment.contribution_employment = sentiment_contribution_employment;
    city_data.sentiment.penalty_tents = sentiment_penalty_tents;
    city_data.sentiment.religion_coverage = sentiment_contribution_religion_coverage;
    city_data.sentiment.monuments = sentiment_contribution_monuments;

    int houses_calculated = 0;
    int houses_needing_food = 0;
    int total_sentiment_contribution_food = 0;
    int total_sentiment_penalty_tents = 0;
    int default_sentiment = difficulty_sentiment();

    buildings_valid_do([&] (building &b) {
        if (!b.house_size) {
            return;
        }

        if (!b.house_population) {
            b.sentiment.house_happiness = 10 + default_sentiment;
            return;
        }

        if (city_data.population.population < 300) {
            // small town has no complaints
            sentiment_contribution_employment = 0;
            sentiment_contribution_taxes = 0;
            sentiment_contribution_wages = 0;

            b.sentiment.house_happiness = default_sentiment;
            if (city_data.population.population < 200) {
                b.sentiment.house_happiness += 10;
            } else if (default_sentiment < 50 && config_get(CONFIG_GP_FIX_IMMIGRATION_BUG)) {
                // Fix very hard immigration bug: give a boost for Very Hard difficulty so that
                // immigration is not halted simply because you are between pop 200 and 300
                b.sentiment.house_happiness += 50 - default_sentiment;
            }
            return;
        }
        // population >= 300
        houses_calculated++;
        int sentiment_contribution_food = 0;
        int sentiment_contribution_tents = 0;
        if (!model_get_house(b.subtype.house_level)->food_types) {
            // tents
            b.house_days_without_food = 0;
            sentiment_contribution_tents = sentiment_penalty_tents;
            total_sentiment_penalty_tents += sentiment_penalty_tents;
        } else {
            // shack+
            houses_needing_food++;
            if (b.data.house.num_foods >= 2) {
                sentiment_contribution_food = 2;
                total_sentiment_contribution_food += 2;
                b.house_days_without_food = 0;
            } else if (b.data.house.num_foods >= 1) {
                sentiment_contribution_food = 1;
                total_sentiment_contribution_food += 1;
                b.house_days_without_food = 0;
            } else {
                // needs food but has no food
                if (b.house_days_without_food < 3)
                    b.house_days_without_food++;

                sentiment_contribution_food = -b.house_days_without_food;
                total_sentiment_contribution_food -= b.house_days_without_food;
            }
        }
        b.sentiment.house_happiness += sentiment_contribution_taxes;
        b.sentiment.house_happiness += sentiment_contribution_wages;
        b.sentiment.house_happiness += sentiment_contribution_employment;
        b.sentiment.house_happiness += sentiment_contribution_food;
        b.sentiment.house_happiness += sentiment_contribution_tents;
        b.sentiment.house_happiness += sentiment_contribution_religion_coverage;
        b.sentiment.house_happiness += sentiment_contribution_monuments;
        b.sentiment.house_happiness = calc_bound(b.sentiment.house_happiness, 0, 100);
    });

    int sentiment_contribution_food = 0;
    int sentiment_contribution_tents = 0;
    if (houses_needing_food) {
        sentiment_contribution_food = total_sentiment_contribution_food / houses_needing_food;
    }

    if (houses_calculated) {
        sentiment_contribution_tents = total_sentiment_penalty_tents / houses_calculated;
    }

    int total_sentiment = 0;
    int total_houses = 0;
    buildings_valid_do([&total_houses, &total_sentiment] (building &b) {
        if (b.house_size && b.house_population) {
            total_houses++;
            total_sentiment += b.sentiment.house_happiness;
        }
    });
    
    if (total_houses) {
        city_data.sentiment.value = total_sentiment / total_houses;
    } else {
        city_data.sentiment.value = 60;
    }

    if (city_data.sentiment.message_delay) {
        city_data.sentiment.message_delay--;
    }

    if (city_data.sentiment.value < 48 && city_data.sentiment.value < city_data.sentiment.previous_value) {
        if (city_data.sentiment.message_delay <= 0) {
            city_data.sentiment.message_delay = 3;

            if (city_data.sentiment.value < 35) {
                city_message_post(false, MESSAGE_PEOPLE_ANGRY, 0, 0);
            } else if (city_data.sentiment.value < 40) {
                city_message_post(false, MESSAGE_PEOPLE_UNHAPPY, 0, 0);
            } else {
                city_message_post(false, MESSAGE_PEOPLE_DISGRUNTLED, 0, 0);
            }
        }
    }

    int worst_sentiment = 0;
    city_data.sentiment.low_mood_cause = LOW_MOOD_NONE;
    if (sentiment_contribution_food < worst_sentiment) {
        worst_sentiment = sentiment_contribution_food;
        city_data.sentiment.low_mood_cause = LOW_MOOD_NO_FOOD;
    }

    if (sentiment_contribution_employment < worst_sentiment) {
        worst_sentiment = sentiment_contribution_employment;
        city_data.sentiment.low_mood_cause = LOW_MOOD_NO_JOBS;
    }

    if (sentiment_contribution_taxes < worst_sentiment) {
        worst_sentiment = sentiment_contribution_taxes;
        city_data.sentiment.low_mood_cause = LOW_MOOD_HIGH_TAXES;
    }

    if (sentiment_contribution_wages < worst_sentiment) {
        worst_sentiment = sentiment_contribution_wages;
        city_data.sentiment.low_mood_cause = LOW_MOOD_LOW_WAGES;
    }

    if (sentiment_contribution_tents < worst_sentiment) {
        city_data.sentiment.low_mood_cause = LOW_MOOD_MANY_TENTS;
    }

    city_data.sentiment.previous_value = city_data.sentiment.value;
}
