#pragma once

#include "city/constants.h"
#include "core/bstring.h"
#include "core/game_environment.h"
#include "game/resource.h"

#include <iosfwd>

struct resources_list {
    int size;
    e_resource items[RESOURCES_MAX];
};

int city_resource_count(e_resource resource);
pcstr city_resource_id(e_resource resource);

const resources_list* city_resource_get_available();
const resources_list* city_resource_get_available_foods();
const resources_list* city_resource_get_available_market_goods();

int city_resource_multiple_wine_available();
int city_resource_food_types_available();
int city_resource_food_stored();
int city_resource_food_needed();
int city_resource_food_supply_months();
int city_resource_food_percentage_produced();
int city_resource_operating_granaries();
int city_resource_last_used_storageyard();
void city_resource_set_last_used_storageyard(int warehouse_id);
int city_resource_trade_status(e_resource resource);
void city_resource_cycle_trade_status(e_resource resource);
void city_resource_cycle_trade_import(e_resource resource);
void city_resource_cycle_trade_export(e_resource resource);
int city_resource_trading_amount(e_resource resource);
void city_resource_change_trading_amount(e_resource resource, int delta);
int city_resource_is_stockpiled(e_resource resource);
int city_resource_ready_for_using(e_resource resource);
void city_resource_toggle_stockpiled(e_resource resource);
int city_resource_is_mothballed(e_resource resource);
void city_resource_toggle_mothballed(e_resource resource);
void city_resource_add_produced_to_granary(int amount);
void city_resource_remove_from_granary(int food, int amount);
void city_resource_add_to_storageyard(e_resource resource, int amount);
void city_resource_remove_from_storageyard(e_resource resource, int amount);
void city_resource_calculate_storageyard_stocks();
void city_resource_determine_available();
void city_resource_calculate_food_stocks_and_supply_wheat();
void city_resource_consume_food();
void city_resource_add_items(e_resource res, int amount);

template<e_resource R>
void game_cheat_add_resource(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"100" : args.c_str());
    city_resource_add_items(R, amount);
    window_invalidate();
    city_warning_show_console(bstring128("Added ", city_resource_id(R)).c_str());
};
