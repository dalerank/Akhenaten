#pragma once

#include "labor_category.h"
#include "core/archive.h"
#include "building/building_type.h"

struct building;

struct labor_category {
    int workers_needed;
    int workers_allocated;
    int buildings;
    int priority;
    int total_houses_covered;
} ;

struct city_labor_t {
    int32_t workers_available;
    int32_t workers_employed;
    int32_t workers_unemployed;
    int32_t workers_needed;
    int8_t unemployment_percentage_for_goverment;
    int8_t unemployment_percentage;
    labor_category categories[10];

    int workers_allocated(int category) const;
    void calculate_workers(int num_plebs, int num_patricians);
    void calculate_workers_needed_per_category();
    void set_building_worker_weight();
    void allocate_workers_to_categories();
    void allocate_workers_to_water();
    void allocate_workers_to_non_water_buildings();
    void allocate_workers_to_buildings();
    void check_employment();
    void allocate_workers();
    void update();
    void set_priority(int category, int new_priority);
    int max_selectable_priority(int category);
    const labor_category* category(int category);
    static void set_category(e_building_type type, int category);
};
ANK_CONFIG_PROPERTY(city_labor_t, unemployment_percentage)

e_labor_category category_for_building(building* b);

template<class T>
void city_labor_set_category(const T &model) {
    city_labor_set_category(model.TYPE, model.labor_category);
}