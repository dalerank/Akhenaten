#pragma once

#include "building/building_type.h"
#include "core/archive.h"
#include "core/svector.h"

#include <cstdint>

// OG city/food_supply.c: the food the city can expect in a month (farms by fertility and model laborers, cattle
// ranches, hunting lodges, fishing wharves, imports from open trade cities) against what its people need.
struct city_food_supply_rules_t {
    svector<e_building_type, 16> food_farms;
    int farm_produce_per_worker_pct = 16;
    int farm_fertility_max = 99;
    int farm_produce_scale = 10;
    int floodplain_farm_food_factor = 48;
    int meadow_farm_food_factor = 64;
    int harvest_food_divisor = 10;
    int ranch_food_factor = 16;
    int ranch_food_divisor = 4;
    int ranch_food_percentage = 80;
    int import_amount_per_load = 100;
    int months_per_year = 12;
    int food_per_cart = 100;
    int consumption_percentage = 25;
    int blessed_consumption_percentage = 20;
    int hut_warning_min_population = 300;
    int hut_warning_min_food_percent = 96;
};
ANK_CONFIG_STRUCT(city_food_supply_rules_t, food_farms, farm_produce_per_worker_pct, farm_fertility_max,
  farm_produce_scale, floodplain_farm_food_factor, meadow_farm_food_factor, harvest_food_divisor, ranch_food_factor,
  ranch_food_divisor, ranch_food_percentage, import_amount_per_load, months_per_year, food_per_cart,
  consumption_percentage, blessed_consumption_percentage, hut_warning_min_population, hut_warning_min_food_percent)

extern city_food_supply_rules_t city_food_supply_rules;

struct food_supply_sources {
    int floodplain_produce = 0;
    int meadow_produce = 0;
    int ranch_food = 0;
    int hunting_food = 0;
    int fishing_food = 0;
    int import_food = 0;
    int consumption_percentage = 0;
};

int food_supply_percentage(const food_supply_sources& sources, const city_food_supply_rules_t& rules);
int food_supply_farm_expected_produce(int fertility, int laborers, bool blessed, const city_food_supply_rules_t& rules);

struct city_food_supply_t {
    int32_t hunting_lodges_working;
    int32_t game_meat_last_month;
    int32_t game_meat_this_month;
    int32_t fishing_wharfs_working;
    int32_t fish_last_month;
    int32_t fish_this_month;

    void init();
    void advance_month();
    food_supply_sources gather() const;
    int percentage() const;
};
ANK_CONFIG_PROPERTY(city_food_supply_t, hunting_lodges_working, game_meat_last_month, game_meat_this_month,
  fishing_wharfs_working, fish_last_month, fish_this_month)
