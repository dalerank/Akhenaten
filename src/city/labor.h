#pragma once

#include "building/building_type.h"
#include "labor_category.h"

class building;

struct labor_category_data {
    int workers_needed;
    int workers_allocated;
    int buildings;
    int priority;
    int total_houses_covered;
} ;

int city_labor_unemployment_percentage(void);
int city_labor_unemployment_percentage_for_senate(void);

int city_labor_workers_needed(void);
int city_labor_workers_employed(void);
int city_labor_workers_unemployed(void);

int city_labor_wages(void);
void city_labor_change_wages(int amount);

int city_labor_wages_rome(void);
int city_labor_raise_wages_rome(void);
int city_labor_lower_wages_rome(void);

e_labor_category category_for_building(building* b);

const labor_category_data* city_labor_category(int category);
void city_labor_set_category(e_building_type type, int category);

template<class T>
void city_labor_set_category(const T &model) {
    city_labor_set_category(model.type, model.labor_category);
}

void city_labor_calculate_workers(int num_plebs, int num_patricians);

void city_labor_allocate_workers(void);

void city_labor_update(void);

void city_labor_set_priority(int category, int new_priority);

int city_labor_max_selectable_priority(int category);
