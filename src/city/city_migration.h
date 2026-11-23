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

struct migration_state {
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
};
ANK_CONFIG_PROPERTY(migration_state, newcomers, percentage, no_immigration_cause)

struct population_state;
struct sentiment_state;
struct labor_state;
struct city_figures_t;

struct migration_context {
    population_state& population;
    population_system population_sys;
    const sentiment_state& sentiment;
    const labor_state& labor;
    const city_figures_t& figures;
    int year;
    int month;
};

class migration_system {
public:
    migration_system(migration_state& state, const migration_context& ctx) : _state(state), _ctx(ctx) {}

    using condition = std::function<void(migration_state&)>;
    static void add_condition(condition);
    static void set_migration_cap(xstring reason, int cap);
    static void set_unemployments_cap(xstring reason, int min, int max);
    static const std::unordered_map<xstring, int>& get_migration_caps();
    static city_migration_defaults_t& current_params();

    void reset();
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
    void advance_year() { _state.nobles_leave_city_this_year = 0; }
    void reset_newcomers() { _state.newcomers = 0; }

private:
    migration_state& _state;
    migration_context _ctx;
};
