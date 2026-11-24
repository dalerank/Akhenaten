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
};
ANK_CONFIG_PROPERTY(labor_category, workers_needed, workers_allocated, priority)

struct city_labor_t {
    int32_t workers_available;
    int32_t workers_employed;
    int32_t workers_unemployed;
    int32_t workers_needed;
    int8_t unemployment_percentage_for_goverment;
    int8_t unemployment_percentage;
    labor_category categories[LABOR_CATEGORY_SIZE];

    int workers_allocated(int category) const;
    const labor_category* category(int category) const;
    int priority_rank_max() const;
    int max_selectable_priority(int category) const;

    static int calc_fixed_workers_available(int num_plebs);
    static void set_category(e_building_type type, int category);

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
    void clear_storage_priority_if_split_off();

    void reset();

private:
    bool is_industry_disabled(building* b) const;
    bool should_have_workers(building* b, int category, int check_access) const;
};

city_labor_t& city_labor();

e_labor_category category_for_building(building* b);
bool labor_category_split_enabled();
bool is_enhanced_storage_labor_type(e_building_type type);

template<class T>
void city_labor_set_category(const T &model) {
    city_labor_t::set_category(model.TYPE, model.labor_category);
}
