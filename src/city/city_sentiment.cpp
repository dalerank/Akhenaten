#include "city_sentiment.h"

#include "building/building_house.h"
#include "city/constants.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/difficulty.h"
#include "game/tutorial.h"
#include "game/game.h"
#include "game/game_config.h"
#include "city/coverage.h"

#include <algorithm>
#include <numeric>

static const int SENTIMENT_PER_TAX_RATE[26] = {3, 2, 2, 2, 1, 1, 1, 0, 0, -1, -2, -2, -3, -3, -3, -5, -5, -5, -5, -6, -6, -6, -6, -6, -6, -6};

void city_sentiment_t::reset_protesters_criminals() {
    protesters = 0;
    criminals = 0;
}

int city_sentiment_t::calc_penalty_for_hut_dwellers() {
    // alternate the penalty for every update
    if (!include_huts) {
        include_huts = true;
        return 0;
    }

    include_huts = false;
    const auto &population = g_city.population;

    int penalty;
    int pct_tents = calc_percentage(population.people_in_huts, population.current);
    if (population.people_in_manors > 0) {
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
    } else if (population.people_in_residences > 0) {
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

int city_sentiment_t::calc_sentiment_contribution_wages() {
    const auto & finance = g_city.finance;

    wages = finance.wages;
    int contribution = 0;
    int wage_diff = finance.wages - finance.wages_kingdome;
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

int city_sentiment_t::calc_contribution_religion_coverage() {
    if (!game_features::gameplay_change_religion_coverage_influence_sentiment) {
        return 0;
    }

    const auto &known_gods = g_city.religion.known_gods();
    if (known_gods.size() <= 0) {
        return 0;
    }

    int average_coverage = 0;
    for (auto *god : known_gods) {
        average_coverage += g_city.religion.coverage_avg(god->type);
    }

    average_coverage /= (int)known_gods.size();
    int religion_points = 0;
    if (average_coverage >= 50) {
        religion_points = (average_coverage - 50) / 15;
    } else {
        religion_points = (average_coverage - 50) / 25 - 1;
    }
    religion_points = calc_bound(religion_points, -5, 5);
    return religion_points;
}

int city_sentiment_t::calc_contribution_employment() {
    unemployment_pct = g_city.labor.unemployment_percentage;

    if (unemployment_pct > 25)
        return -3;
    else if (unemployment_pct > 17)
        return -2;
    else if (unemployment_pct > 10)
        return -1;
    else if (unemployment_pct > 4)
        return 0;
    else {
        return 1;
    }
}

int city_sentiment_t::calc_contribution_monuments() {
    if (!game_features::gameplay_change_monuments_influence_sentiment) {
        return 0;
    }

    auto types = {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST};
    const int shrines = g_city.buildings.count_active(types);

    int shrine_points = 0;
    const auto &population = g_city.population;
    if (population.current > 5000) {
        shrine_points = 5;
    } if (population.current > 1000) {
        shrine_points = 10;
    } else if (population.current > 500) {
        shrine_points = 15;
    } else if (population.current > 350) {
        shrine_points = 25;
    } else if (population.current > 100) {
        shrine_points = 50;
    }

    int monument_points = calc_bound((shrines * shrine_points - population.current - 350) / 50, 0, 5);
    return monument_points;
}

void city_sentiment_t::update_day() {
    last_mugger_message = std::max<short>(0, last_mugger_message--);

    if (game.simtime.day % 8 == 0) {
        update();
    }
}

void city_sentiment_t::init() {
    can_create_mugger = (g_scenario.campaign_scenario_id() > 0);
    can_create_protestor = (g_scenario.campaign_scenario_id() > 1);
}

void city_sentiment_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Sentiment Update");
    city_population_check_consistency();

    contribution_taxes = SENTIMENT_PER_TAX_RATE[g_city.finance.tax_percentage];
    contribution_wages = calc_sentiment_contribution_wages();
    contribution_employment = calc_contribution_employment();
    contribution_religion_coverage = calc_contribution_religion_coverage();
    contribution_monuments = calc_contribution_monuments();
    contribution_penalty_huts = calc_penalty_for_hut_dwellers();

    int houses_calculated = 0;
    int houses_needing_food = 0;
    int total_sentiment_contribution_food = 0;
    int total_sentiment_penalty_huts = 0;
    int default_sentiment = difficulty_sentiment();

    buildings_house_do([&] (auto house) {
        if (!house->hsize()) {
            return;
        }

        auto &housed = house->runtime_data();
        if (house->house_population() <= 0) {
            housed.house_happiness = 10 + default_sentiment;
            return;
        }

        if (g_city.population.current < 300) {
            // small town has no complaints
            contribution_employment = 0;
            contribution_taxes = 0;
            contribution_wages = 0;

            housed.house_happiness = default_sentiment;
            if (g_city.population.current < 200) {
                housed.house_happiness += 10;
            } else if (default_sentiment < 50 && !!game_features::gameplay_fix_immigration) {
                // Fix very hard immigration bug: give a boost for Very Hard difficulty so that
                // immigration is not halted simply because you are between pop 200 and 300
                housed.house_happiness += 50 - default_sentiment;
            }
            return;
        }
        // population >= 300
        houses_calculated++;
        contribution_food = 0;
        contribution_huts = 0;
        if (!house->model().food_types) {
            // tents
            housed.days_without_food = 0;
            contribution_huts = contribution_penalty_huts;
            total_sentiment_penalty_huts += contribution_penalty_huts;
        } else {
            // shack+
            houses_needing_food++;
            if (housed.num_foods >= 2) {
                contribution_food = 2;
                total_sentiment_contribution_food += 2;
                housed.days_without_food = 0;
            } else if (housed.num_foods >= 1) {
                contribution_food = 1;
                total_sentiment_contribution_food += 1;
                housed.days_without_food = 0;
            } else {
                // needs food but has no food
                if (housed.days_without_food < 3)
                    housed.days_without_food++;

                contribution_food = -housed.days_without_food;
                total_sentiment_contribution_food -= housed.days_without_food;
            }
        }
        housed.house_happiness += contribution_taxes;
        housed.house_happiness += contribution_wages;
        housed.house_happiness += contribution_employment;
        housed.house_happiness += contribution_food;
        housed.house_happiness += contribution_huts;
        housed.house_happiness += contribution_religion_coverage;
        housed.house_happiness += contribution_monuments;
        housed.house_happiness = calc_bound(housed.house_happiness, 0, 100);
    });

    int sentiment_contribution_food = 0;
    int sentiment_contribution_tents = 0;
    if (houses_needing_food) {
        sentiment_contribution_food = total_sentiment_contribution_food / houses_needing_food;
    }

    if (houses_calculated) {
        sentiment_contribution_tents = total_sentiment_penalty_huts / houses_calculated;
    }

    int total_sentiment = 0;
    int total_houses = 0;
    buildings_house_do([&total_houses, &total_sentiment] (auto house) {
        if (house->house_population() > 0) {
            total_houses++;
            total_sentiment += house->runtime_data().house_happiness;
        }
    });
    
    value = total_houses ? total_sentiment / total_houses : 60;

    if (message_delay) {
        message_delay--;
    }

    if (value < 48 && value < previous_value) {
        if (message_delay <= 0) {
            message_delay = 3;

            if (value < 35) {
                events::emit(event_message{ false, "message_people_angry", 0, 0 });
            } else if (value < 40) {
                events::emit(event_message{ false, "message_city_crime", 0, 0 });
            } else {
                events::emit(event_message{ false, "message_people_disgruntled", 0, 0 });
            }
        }
    }

    int worst_sentiment = 0;
    low_mood_cause = LOW_MOOD_NONE;
    if (sentiment_contribution_food < worst_sentiment) {
        worst_sentiment = sentiment_contribution_food;
        low_mood_cause = LOW_MOOD_NO_FOOD;
    }

    if (contribution_employment < worst_sentiment) {
        worst_sentiment = contribution_employment;
        low_mood_cause = LOW_MOOD_NO_JOBS;
    }

    if (contribution_taxes < worst_sentiment) {
        worst_sentiment = contribution_taxes;
        low_mood_cause = LOW_MOOD_HIGH_TAXES;
    }

    if (contribution_wages < worst_sentiment) {
        worst_sentiment = contribution_wages;
        low_mood_cause = LOW_MOOD_LOW_WAGES;
    }

    if (sentiment_contribution_tents < worst_sentiment) {
        low_mood_cause = LOW_MOOD_MANY_TENTS;
    }

    previous_value = value;
}
