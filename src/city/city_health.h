#pragma once

#include <cstdint>

#include "core/archive.h"
#include "core/svector.h"

struct event_city_disease { int absday; };

struct city_health_population_bonus {
    int32_t pop;
    int32_t bonus;
};
ANK_CONFIG_STRUCT(city_health_population_bonus, pop, bonus)

struct city_health_rules_t {
    float coverage_factor = 0.01f;
    int32_t mortuary_points = 25;
    int32_t physician_points = 15;
    int32_t food_points = 10;
    int32_t second_food_points = 5;
    int32_t third_food_points = 5;
    int32_t physician_and_food_points = 40;
    int32_t monthly_step = 2;
    svector<city_health_population_bonus, 16> population_bonus;
};
ANK_CONFIG_STRUCT(city_health_rules_t,
    coverage_factor, mortuary_points, physician_points, food_points,
    second_food_points, third_food_points, physician_and_food_points,
    monthly_step, population_bonus)

struct city_health_t {
    int32_t num_mortuary_workers;
    int32_t target_value;
    int32_t value;

    void change(int amount);
    void start_disease(int total_people, bool force, int plague_people);
    void update_month();
    void reset_mortuary_workers();
    void add_mortuary_workers(int amount);
    void update_coverage();
};
