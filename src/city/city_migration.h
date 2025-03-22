#pragma once

#include <cstdint>

struct city_migration_t {
    int16_t immigration_duration;
    int32_t emigration_duration;
    int32_t immigration_amount_per_batch;
    int32_t emigration_amount_per_batch;
    int32_t immigration_queue_size;
    int32_t emigration_queue_size;
    int32_t immigrated_today;
    int32_t emigrated_today;
    int32_t refused_immigrants_today;
    int32_t no_immigration_cause;
    int8_t percentage;
    int32_t newcomers;
    int32_t emigration_message_shown;
    int32_t percentage_by_sentiment;
    uint16_t nobles_leave_city_this_year;
    bool migration_cap;
    bool invading_cap;

    void update();
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
};

int city_migration_percentage();
int city_migration_newcomers();
void city_migration_reset_newcomers();