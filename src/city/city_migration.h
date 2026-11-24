#pragma once

#include <cstdint>
#include <functional>

#include "core/archive.h"
#include "city/city_population.h"

struct event_migration_update { int population; };

struct sentiment_step_t { int s; int i; };
ANK_CONFIG_STRUCT(sentiment_step_t, s, i)

struct unemployment_step_t { int u; int p; };
ANK_CONFIG_STRUCT(unemployment_step_t, u, p)

struct city_migration_defaults_t {
    uint8_t max_immigration_amount_per_batch;
    uint8_t max_emigration_amount_per_batch;
    uint8_t max_newcomers_per_update;
    uint8_t max_leftovers_per_update;
};
ANK_CONFIG_STRUCT(city_migration_defaults_t,
    max_immigration_amount_per_batch,
    max_emigration_amount_per_batch,
    max_newcomers_per_update,
    max_leftovers_per_update)

struct city_migration_t {
    using condition = std::function<void(city_migration_t&)>;

    uint8_t immigration_queue_size;
    uint8_t emigration_queue_size;
    uint16_t immigration_duration;
    uint16_t emigration_duration;
    uint8_t immigration_amount_per_batch;
    uint8_t emigration_amount_per_batch;
    uint8_t immigrated_today;
    uint8_t emigrated_today;
    uint8_t refused_immigrants_today;
    int16_t percentage;
    int16_t percentage_by_sentiment;
    int16_t percentage_by_unemployments;
    int32_t population_cap;
    int8_t no_immigration_cause;
    int8_t emigration_message_shown;
    uint16_t nobles_leave_city_this_year;
    uint16_t newcomers;

    bool migration_cap;
    bool invading_cap;

    int problems_cause() const { return no_immigration_cause; }

    svector<condition, 16> conditions;
    std::unordered_map<xstring, int> cap_reasons;
    std::unordered_map<xstring, std::pair<int, int>> unemployment_cap_reasons;

    static city_migration_defaults_t& current_params();

    void add_condition(condition cond);
    void set_migration_cap(xstring reason, int cap);
    void set_unemployments_cap(xstring reason, int min, int max);
    const std::unordered_map<xstring, int>& get_migration_caps() const;

    void reset();
    void clear_conditions();
    void update();
    void update_month();
    void update_conditions();
    void update_status();
    void nobles_leave_city(int num_people);
    void create_migrants();
    void create_emigrants(int num_people);
    void create_immigrants(int num_people);
    void determine_reason();
    int no_room_for_immigrants();
    void advance_year() { nobles_leave_city_this_year = 0; }
    void reset_newcomers() { newcomers = 0; }
};
ANK_CONFIG_PROPERTY(city_migration_t, newcomers, percentage, no_immigration_cause)

city_migration_t& city_migration();
