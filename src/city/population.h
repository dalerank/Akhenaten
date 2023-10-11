#pragma once

int city_population();
int city_population_school_age();
int city_population_academy_age();

int city_population_last_used_house_add();
void city_population_set_last_used_house_add(int building_id);

int city_population_last_used_house_remove();
void city_population_set_last_used_house_remove(int building_id);

void city_population_clear_capacity();
void city_population_add_capacity(int people_in_house, int max_people);

/**
 * Add people to the city.
 * @param num_people Number of people to add
 */
void city_population_add(int num_people);

/**
 * Add people returning after becoming homeless.
 * @param num_people Number of people to add
 */
void city_population_add_homeless(int num_people);

/**
 * Remove people from the city.
 * @param num_people Number of people to remove
 */
void city_population_remove(int num_people);

void city_population_remove_homeless(int num_people);

void city_population_remove_home_removed(int num_people);

void city_population_remove_for_troop_request(int num_people);

int city_population_people_of_working_age();

void city_population_calculate_educational_age();

void city_population_record_monthly();

int city_population_monthly_count();

int city_population_at_month(int max_months, int month);

int city_population_at_age(int age);

int city_population_at_level(int house_level);

void city_population_request_yearly_update();

void city_population_yearly_update();

void city_population_check_consistency();

int city_population_graph_order();

void city_population_set_graph_order(int order);

int city_population_open_housing_capacity();

int calculate_total_housing_buildings();

int city_population_open_housing_capacity();

int city_population_total_housing_capacity();

int* calculate_number_of_each_housing_type();

int* calculate_houses_demanding_goods(int* housing_type_counts);

int city_population_yearly_deaths();

int city_population_yearly_births();

int city_population_average_age();

int city_population_percent_in_workforce();

int percentage_city_population_in_shanties();

int percentage_city_population_in_manors();