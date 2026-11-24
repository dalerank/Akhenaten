#include "city_sentiment.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "city/buildings.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_taxes.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/difficulty.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "city/coverage.h"

#include <algorithm>
#include <numeric>
#include "scenario/scenario.h"

static const int SENTIMENT_PER_TAX_RATE[26] = {3, 2, 2, 2, 1, 1, 1, 0, 0, -1, -2, -2, -3, -3, -3, -5, -5, -5, -5, -6, -6, -6, -6, -6, -6, -6};

void sentiment_system::reset_protesters_criminals() {
    _state.protesters = 0;
    _state.criminals = 0;
}

int sentiment_system::calc_penalty_for_hut_dwellers() {
    // alternate the penalty for every update
    if (!_state.include_huts) {
        _state.include_huts = true;
        return 0;
    }

    _state.include_huts = false;
    const auto& population = _ctx.population;

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

int sentiment_system::calc_sentiment_contribution_wages() {
    const auto& finance = _ctx.finance;

    _state.wages = finance.wages;
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

int sentiment_system::calc_contribution_religion_coverage() {
    if (!game_features::gameplay_change_religion_coverage_influence_sentiment) {
        return 0;
    }

    const auto& known_gods = _ctx.gods.known_gods();
    if (known_gods.size() <= 0) {
        return 0;
    }

    int average_coverage = 0;
    for (auto *god : known_gods) {
        average_coverage += _ctx.gods.coverage_avg(god->type);
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

int sentiment_system::calc_contribution_employment() {
    _state.unemployment_pct = _ctx.labor.unemployment_percentage;

    if (_state.unemployment_pct > 25)
        return -3;
    else if (_state.unemployment_pct > 17)
        return -2;
    else if (_state.unemployment_pct > 10)
        return -1;
    else if (_state.unemployment_pct > 4)
        return 0;
    else {
        return 1;
    }
}

int sentiment_system::calc_contribution_monuments() {
    if (!game_features::gameplay_change_monuments_influence_sentiment) {
        return 0;
    }

    auto types = {BUILDING_SHRINE_OSIRIS, BUILDING_SHRINE_RA, BUILDING_SHRINE_PTAH, BUILDING_SHRINE_SETH, BUILDING_SHRINE_BAST};
    const int shrines = _ctx.buildings.count_active(types);

    int shrine_points = 0;
    const auto& population = _ctx.population;
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

void sentiment_system::update_day() {
    _state.last_mugger_message = std::max<short>(0, _state.last_mugger_message--);

    if (_ctx.day % 8 == 0) {
        update();
    }
}

void sentiment_system::init() {
    _state.can_create_mugger = (_ctx.campaign_scenario_id > 0);
    _state.can_create_protestor = (_ctx.campaign_scenario_id > 1);
}

void sentiment_system::update() {
    OZZY_PROFILER_FUNCTION();
    city_population_check_consistency();

    _state.contribution_taxes = SENTIMENT_PER_TAX_RATE[city_taxes().tax_percentage];
    _state.contribution_wages = calc_sentiment_contribution_wages();
    _state.contribution_employment = calc_contribution_employment();
    _state.contribution_religion_coverage = calc_contribution_religion_coverage();
    _state.contribution_monuments = calc_contribution_monuments();
    _state.contribution_penalty_huts = calc_penalty_for_hut_dwellers();

    // OG Hathor oracle on Bast complex: improve city sentiment.
    int contribution_hathor = 0;
    if (_ctx.hathor_oracle) {
        contribution_hathor = building_temple_complex_bast::current_params().hathor_sentiment_bonus;
    }

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

        if (_ctx.population.current < 300) {
            // small town has no complaints
            _state.contribution_employment = 0;
            _state.contribution_taxes = 0;
            _state.contribution_wages = 0;

            housed.house_happiness = default_sentiment;
            if (_ctx.population.current < 200) {
                housed.house_happiness += 10;
            } else if (default_sentiment < 50 && !!game_features::gameplay_fix_immigration) {
                // Fix very hard immigration bug: give a boost for Very Hard difficulty so that
                // immigration is not halted simply because you are between pop 200 and 300
                housed.house_happiness += 50 - default_sentiment;
            }
            housed.house_happiness += contribution_hathor;
            housed.house_happiness = calc_bound(housed.house_happiness, 0, 100);
            return;
        }
        // population >= 300
        houses_calculated++;
        _state.contribution_food = 0;
        _state.contribution_huts = 0;
        if (!house->model().food_types) {
            // tents
            housed.days_without_food = 0;
            _state.contribution_huts = _state.contribution_penalty_huts;
            total_sentiment_penalty_huts += _state.contribution_penalty_huts;
        } else {
            // shack+
            houses_needing_food++;
            if (housed.num_foods >= 2) {
                _state.contribution_food = 2;
                total_sentiment_contribution_food += 2;
                housed.days_without_food = 0;
            } else if (housed.num_foods >= 1) {
                _state.contribution_food = 1;
                total_sentiment_contribution_food += 1;
                housed.days_without_food = 0;
            } else {
                // needs food but has no food
                if (housed.days_without_food < 3)
                    housed.days_without_food++;

                _state.contribution_food = -housed.days_without_food;
                total_sentiment_contribution_food -= housed.days_without_food;
            }
        }
        housed.house_happiness += _state.contribution_taxes;
        housed.house_happiness += _state.contribution_wages;
        housed.house_happiness += _state.contribution_employment;
        housed.house_happiness += _state.contribution_food;
        housed.house_happiness += _state.contribution_huts;
        housed.house_happiness += _state.contribution_religion_coverage;
        housed.house_happiness += _state.contribution_monuments;
        housed.house_happiness += contribution_hathor;
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

    _state.value = total_houses ? total_sentiment / total_houses : 60;

    if (_state.message_delay) {
        _state.message_delay--;
    }

    if (_state.value < 48 && _state.value < _state.previous_value) {
        if (_state.message_delay <= 0) {
            _state.message_delay = 3;

            if (_state.value < 35) {
                events::emit(event_message{ false, "message_people_angry", 0, 0, SOURCE_LOCATION });
            } else if (_state.value < 40) {
                events::emit(event_message{ false, "message_city_crime", 0, 0, SOURCE_LOCATION });
            } else {
                events::emit(event_message{ false, "message_people_disgruntled", 0, 0, SOURCE_LOCATION });
            }
        }
    }

    int worst_sentiment = 0;
    _state.low_mood_cause = LOW_MOOD_NONE;
    if (sentiment_contribution_food < worst_sentiment) {
        worst_sentiment = sentiment_contribution_food;
        _state.low_mood_cause = LOW_MOOD_NO_FOOD;
    }

    if (_state.contribution_employment < worst_sentiment) {
        worst_sentiment = _state.contribution_employment;
        _state.low_mood_cause = LOW_MOOD_NO_JOBS;
    }

    if (_state.contribution_taxes < worst_sentiment) {
        worst_sentiment = _state.contribution_taxes;
        _state.low_mood_cause = LOW_MOOD_HIGH_TAXES;
    }

    if (_state.contribution_wages < worst_sentiment) {
        worst_sentiment = _state.contribution_wages;
        _state.low_mood_cause = LOW_MOOD_LOW_WAGES;
    }

    if (sentiment_contribution_tents < worst_sentiment) {
        _state.low_mood_cause = LOW_MOOD_MANY_TENTS;
    }

    _state.previous_value = _state.value;
}

class sentiment_sim_system : public sim_system {
public:
    const char* name() const override { return "sentiment"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_reset_protesters, SIM_PHASE_TICK_SLOT, 44, SIM_AREA_SENTIMENT,
          [] { g_city.sentiment_sys().reset_protesters_criminals(); }});
        schedule.add(
          {sim_step_sentiment, SIM_PHASE_DAY, -1, SIM_AREA_SENTIMENT, [] { g_city.sentiment_sys().update_day(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_sentiment_system) {
    static sentiment_sim_system system;
    g_simulation.register_system(&system);
}
