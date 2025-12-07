#pragma once

#include "game/resource.h"
#include "city/constants.h"

struct city_resource_handle {
    e_resource resource;

    void cycle_trade_import();
    e_trade_status trade_status();
    void cycle_trade_status();
    void cycle_trade_export();
    int industry_active();
    int industry_total();
    int yards_stored();
    bool is_stockpiled();

    bool can_produce();
    bool can_import(bool check_if_import);
    bool can_export(bool check);
    int trading_amount();

    void change_trading_amount(int amount);
    void toggle_stockpiled();
    bool is_mothballed();

    int stack_proper_quantity(int value);
    xstring name();
};

extern city_resource_handle city_resource_barley;
extern city_resource_handle city_resource_gems;
extern city_resource_handle city_resource_beer;
extern city_resource_handle city_resource_reeds;
extern city_resource_handle city_resource_clay;
extern city_resource_handle city_resource_copper;
extern city_resource_handle city_resource_flax;
extern city_resource_handle city_resource_linen;
extern city_resource_handle city_resource_papyrus;