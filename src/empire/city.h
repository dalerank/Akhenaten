#pragma once

#include "empire/type.h"
#include "game/resource.h"

struct empire_city {
    int in_use; // this can be 2, so it's an int!
    e_empire_city type;
    int name_id;
    int route_id;
    bool is_open;
    bool buys_resource[RESOURCES_MAX];
    bool sells_resource[RESOURCES_MAX];
    int cost_to_open;
    int ph_unk01;
    int ph_unk02;
    int trader_entry_delay;
    int empire_object_id;
    int is_sea_trade;
    int trader_figure_ids[3];
};

void empire_city_clear_all(void);

empire_city* empire_city_get(int city_id);

int empire_city_get_route_id(int city_id);

bool empire_can_import_resource(int resource, bool check_if_open);
bool empire_can_export_resource(int resource, bool check_if_open);

bool empire_can_produce_resource(int resource, bool check_if_open);
// bool empire_can_produce_resource_potentially(int resource);

int empire_city_get_for_object(int empire_object_id);

int empire_city_get_for_trade_route(int route_id);

bool empire_city_is_trade_route_open(int route_id);

void empire_city_reset_yearly_trade_amounts(void);

int empire_city_count_wine_sources(void);

int empire_city_get_vulnerable_roman(void);

void empire_city_expand_empire(void);

void empire_city_set_vulnerable(int city_id);

void empire_city_set_foreign(int city_id);

void empire_city_open_trade(int city_id);

void empire_city_generate_trader(void);

void empire_city_remove_trader(int city_id, int figure_id);

void set_city_produce_resource(int resource, bool v);
bool can_produce_resource(int resource);