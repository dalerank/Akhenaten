#pragma once

#include <cstdint>
#include "building/building_type.h"
#include "core/archive.h"

struct event_population_changed { int value; };

struct population_milestone {
    uint32_t pop;
    xstring title;
    xstring message;
};
ANK_CONFIG_STRUCT(population_milestone, pop, title, message)

struct city_population_rules_t {
    std::array<int8_t, 10> births_per_age_decennium = { 0, 3, 16, 9, 2, 0, 0, 0, 0, 0 };
    svector<population_milestone, 16> milestones;
};
ANK_CONFIG_STRUCT(city_population_rules_t, births_per_age_decennium, milestones);

struct city_population_t {
    int32_t current;
    int32_t last_day_current;
    int32_t last_year;
    int32_t school_age;
    int32_t academy_age;
    int32_t working_age;
    struct {
        std::array<int32_t, 2400> values;
        int32_t next_index;
        int32_t count;
    } monthly;
    std::array<uint16_t, 100> at_age;
    std::array<uint16_t, HOUSE_LEVEL_MAX> at_level;
    std::array<uint16_t, HOUSE_LEVEL_MAX> housing_type_counts;
    std::array<uint16_t, 4> houses_demanding_goods;

    int32_t yearly_update_requested;
    int32_t yearly_births;
    int32_t yearly_deaths;
    int32_t lost_removal;
    int32_t lost_homeless;
    int32_t lost_troop_request;
    int32_t last_change;
    int32_t total_all_years;
    int32_t total_years;
    int32_t average_per_year;
    int32_t highest_ever;
    int32_t total_capacity;
    int32_t room_in_houses;

    int32_t people_in_huts;
    int32_t people_in_shanties;
    int32_t people_in_residences;
    int32_t people_in_manors;
    int32_t percentage_plebs;

    int32_t last_used_house_add;
    int32_t last_used_house_remove;

    int get_people_in_age_decennium(int decennium) const;

    int get_people_of_working_age() const;
    int get_people_aged_between(int min, int max) const;

    int at_month(int max_months, int month) const;
    int total_housing_buildings() const;

    void reset();
    void recalculate();
    void yearly_recalculate();
    void yearly_update();
    int average_age();
    void add(int num_people);
    void remove(int num_people);
    void add_homeless(int num_people);
    void remove_homeless(int num_people);
    void remove_home_removed(int num_people);
    void remove_for_troop_request(int num_people);
    void record_monthly();
    void update_day();
    int add_to_houses(int num_people);
    int remove_from_houses(int num_people);
    int create_immigrants(int num_people);
    void update_room();
    int create_emigrants(int num_people);
    void reached_milestone(bool force);
    void evict_overcrowded();
    void update_migration();
    void calculate_working_people();
    void calculate_educational_age();
    void yearly_calculate_births();
    void houses_demanding_goods_fill_from();
    void housing_type_counts_update();
    void count_at_levels();
    void yearly_advance_ages_and_calculate_deaths();
    void request_yearly_update();
    void check_consistency();

private:
    void clear_capacity();
    void add_capacity(int people_in_house, int max_people);
    void add_to_census(int num_people);
    void remove_from_census(int num_people);
    void remove_from_census_in_age_decennium(int decennium, int num_people);
    int calculate_people_per_house_type();
};

ANK_CONFIG_PROPERTY(city_population_t, current, people_in_shanties, people_in_manors, highest_ever)

city_population_t& city_population();
