#pragma once

#include "buildings.h"

struct labor_category_data {
    int workers_needed;
    int workers_allocated;
    int buildings;
    int priority;
    int total_houses_covered;
} ;

enum e_labor_category {
    LABOR_CATEGORY_NONE = -1,
    LABOR_CATEGORY_FOOD_PRODUCTION = 0, // todo: wrong index...
    LABOR_CATEGORY_INDUSTRY_COMMERCE = 1,
    LABOR_CATEGORY_ENTERTAINMENT = 2,
    LABOR_CATEGORY_RELIGION = 3,
    LABOR_CATEGORY_EDUCATION = 4,
    LABOR_CATEGORY_WATER_HEALTH = 5,
    LABOR_CATEGORY_INFRASTRUCTURE = 6,
    LABOR_CATEGORY_GOVERNMENT = 7,
    LABOR_CATEGORY_MILITARY = 8,
    LABOR_CATEGORY_SIZE = 10,
};

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

void city_labor_calculate_workers(int num_plebs, int num_patricians);

void city_labor_allocate_workers(void);

void city_labor_update(void);

void city_labor_set_priority(int category, int new_priority);

int city_labor_max_selectable_priority(int category);
