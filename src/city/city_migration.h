#pragma once

#include <cstdint>
#include <functional>

struct city_migration_t {
    uint16_t immigration_duration;
    uint16_t emigration_duration;
    uint8_t immigration_amount_per_batch;
    uint8_t emigration_amount_per_batch;
    uint8_t immigration_queue_size;
    uint8_t emigration_queue_size;
    uint8_t immigrated_today;
    uint8_t emigrated_today;
    uint8_t refused_immigrants_today;
    int8_t no_immigration_cause;
    int8_t percentage;
    uint16_t newcomers;
    int8_t emigration_message_shown;
    int8_t percentage_by_sentiment;
    uint16_t nobles_leave_city_this_year;
    int32_t population_cap;

    bool migration_cap;
    bool invading_cap;

    void reset();
    void update();
    void update_conditions();
    void update_status();
    void nobles_leave_city(int num_people);
    void create_migrants();
    void create_emigrants(int num_people);
    void create_immigrants(int num_people);
    
    void determine_reason();
    int no_room_for_immigrants();

    int problems_cause() { return no_immigration_cause; }
    void advance_year() { nobles_leave_city_this_year = 0; }
    void reset_newcomers() { newcomers = 0; }

    using condition = std::function<void(city_migration_t &)>;
    void add_condition(condition);
};

int city_migration_percentage();
int city_migration_newcomers();
void city_migration_reset_newcomers();