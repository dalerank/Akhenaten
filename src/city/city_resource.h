#pragma once

#include "city/constants.h"
#include "core/bstring.h"
#include "core/game_environment.h"
#include "game/resource.h"
#include "core/svector.h"

#include <iosfwd>
#include <string>

struct event_stats_remove_resource { e_resource resource; int amount; };
struct event_stats_append_resource { e_resource resource; int amount; };
struct event_granaries_remove_resource { e_resource resource; int amount; };
struct event_storageyards_add_resource { e_resource resource; int amount; };
struct event_storageyards_remove_resource { e_resource resource; int amount; };
struct event_city_remove_resource { e_resource resource; int amount; };

struct city_resources_t {
    uint16_t space_in_storages[RESOURCES_MAX];
    uint16_t stored_in_storages[RESOURCES_MAX];
    e_trade_status trade_status[RESOURCES_MAX];
    int16_t trading_amount[RESOURCES_MAX];
    int32_t stockpiled[RESOURCES_MAX];
    int16_t mothballed[RESOURCES_MAX];
    int16_t unk_00[RESOURCES_MAX];

    uint8_t wine_types_available;
    int8_t food_types_available_arr[RESOURCES_FOODS_MAX];
    int8_t food_types_eaten_arr[RESOURCES_FOODS_MAX];
    e_resource food_types_allowed[RESOURCES_FOODS_MAX];
    int32_t food_types_available_num;
    int32_t food_types_eaten_num;
    int32_t granary_food_stored[RESOURCES_FOODS_MAX];
    int32_t granary_total_stored;
    int32_t food_supply_months;
    int32_t food_needed_per_month;
    int32_t food_consumed_last_month;
    int32_t food_produced_last_month;
    int32_t food_produced_this_month;
    int8_t food_types_arr_unk_00[RESOURCES_FOODS_MAX];
    int8_t food_types_arr_unk_01[RESOURCES_FOODS_MAX];

    struct {
        int operating;
        int not_operating;
        int not_operating_with_food;
        int understaffed;
    } granaries;

    int yards_stored(e_resource resource);
    int granary_stored(e_resource resource);
    int stored(e_resource resource);
    int gettable(e_resource resource);

    void calculate_stocks();

    void init();
};

const resource_list &city_resource_get_available();
const resource_list &city_resource_get_available_foods();
const resource_list &city_resource_get_available_market_goods();

int city_resource_multiple_wine_available();
int city_resource_food_types_available();
int city_resource_food_supply_months();
int city_resource_food_percentage_produced();
int city_resource_operating_granaries();

e_trade_status city_resource_trade_status(e_resource resource);
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
void city_resource_calculate_storageyard_stocks();
void city_resource_determine_available();
void city_resource_calculate_food_stocks_and_supply_wheat();
void city_resource_consume_food();
void city_resource_add_items(e_resource res, int amount);
void city_resource_was_added_warning(e_resource res);

template<e_resource R>
void game_cheat_add_resource(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"100" : args.c_str());
    city_resource_add_items(R, amount);
    city_resource_was_added_warning(R);
};
