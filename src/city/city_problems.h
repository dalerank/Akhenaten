#pragma once

#include <array>
#include <cstdint>

#include "core/archive.h"
#include "core/svector.h"

// OG figure_phrase.c: the city problems a walker talks about, by weight.
enum e_city_problem : int8_t {
    CITY_PROBLEM_HEALTH = 0,
    CITY_PROBLEM_FOOD = 1,
    CITY_PROBLEM_INVASION = 2,
    CITY_PROBLEM_WORKER_SHORTAGE = 3,
    CITY_PROBLEM_GODS = 4,
    CITY_PROBLEM_KINGDOM = 5,
    CITY_PROBLEM_UNEMPLOYMENT = 6,
    CITY_PROBLEM_ENTERTAINMENT = 7,
    CITY_PROBLEM_COUNT = 8,
    CITY_PROBLEM_NOTHING_TO_COMPLAIN = 8,
    CITY_PROBLEM_NONE = 9,
};

struct city_problem_step {
    int32_t value;
    uint8_t weight;
};
ANK_CONFIG_STRUCT(city_problem_step, value, weight)

using city_problem_steps = svector<city_problem_step, 4>;

// A "below" table takes the first step whose value is above the city's value, an "above" table the first step
// whose value is below it; no step means calm_weight.
struct city_problem_rules_t {
    uint8_t calm_weight = 1;
    uint8_t undefended_invasion_weight = 8;
    city_problem_steps health_below;
    city_problem_steps food_months_below;
    city_problem_steps worker_shortage_above;
    city_problem_steps lowest_god_mood_below;
    city_problem_steps kingdom_below;
    city_problem_steps unemployment_above;
    city_problem_steps entertainment_below;
};
ANK_CONFIG_STRUCT(city_problem_rules_t, calm_weight, undefended_invasion_weight, health_below, food_months_below,
  worker_shortage_above, lowest_god_mood_below, kingdom_below, unemployment_above, entertainment_below)

struct city_problem_inputs {
    int32_t health = 0;
    int32_t food_supply_months = 0;
    bool invasion_running = false;
    bool has_defenders = false;
    bool favour_army_sent = false;
    int32_t workers_allocated = 0;
    int32_t workers_needed = 0;
    int32_t lowest_god_mood = 100;
    int32_t kingdom_rating = 0;
    int32_t population = 0;
    int32_t workers_unemployed = 0;
    int32_t average_entertainment = 0;
};

struct city_problem_weights {
    std::array<uint8_t, CITY_PROBLEM_COUNT> weights{};
    int32_t total = 0;
    bool none = true;
};

city_problem_inputs city_problem_gather_inputs();
city_problem_weights city_problem_compute_weights(const city_problem_inputs& in);
int city_problem_pick(const city_problem_weights& w, int random7);

// The weights of the last pick, which the figure window's "tell me more" button walks through.
city_problem_weights& city_problem_last_weights();
int city_problem_pick_current();
bool city_problem_other_loaded(int current_phrase);
int city_problem_next(int current_phrase);
