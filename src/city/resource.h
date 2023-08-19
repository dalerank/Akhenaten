#pragma once

#include "city/constants.h"
#include "core/game_environment.h"
#include "game/resource.h"

struct resources_list {
    int size;
    e_resource items[RESOURCES_MAX];
};

int city_resource_count(int resource);

const resources_list* city_resource_get_available(void);
const resources_list* city_resource_get_available_foods(void);
const resources_list* city_resource_get_available_market_goods(void);

int city_resource_multiple_wine_available(void);

int city_resource_food_types_available(void);
int city_resource_food_stored(void);
int city_resource_food_needed(void);
int city_resource_food_supply_months(void);
int city_resource_food_percentage_produced(void);

int city_resource_operating_granaries(void);

int city_resource_last_used_storageyard(void);
void city_resource_set_last_used_storageyard(int warehouse_id);

int city_int(int resource);
void city_resource_cycle_trade_status(int resource);
void city_resource_cycle_trade_import(int resource);
void city_resource_cycle_trade_export(int resource);

int city_resource_trading_amount(int resource);
void city_resource_change_trading_amount(int resource, int delta);

int city_resource_is_stockpiled(int resource);
void city_resource_toggle_stockpiled(int resource);

int city_resource_is_mothballed(int resource);
void city_resource_toggle_mothballed(int resource);

void city_resource_add_produced_to_granary(int amount);
void city_resource_remove_from_granary(int food, int amount);

void city_resource_add_to_storageyard(int resource, int amount);
void city_resource_remove_from_storageyard(int resource, int amount);
void city_resource_calculate_storageyard_stocks(void);

void city_resource_determine_available(void);

void city_resource_calculate_food_stocks_and_supply_wheat(void);

// void city_resource_calculate_workshop_stocks(void);

void city_resource_consume_food(void);
