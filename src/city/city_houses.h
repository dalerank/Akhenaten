#pragma once

#include "building/building_house_demands.h"

struct city_houses_t : house_demands {
    void reset();
    void reset_demands();
    void calculate_culture_demands();
    void update_health();
    void decay_tax_coverage();
    void decay_services();
    void decay_houses_covered();
    void calculate_culture_aggregates();
    void process_evolve();
};

city_houses_t& city_houses();
