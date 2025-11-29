#pragma once

#include <cstdint>

struct event_city_disease { int absday; };

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
