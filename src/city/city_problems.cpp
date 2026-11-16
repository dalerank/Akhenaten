#include "city/city_problems.h"

#include <algorithm>

#include "city/city.h"
#include "city/city_resource.h"
#include "core/random.h"
#include "figure/formation.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

city_problem_rules_t ANK_VARIABLE(city_problem_rules);

namespace {

    city_problem_weights g_last_weights;

    uint8_t weight_below(const city_problem_steps& steps, int value, bool& none) {
        for (const auto& step : steps) {
            if (value < step.value) {
                none = false;
                return step.weight;
            }
        }
        return city_problem_rules.calm_weight;
    }

    uint8_t weight_above(const city_problem_steps& steps, int value, bool& none) {
        for (const auto& step : steps) {
            if (value > step.value) {
                none = false;
                return step.weight;
            }
        }
        return city_problem_rules.calm_weight;
    }

} // namespace

city_problem_inputs city_problem_gather_inputs() {
    city_problem_inputs in;
    in.health = g_city.health.value;
    in.food_supply_months = city_resource_food_supply_months();
    in.invasion_running = g_scenario.events.any_invasion_running();
    in.has_defenders = formation_get_num_forts() > 0 || city_own_warships() > 0;
    in.favour_army_sent = g_scenario.events.favour_invasion_fired();
    for (const auto& category : g_city.labor.categories) {
        in.workers_allocated += category.workers_allocated;
        in.workers_needed += category.workers_needed;
    }
    for (const auto& god : g_city.religion.gods) {
        in.lowest_god_mood = std::min<int>(in.lowest_god_mood, god.mood);
    }
    in.kingdom_rating = g_city.kingdome.rating;
    in.population = g_city.population.current;
    in.workers_unemployed = g_city.labor.workers_unemployed;
    in.average_entertainment = g_city.avg_coverage.average_entertainment;
    return in;
}

// OG figure_phrase_city_weights.
city_problem_weights city_problem_compute_weights(const city_problem_inputs& in) {
    const auto& rules = city_problem_rules;
    city_problem_weights out;
    auto& w = out.weights;
    bool& none = out.none;

    w[CITY_PROBLEM_HEALTH] = weight_below(rules.health_below, in.health, none);
    w[CITY_PROBLEM_FOOD] = weight_below(rules.food_months_below, in.food_supply_months, none);

    // OG leaves the weight variable untouched while a defended invasion runs, so the food weight repeats.
    if (!in.invasion_running) {
        w[CITY_PROBLEM_INVASION] = rules.calm_weight;
    } else if (!in.has_defenders) {
        w[CITY_PROBLEM_INVASION] = rules.undefended_invasion_weight;
        none = false;
    } else {
        w[CITY_PROBLEM_INVASION] = w[CITY_PROBLEM_FOOD];
    }

    if (in.workers_needed == 0) {
        w[CITY_PROBLEM_WORKER_SHORTAGE] = rules.calm_weight;
    } else {
        const int unfilled = 100 - (in.workers_allocated * 100) / in.workers_needed;
        w[CITY_PROBLEM_WORKER_SHORTAGE] = weight_above(rules.worker_shortage_above, unfilled, none);
    }

    w[CITY_PROBLEM_GODS] = weight_below(rules.lowest_god_mood_below, in.lowest_god_mood, none);

    w[CITY_PROBLEM_KINGDOM] = in.favour_army_sent ? 0 : weight_below(rules.kingdom_below, in.kingdom_rating, none);

    if (in.population == 0) {
        w[CITY_PROBLEM_UNEMPLOYMENT] = rules.calm_weight;
    } else {
        const int unemployed = (in.workers_unemployed * 100) / in.population;
        w[CITY_PROBLEM_UNEMPLOYMENT] = weight_above(rules.unemployment_above, unemployed, none);
    }

    w[CITY_PROBLEM_ENTERTAINMENT] = weight_below(rules.entertainment_below, in.average_entertainment, none);

    for (uint8_t v : w) {
        out.total += v;
    }

    // A calm side of the labour pair cancels its own weight against the other side.
    if (w[CITY_PROBLEM_WORKER_SHORTAGE] == 1) {
        if (w[CITY_PROBLEM_UNEMPLOYMENT] >= 1) {
            w[CITY_PROBLEM_WORKER_SHORTAGE] = 0;
            out.total -= 1;
        }
    } else if (w[CITY_PROBLEM_WORKER_SHORTAGE] > 1 && w[CITY_PROBLEM_UNEMPLOYMENT] == 1) {
        w[CITY_PROBLEM_UNEMPLOYMENT] = 0;
        out.total -= 1;
    }
    return out;
}

// OG figure_phrase_pick_city_problem: masks the random byte with the sum of the shares instead of a modulo.
int city_problem_pick(const city_problem_weights& cw, int random7) {
    const auto& w = cw.weights;
    if (cw.total <= 0) {
        return CITY_PROBLEM_NONE;
    }
    int sum = 0;
    for (uint8_t v : w) {
        sum += (v * 100) / cw.total;
    }
    const int r = random7 & sum;
    if (cw.none) {
        return CITY_PROBLEM_NONE;
    }
    int acc = 0;
    int i = 0;
    for (; i < CITY_PROBLEM_COUNT; i++) {
        acc += (w[i] * 100) / cw.total;
        if (r <= acc) {
            break;
        }
    }
    if (i == CITY_PROBLEM_COUNT) {
        i = CITY_PROBLEM_COUNT - 1;
    }
    return (w[i] == 1) ? CITY_PROBLEM_NOTHING_TO_COMPLAIN : i;
}

city_problem_weights& city_problem_last_weights() {
    return g_last_weights;
}

int city_problem_pick_current() {
    g_last_weights = city_problem_compute_weights(city_problem_gather_inputs());
    return city_problem_pick(g_last_weights, random_data_struct()->random1_7bit);
}

// OG building_info.c other_phrase_is_loaded.
bool city_problem_other_loaded(int current_phrase) {
    for (int i = 0; i < CITY_PROBLEM_COUNT; i++) {
        if (i != current_phrase && g_last_weights.weights[i] > 1) {
            return true;
        }
    }
    return false;
}

// OG window_figure_info_button_city_problem. OG keeps the index of the last weight above the running "best"
// index (it compares weights with an index), not the heaviest problem.
int city_problem_next(int current_phrase) {
    if (current_phrase == CITY_PROBLEM_NONE) {
        return current_phrase;
    }
    auto& w = g_last_weights.weights;
    if (current_phrase >= 0 && current_phrase < CITY_PROBLEM_COUNT) {
        w[current_phrase] = 0;
    }
    int best = 0;
    for (int i = 0; i < CITY_PROBLEM_COUNT; i++) {
        if (w[i] > best) {
            best = i;
        }
    }
    if (w[best] <= 1) {
        return current_phrase;
    }
    w[best] = 0;
    return best;
}
