#pragma once

#include "city/constants.h"
#include "core/bstring.h"
#include "game/resource.h"
#include "core/svector.h"

#include <iosfwd>
#include <string>

struct simulation_time_t;

struct event_stats_remove_resource { e_resource resource; int amount; };
struct event_stats_append_resource { e_resource resource; int amount; };
struct event_produced_resources { e_resource resource; int amount; };;
struct event_granaries_remove_resource { e_resource resource; int amount; };
struct event_storageyards_add_resource { e_resource resource; int amount; };
struct event_storageyards_remove_resource { e_resource resource; int amount; };
struct event_city_remove_resource { e_resource resource; int amount; };
struct event_toggle_industry_mothballed { e_resource resource; };

struct city_resources_t {
    uint16_t space_in_storages[RESOURCES_MAX];
    uint16_t stored_in_storages[RESOURCES_MAX];
    e_trade_status trade_status[RESOURCES_MAX];
    int16_t trading_amount[RESOURCES_MAX];
    int32_t stockpiled[RESOURCES_MAX];
    bool mothballed[RESOURCES_MAX];
    int16_t unk_00[RESOURCES_MAX];

    uint8_t beer_types_available;
    svector<uint16_t, RESOURCES_FOODS_MAX> food_types_available;
    svector<uint16_t, RESOURCES_FOODS_MAX> food_types_eaten;
    e_resource food_types_allowed[RESOURCES_FOODS_MAX];
    uint32_t granary_food_stored[RESOURCES_FOODS_MAX];
    uint32_t granary_total_stored;
    uint8_t food_supply_months;
    uint16_t food_needed_per_month;

    struct resource_consumption_t {
        uint16_t month;
        uint16_t year;
        resource_list consumed;
        resource_list stored;
        resource_list produced;

        void clear() {
            month = 0;
            year = 0;
            consumed.clear();
            stored.clear();
            produced.clear();
        }
    };

    resource_consumption_t res_last_month;
    resource_consumption_t res_this_month;

    inline int food_produced_last_month() const { return res_last_month.produced.sum(); }
    inline int food_consumed_last_month() const { return res_last_month.consumed.sum(); }

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
    const resource_list &available();
    const resource_list &available_foods();
    const resource_list &available_market_goods();
    int food_percentage_produced();
    void calculate_available_food();
    void calculate_food_stocks_and_supply_wheat();
    void consume_food_weekly(const simulation_time_t& t);
    void consume_goods_weekly(const simulation_time_t& t);
    void toggle_mothballed(e_resource resource);
    bool is_mothballed(e_resource resource);
    void toggle_stockpiled(e_resource resource);
    int is_stockpiled(e_resource resource);

    int food_types_available_num();

    void init();
    void advance_month();
};


int city_resource_multiple_wine_available();
int city_resource_food_supply_months();
int city_resource_operating_granaries();

e_trade_status city_resource_trade_status(e_resource resource);
void city_resource_cycle_trade_status(e_resource resource);
void city_resource_cycle_trade_import(e_resource resource);
void city_resource_cycle_trade_export(e_resource resource);
int city_resource_trading_amount(e_resource resource);
void city_resource_change_trading_amount(e_resource resource, int delta);
int city_resource_ready_for_using(e_resource resource);
void city_resource_remove_from_granary(int food, int amount);
void city_resource_calculate_storageyard_stocks();
void city_resource_determine_available();
void city_resource_add_items(e_resource res, int amount);
void city_resource_was_added_warning(e_resource res);

template<e_resource R>
void game_cheat_add_resource(std::istream &is, std::ostream &os) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"100" : args.c_str());
    city_resource_add_items(R, amount);
    city_resource_was_added_warning(R);
};
